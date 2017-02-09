// Includes
#include "LightBulb/Learning/Supervised/GradientCalculation/Backpropagation.hpp"
#include "LightBulb/Teaching/AbstractTeachingLesson.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"
#include "LightBulb/Function/ActivationFunction/AbstractActivationFunction.hpp"

namespace LightBulb
{
	Backpropagation::Backpropagation(double flatSpotEliminationFac_)
	{
		flatSpotEliminationFac = flatSpotEliminationFac_;
	}
	
	void Backpropagation::initGradient(const AbstractNetworkTopology& networkTopology)
	{
		AbstractGradientCalculation::initGradient(networkTopology);
		if (lastDeltaVectorOutputLayer.empty()) {
			lastDeltaVectorOutputLayer = networkTopology.getAllNetInputs();
		}
		if (activationFunctionDerivations.empty()) {
			activationFunctionDerivations = networkTopology.getAllNetInputs();
		}
	}

	void Backpropagation::calcGradient(const AbstractNetworkTopology& networkTopology, const std::vector<Vector<>>& netInputs, const std::vector<Vector<>>& activations, const Vector<>& errorVector, const Vector<>* alternativeActivation)
	{
		for (int layerIndex = networkTopology.getLayerCount() - 1; layerIndex > 0; layerIndex--)
		{
			const Vector<>& activationToUse = (layerIndex == 1 && alternativeActivation ? *alternativeActivation : activations[layerIndex - 1]);
			if (isCalculatorType(CT_GPU))
			{
				// If its the last layer
				if (layerIndex == networkTopology.getLayerCount() - 1)
				{
					networkTopology.getOutputNeuronDescription().getActivationFunction().executeDerivation(netInputs[layerIndex], activationFunctionDerivations[layerIndex]);
					backpropagateLastLayer(errorVector.getViennaclValue(), activationFunctionDerivations[layerIndex].getViennaclValue(), activationToUse.getViennaclValue(), lastDeltaVectorOutputLayer[layerIndex].getViennaclValueForEditing(), gradientToUse->at(layerIndex - 1).getViennaclValueForEditing());
				}
				else
				{
					nextLayerErrorValueFactor.getViennaclValueForEditing().resize(networkTopology.getAllWeights()[layerIndex].getViennaclValue().size2() - networkTopology.usesBiasNeuron());
					networkTopology.getInnerNeuronDescription().getActivationFunction().executeDerivation(netInputs[layerIndex], activationFunctionDerivations[layerIndex]);
					backpropagateInnerLayer_1(nextLayerErrorValueFactor.getViennaclValueForEditing(), lastDeltaVectorOutputLayer[layerIndex + 1].getViennaclValue(), networkTopology.getAllWeights()[layerIndex].getViennaclValue());
					backpropagateInnerLayer_2(nextLayerErrorValueFactor.getViennaclValueForEditing(), activationFunctionDerivations[layerIndex].getViennaclValue(),  lastDeltaVectorOutputLayer[layerIndex].getViennaclValueForEditing());
					backpropagateInnerLayer_3(activationToUse.getViennaclValue(), lastDeltaVectorOutputLayer[layerIndex].getViennaclValueForEditing(), gradientToUse->at(layerIndex - 1).getViennaclValueForEditing());
				}
			}
			else
			{
				// If its the last layer
				if (layerIndex == networkTopology.getLayerCount() - 1)
				{
					// Compute the delta value: activationFunction'(netInput) * errorValue
					networkTopology.getOutputNeuronDescription().getActivationFunction().executeDerivation(netInputs[layerIndex], activationFunctionDerivations[layerIndex]);
					lastDeltaVectorOutputLayer[layerIndex].getEigenValueForEditing() = (activationFunctionDerivations[layerIndex].getEigenValue().array() + flatSpotEliminationFac) * errorVector.getEigenValue().array();
				}
				else
				{
					Vector<> nextLayerErrorValueFactor(networkTopology.getEfferentWeightsPerLayer(layerIndex).getEigenValue().topRows(networkTopology.getEfferentWeightsPerLayer(layerIndex).getEigenValue().rows() - networkTopology.usesBiasNeuron()) * lastDeltaVectorOutputLayer[layerIndex + 1].getEigenValue());

					// Compute the delta value:  activationFunction'(netInput) * nextLayerErrorValueFactor
					networkTopology.getInnerNeuronDescription().getActivationFunction().executeDerivation(netInputs[layerIndex], activationFunctionDerivations[layerIndex]);
					lastDeltaVectorOutputLayer[layerIndex].getEigenValueForEditing() = (activationFunctionDerivations[layerIndex].getEigenValue().array() + flatSpotEliminationFac) * nextLayerErrorValueFactor.getEigenValue().array();
				}

				gradientToUse->at(layerIndex - 1).getEigenValueForEditing().leftCols(activationToUse.getEigenValue().rows()).noalias() += -1 * (lastDeltaVectorOutputLayer[layerIndex].getEigenValue() * activationToUse.getEigenValue().transpose()).matrix();
				if (networkTopology.usesBiasNeuron())
					gradientToUse->at(layerIndex - 1).getEigenValueForEditing().col(activationToUse.getEigenValue().rows()).noalias() -= lastDeltaVectorOutputLayer[layerIndex].getEigenValue();
			}
		}
	}

