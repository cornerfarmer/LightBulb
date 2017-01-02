// Includes
#include "LightBulb/Learning/Supervised/GradientCalculation/Backpropagation.hpp"
#include "LightBulb/Teaching/Teacher.hpp"
#include "LightBulb/ActivationOrder/TopologicalOrder.hpp"
#include "LightBulb/Teaching/AbstractTeachingLesson.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"

namespace LightBulb
{
	Backpropagation::Backpropagation(double flatSpotEliminationFac_)
	{
		flatSpotEliminationFac = flatSpotEliminationFac_;
	}

	void Backpropagation::calcGradient(const AbstractNetworkTopology& networkTopology, const std::vector<Vector>& netInputs, const std::vector<Vector>& activations, const Vector& errorVector)
	{
		for (int layerIndex = networkTopology.getLayerCount() - 1; layerIndex > 0; layerIndex--)
		{
			if (lastDeltaVectorOutputLayer.getCalculatorType() == CT_GPU) 
			{
				// If its the last layer
				if (layerIndex == networkTopology.getLayerCount() - 1)
				{
					lastDeltaVectorOutputLayer.getViennaclValueForEditing().resize(netInputs[layerIndex].getViennaclValue().size());
					backpropagateLastLayer(errorVector.getViennaclValue(), networkTopology.getOutputNeuronDescription().getActivationFunction().executeDerivation(netInputs[layerIndex]).getViennaclValue(), activations[layerIndex - 1].getViennaclValue(), lastDeltaVectorOutputLayer.getViennaclValue(), gradientToUse->at(layerIndex - 1).getViennaclValueForEditing());
				}
				else
				{
					nextLayerErrorValueFactor.getViennaclValueForEditing().resize(networkTopology.getEfferentWeightsPerLayer(layerIndex).getViennaclValue().size1());

					nextLayerErrorValueFactor.getViennaclValueForEditing() = viennacl::linalg::prod(networkTopology.getEfferentWeightsPerLayer(layerIndex).getViennaclValue(), lastDeltaVectorOutputLayer.getViennaclValue());

					if (networkTopology.usesBiasNeuron())
						nextLayerErrorValueFactor.getViennaclValueForEditing().resize(nextLayerErrorValueFactor.getViennaclValue().size() - 1);
					// Compute the delta value:  activationFunction'(netInput) * nextLayerErrorValueFactor

					lastDeltaVectorOutputLayer.getViennaclValueForEditing().resize(netInputs[layerIndex].getViennaclValue().size());
					lastDeltaVectorOutputLayer.getViennaclValueForEditing() = viennacl::linalg::element_prod(networkTopology.getInnerNeuronDescription().getActivationFunction().executeDerivation(netInputs[layerIndex]).getViennaclValue(), nextLayerErrorValueFactor.getViennaclValue());

					gradientToUse->at(layerIndex - 1).getViennaclValueForEditing() = gradientToUse->at(layerIndex - 1).getViennaclValue();
					gradientToUse->at(layerIndex - 1).getViennaclValueForEditing() += -1 * viennacl::linalg::outer_prod(lastDeltaVectorOutputLayer.getViennaclValue(), activations[layerIndex - 1].getViennaclValue());

				}
			}
			else
			{
				// If its the last layer
				if (layerIndex == networkTopology.getLayerCount() - 1)
				{
					// Compute the delta value: activationFunction'(netInput) * errorValue
					lastDeltaVectorOutputLayer.getEigenValueForEditing() = (networkTopology.getOutputNeuronDescription().getActivationFunction().executeDerivation(netInputs[layerIndex]).getEigenValue().array() + flatSpotEliminationFac) * errorVector.getEigenValue().array();
				}
				else
				{
					Vector nextLayerErrorValueFactor(networkTopology.getEfferentWeightsPerLayer(layerIndex).getEigenValue() * lastDeltaVectorOutputLayer.getEigenValue());

					// Compute the delta value:  activationFunction'(netInput) * nextLayerErrorValueFactor
					lastDeltaVectorOutputLayer.getEigenValueForEditing() = (networkTopology.getInnerNeuronDescription().getActivationFunction().executeDerivation(netInputs[layerIndex]).getEigenValue().array() + flatSpotEliminationFac) * nextLayerErrorValueFactor.getEigenValue().head(nextLayerErrorValueFactor.getEigenValue().rows() - networkTopology.usesBiasNeuron()).array();
				}

				gradientToUse->at(layerIndex - 1).getEigenValueForEditing().noalias() = gradientToUse->at(layerIndex - 1).getEigenValue() + -1 * (lastDeltaVectorOutputLayer.getEigenValue() * activations[layerIndex - 1].getEigenValue().transpose()).matrix();
			}
		}
	}

