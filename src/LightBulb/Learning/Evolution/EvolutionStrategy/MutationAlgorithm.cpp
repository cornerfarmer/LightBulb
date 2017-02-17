// Includes
#include "LightBulb/Learning/Evolution/EvolutionStrategy/MutationAlgorithm.hpp"
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"
#include <math.h>
#include "LightBulb/LinearAlgebra/Matrix.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"
#include "LightBulb/Random/ZigguratGenerator.hpp"

namespace LightBulb
{
	MutationAlgorithm::MutationAlgorithm(double mutationStrengthChangeSpeed_, double mutationStrengthMax_, double mutationStrengthMin_)
	{
		mutationStrengthChangeSpeed = mutationStrengthChangeSpeed_;
		// Initialize the mutation strength boundaries
		mutationStrengthMax = mutationStrengthMax_;
		mutationStrengthMin = mutationStrengthMin_;
	}

	void MutationAlgorithm::execute(AbstractIndividual& individual1)
	{
		Vector<>& mutationStrength = individual1.getMutationStrength();

		if (isCalculatorType(CT_GPU))
		{
			std::vector<Matrix<>>& weights = individual1.getNeuralNetwork().getNetworkTopology().getAllWeights();
			int randNumberCount = mutationStrength.getViennaclValue().size();
			for (auto layer = weights.begin(); layer != weights.end(); layer++)
				randNumberCount += layer->getViennaclValue().size1() * layer->getViennaclValue().size2();

			const Vector<>& randNumbers = zigguratGenerator->randMultipleDouble(randNumberCount);

			mutateMutationStrength(mutationStrength.getViennaclValueForEditing(), randNumbers.getViennaclValue());

			unsigned int mutationStrengthIndex = 0;
			// Go through all edges
			for (auto layer = weights.begin(); layer != weights.end(); layer++) {
				mutateWeights(layer->getViennaclValueForEditing(), mutationStrength.getViennaclValue(), mutationStrengthIndex, mutationStrength.getViennaclValue().size() + mutationStrengthIndex, randNumbers.getViennaclValue());
				mutationStrengthIndex += layer->getViennaclValue().size1() * layer->getViennaclValue().size2();
			}
		}
		else
		{
			// Go through all mutationStrength values
			for (int i = 0; i < mutationStrength.getEigenValue().size(); i++)
			{
				// Shrink or grow the mutationStrength randomly: *= exp(changeSpeed * random);
				mutationStrength.getEigenValueForEditing()(i) *= exp(mutationStrengthChangeSpeed * zigguratGenerator->randFloat());
				// Make sure the values stays inside our boundaries
				mutationStrength.getEigenValueForEditing()(i) = (mutationStrength.getEigenValue()(i) < 0 ? -1 : 1) * std::min(mutationStrengthMax, std::max(mutationStrengthMin, std::abs(mutationStrength.getEigenValue()(i))));
			}

			std::vector<Matrix<>>& weights = individual1.getNeuralNetwork().getNetworkTopology().getAllWeights();
			int mutationStrengthIndex = 0;
			// Go through all edges
			for (auto layer = weights.begin(); layer != weights.end(); layer++)
			{
				for (int i = 0; i < layer->getEigenValue().rows(); i++)
				{
					for (int j = 0; j < layer->getEigenValue().cols(); j++)
					{
						// Simply add the corresponding mutationStrength value to the weight
						double weightAdd = mutationStrength.getEigenValue()[mutationStrengthIndex] * zigguratGenerator->randFloat();
						(*layer).getEigenValueForEditing()(i, j) += weightAdd;
						mutationStrengthIndex++;
					}
				}
			}
		}
	}

	void MutationAlgorithm::mutateMutationStrength(viennacl::vector_base<float>& mutationStrength, const viennacl::vector_base<float>& randNumbers) const
	{
		static viennacl::ocl::kernel& kernel = getKernel("mutation_algorithm", "mutateMutationStrength", "mutation_algorithm.cl");

		viennacl::ocl::enqueue(kernel(
			viennacl::traits::opencl_handle(mutationStrength),
			cl_uint(viennacl::traits::start(mutationStrength)),
			cl_uint(viennacl::traits::stride(mutationStrength)),
			cl_uint(viennacl::traits::size(mutationStrength)),

			cl_float(mutationStrengthChangeSpeed),
			cl_float(mutationStrengthMax),
			cl_float(mutationStrengthMin),

			viennacl::traits::opencl_handle(randNumbers)
		));
	}

	void MutationAlgorithm::mutateWeights(viennacl::matrix_base<float>& W, const viennacl::vector_base<float>& mutationStrength, unsigned int mutationStrengthOffset, unsigned int randNumbersOffset, const viennacl::vector_base<float>& randNumbers) const
	{
		static viennacl::ocl::kernel& kernel = getKernel("mutation_algorithm", "mutateWeights", "mutation_algorithm.cl");

		viennacl::ocl::enqueue(kernel(
			viennacl::traits::opencl_handle(W),
			cl_uint(viennacl::traits::start1(W)), cl_uint(viennacl::traits::start2(W)),
			cl_uint(viennacl::traits::stride1(W)), cl_uint(viennacl::traits::stride2(W)),
			cl_uint(viennacl::traits::size1(W)), cl_uint(viennacl::traits::size2(W)),
			cl_uint(viennacl::traits::internal_size1(W)), cl_uint(viennacl::traits::internal_size2(W)),

			viennacl::traits::opencl_handle(mutationStrength),
			cl_uint(viennacl::traits::start(mutationStrength)),
			cl_uint(viennacl::traits::stride(mutationStrength)),
			cl_uint(viennacl::traits::size(mutationStrength)),
				
			cl_uint(mutationStrengthOffset),

			viennacl::traits::opencl_handle(randNumbers),
			cl_uint(randNumbersOffset)
		));
	}

	AbstractMutationAlgorithm* MutationAlgorithm::clone() const
	{
		return new MutationAlgorithm(*this);
	}

}