	void Backpropagation::backpropagateLastLayer(const viennacl::vector_base<float>& errorVec, const viennacl::vector_base<float>& derivVec, const viennacl::vector_base<float>& actVec, viennacl::vector_base<float>& deltaVec, viennacl::matrix_base<float>& G)
	{
		static viennacl::ocl::kernel& kernel = getKernel("backpropagation", "backpropagate_last", "backpropagation.cl");

		viennacl::ocl::packed_cl_uint size_errorVec;
		size_errorVec.start = cl_uint(viennacl::traits::start(errorVec));
		size_errorVec.stride = cl_uint(viennacl::traits::stride(errorVec));
		size_errorVec.size = cl_uint(viennacl::traits::size(errorVec));

		viennacl::ocl::packed_cl_uint size_derivVec;
		size_derivVec.start = cl_uint(viennacl::traits::start(derivVec));
		size_derivVec.stride = cl_uint(viennacl::traits::stride(derivVec));
		size_derivVec.size = cl_uint(viennacl::traits::size(derivVec));

		viennacl::ocl::packed_cl_uint size_actVec;
		size_actVec.start = cl_uint(viennacl::traits::start(actVec));
		size_actVec.stride = cl_uint(viennacl::traits::stride(actVec));
		size_actVec.size = cl_uint(viennacl::traits::size(actVec));

		viennacl::ocl::packed_cl_uint size_deltaVec;
		size_deltaVec.start = cl_uint(viennacl::traits::start(deltaVec));
		size_deltaVec.stride = cl_uint(viennacl::traits::stride(deltaVec));
		size_deltaVec.size = cl_uint(viennacl::traits::size(deltaVec));

		viennacl::ocl::enqueue(kernel(viennacl::traits::opencl_handle(errorVec),
			size_errorVec,

			viennacl::traits::opencl_handle(derivVec),
			size_derivVec,

			viennacl::traits::opencl_handle(actVec),
			size_actVec,

			viennacl::traits::opencl_handle(deltaVec),
			size_deltaVec,

			viennacl::traits::opencl_handle(G),
			cl_uint(viennacl::traits::start1(G)), cl_uint(viennacl::traits::start2(G)),
			cl_uint(viennacl::traits::stride1(G)), cl_uint(viennacl::traits::stride2(G)),
			cl_uint(viennacl::traits::size1(G)), cl_uint(viennacl::traits::size2(G)),
			cl_uint(viennacl::traits::internal_size1(G)), cl_uint(viennacl::traits::internal_size2(G))));
	}



