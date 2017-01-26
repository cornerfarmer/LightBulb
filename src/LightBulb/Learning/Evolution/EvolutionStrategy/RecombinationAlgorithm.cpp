// Includes
#include "LightBulb/Learning/Evolution/EvolutionStrategy/RecombinationAlgorithm.hpp"
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"

namespace LightBulb
{
	RecombinationAlgorithm::RecombinationAlgorithm(bool useAverageForWeight_, bool useAverageForMutationStrength_)
	{
		useAverageForWeight = useAverageForWeight_;
		useAverageForMutationStrength = useAverageForMutationStrength_;
	}

	void RecombinationAlgorithm::execute(AbstractIndividual& individual1, AbstractIndividual& individual2)
	{
		std::vector<Matrix<>>& weights1 = static_cast<FeedForwardNetworkTopology&>(individual1.getNeuralNetwork().getNetworkTopology()).getAllWeights();
		std::vector<Matrix<>>& weights2 = static_cast<FeedForwardNetworkTopology&>(individual2.getNeuralNetwork().getNetworkTopology()).getAllWeights();

		if (isCalculatorType(CT_GPU))
		{
			auto layer1 = weights1.begin();
			auto layer2 = weights2.begin();
			for (; layer1 != weights1.end(); layer1++, layer2++)
			{
				if (useAverageForWeight)
					recombineWeightsWithAverage((*layer1).getViennaclValueForEditing(), (*layer2).getViennaclValue());
			}

			if (useAverageForMutationStrength)
				recombineMutationStrengthWithAverage(individual1.getMutationStrength().getViennaclValueForEditing(), individual2.getMutationStrength().getViennaclValue());
		}
		else
		{
			auto layer1 = weights1.begin();
			auto layer2 = weights2.begin();
			for (; layer1 != weights1.end(); layer1++, layer2++)
			{
				for (int i = 0; i < layer1->getEigenValue().rows(); i++)
				{
					for (int j = 0; j < layer1->getEigenValue().cols(); j++)
					{
						if (i < layer2->getEigenValue().rows() && j < layer2->getEigenValue().cols())
						{
							if (useAverageForWeight)
							{
								// Calculate the weights average and store it inside the first individual
								(*layer1).getEigenValueForEditing()(i, j) = ((*layer1).getEigenValue()(i, j) + (*layer2).getEigenValue()(i, j)) / 2;
							}
							else
							{
								if (randomGenerator->randDouble() > 0.5)
									(*layer1).getEigenValueForEditing()(i, j) = (*layer2).getEigenValue()(i, j);
							}
						}
					}
				}
			}


			Vector<>& mutationStrength1 = individual1.getMutationStrength();
			Vector<>& mutationStrength2 = individual2.getMutationStrength();
			
			for (int i = 0; i < mutationStrength2.getEigenValue().size() && i < mutationStrength1.getEigenValue().size(); i++)
			{
				if (useAverageForMutationStrength)
				{
					mutationStrength1.getEigenValueForEditing()[i] = (mutationStrength2.getEigenValue()[i] + mutationStrength1.getEigenValue()[i]) / 2;
				}
				else
				{
					if (randomGenerator->randDouble() > 0.5)
						mutationStrength1.getEigenValueForEditing()[i] = mutationStrength2.getEigenValue()[i];
				}
			}
		}
	}

	void RecombinationAlgorithm::recombineWeightsWithAverage(viennacl::matrix_base<float>& W1, const viennacl::matrix_base<float>& W2) const
	{
		static viennacl::ocl::kernel& kernel = getKernel("recombination_algorithm", "recombineWeightsWithAverage", "recombination_algorithm.cl");

		viennacl::ocl::enqueue(kernel(
			viennacl::traits::opencl_handle(W1),
			cl_uint(viennacl::traits::start1(W1)), cl_uint(viennacl::traits::start2(W1)),
			cl_uint(viennacl::traits::stride1(W1)), cl_uint(viennacl::traits::stride2(W1)),
			cl_uint(viennacl::traits::size1(W1)), cl_uint(viennacl::traits::size2(W1)),
			cl_uint(viennacl::traits::internal_size1(W1)), cl_uint(viennacl::traits::internal_size2(W1)),

			viennacl::traits::opencl_handle(W2),
			cl_uint(viennacl::traits::start1(W2)), cl_uint(viennacl::traits::start2(W2)),
			cl_uint(viennacl::traits::stride1(W2)), cl_uint(viennacl::traits::stride2(W2)),
			cl_uint(viennacl::traits::size1(W2)), cl_uint(viennacl::traits::size2(W2)),
			cl_uint(viennacl::traits::internal_size1(W2)), cl_uint(viennacl::traits::internal_size2(W2))
		));
	}

	void RecombinationAlgorithm::recombineMutationStrengthWithAverage(viennacl::vector_base<float>& vec1, const viennacl::vector_base<float>& vec2) const
	{
		static viennacl::ocl::kernel& kernel = getKernel("recombination_algorithm", "recombineMutationStrengthWithAverage", "recombination_algorithm.cl");

		viennacl::ocl::enqueue(kernel(
			viennacl::traits::opencl_handle(vec1),
			cl_uint(viennacl::traits::start(vec1)),
			cl_uint(viennacl::traits::stride(vec1)),
			cl_uint(viennacl::traits::size(vec1)),

			viennacl::traits::opencl_handle(vec2),
			cl_uint(viennacl::traits::start(vec2)),
			cl_uint(viennacl::traits::stride(vec2)),
			cl_uint(viennacl::traits::size(vec2))
		));
	}

	AbstractCloneable* RecombinationAlgorithm::clone() const
	{
		return new RecombinationAlgorithm(*this);
	}
}