	void Backpropagation::backpropagateLastLayer(const viennacl::vector_base<float>& errorVec, const viennacl::vector_base<float>& derivVec, const viennacl::vector_base<float>& actVec, viennacl::vector_base<float>& deltaVec, viennacl::matrix_base<float>& G)
	{
		viennacl::ocl::kernel& kernel = getKernel("backpropagation", "backpropagate_last", "backpropagation.cl");

		viennacl::ocl::enqueue(kernel(viennacl::traits::opencl_handle(errorVec),
			cl_uint(viennacl::traits::start(errorVec)),
			cl_uint(viennacl::traits::stride(errorVec)),
			cl_uint(viennacl::traits::size(errorVec)),

			viennacl::traits::opencl_handle(derivVec),
			cl_uint(viennacl::traits::start(derivVec)),
			cl_uint(viennacl::traits::stride(derivVec)),
			cl_uint(viennacl::traits::size(derivVec)),

			viennacl::traits::opencl_handle(actVec),
			cl_uint(viennacl::traits::start(actVec)),
			cl_uint(viennacl::traits::stride(actVec)),
			cl_uint(viennacl::traits::size(actVec)),

			viennacl::traits::opencl_handle(deltaVec),
			cl_uint(viennacl::traits::start(deltaVec)),
			cl_uint(viennacl::traits::stride(deltaVec)),
			cl_uint(viennacl::traits::size(deltaVec)),

			viennacl::traits::opencl_handle(G),
			cl_uint(viennacl::traits::start1(G)), cl_uint(viennacl::traits::start2(G)),
			cl_uint(viennacl::traits::stride1(G)), cl_uint(viennacl::traits::stride2(G)),
			cl_uint(viennacl::traits::size1(G)), cl_uint(viennacl::traits::size2(G)),
			cl_uint(viennacl::traits::internal_size1(G)), cl_uint(viennacl::traits::internal_size2(G))));
	}



	void Backpropagation::backpropagateInnerLayer(const viennacl::vector_base<float>& errorVec, const viennacl::vector_base<float>& derivVec, const viennacl::vector_base<float>& actVec, const viennacl::vector_base<float>& lastDeltaVec, viennacl::vector_base<float>& deltaVec, const viennacl::matrix_base<float>& W, viennacl::matrix_base<float>& G)
	{
		viennacl::ocl::kernel& kernel = getKernel("backpropagation", "backpropagate_last", "backpropagation.cl");

		viennacl::ocl::packed_cl_uint size_errorVec;
		size_errorVec.start = cl_uint(viennacl::traits::start(out));
		size_errorVec.stride = cl_uint(viennacl::traits::stride(out));
		size_errorVec.size = cl_uint(viennacl::traits::size(out));

		viennacl::ocl::enqueue(kernel(viennacl::traits::opencl_handle(errorVec),
			cl_uint(viennacl::traits::start(errorVec)),
			cl_uint(viennacl::traits::stride(errorVec)),
			cl_uint(viennacl::traits::size(errorVec)),

			viennacl::traits::opencl_handle(derivVec),
			cl_uint(viennacl::traits::start(derivVec)),
			cl_uint(viennacl::traits::stride(derivVec)),
			cl_uint(viennacl::traits::size(derivVec)),

			viennacl::traits::opencl_handle(actVec),
			cl_uint(viennacl::traits::start(actVec)),
			cl_uint(viennacl::traits::stride(actVec)),
			cl_uint(viennacl::traits::size(actVec)),

			viennacl::traits::opencl_handle(deltaVec),
			cl_uint(viennacl::traits::start(deltaVec)),
			cl_uint(viennacl::traits::stride(deltaVec)),
			cl_uint(viennacl::traits::size(deltaVec)),

			viennacl::traits::opencl_handle(W),
			cl_uint(viennacl::traits::start1(W)), cl_uint(viennacl::traits::start2(W)),
			cl_uint(viennacl::traits::stride1(W)), cl_uint(viennacl::traits::stride2(W)),
			cl_uint(viennacl::traits::size1(W)), cl_uint(viennacl::traits::size2(W)),
			cl_uint(viennacl::traits::internal_size1(W)), cl_uint(viennacl::traits::internal_size2(W)),

			viennacl::traits::opencl_handle(G),
			cl_uint(viennacl::traits::start1(G)), cl_uint(viennacl::traits::start2(G)),
			cl_uint(viennacl::traits::stride1(G)), cl_uint(viennacl::traits::stride2(G)),
			cl_uint(viennacl::traits::size1(G)), cl_uint(viennacl::traits::size2(G)),
			cl_uint(viennacl::traits::internal_size1(G)), cl_uint(viennacl::traits::internal_size2(G))
		));
	}

	AbstractCloneable* Backpropagation::clone() const
	{
		return new Backpropagation(*this);
	}
}