	void Backpropagation::backpropagateInnerLayer_1(viennacl::vector_base<float>& errorVec, const viennacl::vector_base<float>& lastDeltaVec, const viennacl::matrix_base<float>& W)
	{
		static viennacl::ocl::kernel& kernel = getKernel("backpropagation", "backpropagate_inner_1", "backpropagation.cl");

		viennacl::ocl::packed_cl_uint size_errorVec;
		size_errorVec.start = cl_uint(viennacl::traits::start(errorVec));
		size_errorVec.stride = cl_uint(viennacl::traits::stride(errorVec));
		size_errorVec.size = cl_uint(viennacl::traits::size(errorVec));
		
		viennacl::ocl::packed_cl_uint size_lastDeltaVec;
		size_lastDeltaVec.start = cl_uint(viennacl::traits::start(lastDeltaVec));
		size_lastDeltaVec.stride = cl_uint(viennacl::traits::stride(lastDeltaVec));
		size_lastDeltaVec.size = cl_uint(viennacl::traits::size(lastDeltaVec));

		viennacl::ocl::enqueue(kernel(viennacl::traits::opencl_handle(errorVec),
			size_errorVec,

			viennacl::traits::opencl_handle(lastDeltaVec),
			size_lastDeltaVec,

			viennacl::traits::opencl_handle(W),
			cl_uint(viennacl::traits::start1(W)), cl_uint(viennacl::traits::start2(W)),
			cl_uint(viennacl::traits::stride1(W)), cl_uint(viennacl::traits::stride2(W)),
			cl_uint(viennacl::traits::size1(W)), cl_uint(viennacl::traits::size2(W)),
			cl_uint(viennacl::traits::internal_size1(W)), cl_uint(viennacl::traits::internal_size2(W))
		));
	}



	void Backpropagation::backpropagateInnerLayer_2(viennacl::vector_base<float>& errorVec, const viennacl::vector_base<float>& derivVec, viennacl::vector_base<float>& deltaVec)
	{
		static viennacl::ocl::kernel& kernel = getKernel("backpropagation", "backpropagate_inner_2", "backpropagation.cl");

		viennacl::ocl::packed_cl_uint size_errorVec;
		size_errorVec.start = cl_uint(viennacl::traits::start(errorVec));
		size_errorVec.stride = cl_uint(viennacl::traits::stride(errorVec));
		size_errorVec.size = cl_uint(viennacl::traits::size(errorVec));

		viennacl::ocl::packed_cl_uint size_derivVec;
		size_derivVec.start = cl_uint(viennacl::traits::start(derivVec));
		size_derivVec.stride = cl_uint(viennacl::traits::stride(derivVec));
		size_derivVec.size = cl_uint(viennacl::traits::size(derivVec));

		viennacl::ocl::packed_cl_uint size_deltaVec;
		size_deltaVec.start = cl_uint(viennacl::traits::start(deltaVec));
		size_deltaVec.stride = cl_uint(viennacl::traits::stride(deltaVec));
		size_deltaVec.size = cl_uint(viennacl::traits::size(deltaVec));

		viennacl::ocl::enqueue(kernel(viennacl::traits::opencl_handle(errorVec),
			size_errorVec,

			viennacl::traits::opencl_handle(derivVec),
			size_derivVec,

			viennacl::traits::opencl_handle(deltaVec),
			size_deltaVec
		));
	}



	void Backpropagation::backpropagateInnerLayer_3(const viennacl::vector_base<float>& actVec, viennacl::vector_base<float>& deltaVec, viennacl::matrix_base<float>& G)
	{
		static viennacl::ocl::kernel& kernel = getKernel("backpropagation", "backpropagate_inner_3", "backpropagation.cl");

		viennacl::ocl::packed_cl_uint size_actVec;
		size_actVec.start = cl_uint(viennacl::traits::start(actVec));
		size_actVec.stride = cl_uint(viennacl::traits::stride(actVec));
		size_actVec.size = cl_uint(viennacl::traits::size(actVec));

		viennacl::ocl::packed_cl_uint size_deltaVec;
		size_deltaVec.start = cl_uint(viennacl::traits::start(deltaVec));
		size_deltaVec.stride = cl_uint(viennacl::traits::stride(deltaVec));
		size_deltaVec.size = cl_uint(viennacl::traits::size(deltaVec));

		viennacl::ocl::enqueue(kernel(
			viennacl::traits::opencl_handle(actVec),
			size_actVec,

			viennacl::traits::opencl_handle(deltaVec),
			size_deltaVec,

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
