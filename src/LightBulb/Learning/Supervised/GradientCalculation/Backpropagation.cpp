// Includes
#include "LightBulb/Learning/Supervised/GradientCalculation/Backpropagation.hpp"
#include "LightBulb/Teaching/Teacher.hpp"
#include "LightBulb/ActivationOrder/TopologicalOrder.hpp"
#include "LightBulb/Teaching/AbstractTeachingLesson.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"

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
					// Compute the delta value: activationFunction'(netInput) * errorValue
					lastDeltaVectorOutputLayer.getViennaclValueForEditing() = viennacl::linalg::element_prod(networkTopology.getOutputNeuronDescription().getActivationFunction().executeDerivation(netInputs[layerIndex]).getViennaclValue(), errorVector.getViennaclValue());
				}
				else
				{
					Vector nextLayerErrorValueFactor(networkTopology.getEfferentWeightsPerLayer(layerIndex).getViennaclValue().size1());
					nextLayerErrorValueFactor.getViennaclValueForEditing() = viennacl::linalg::prod(networkTopology.getEfferentWeightsPerLayer(layerIndex).getViennaclValue(), lastDeltaVectorOutputLayer.getViennaclValue());

					if (networkTopology.usesBiasNeuron())
						nextLayerErrorValueFactor.getViennaclValueForEditing().resize(nextLayerErrorValueFactor.getViennaclValue().size() - 1);
					// Compute the delta value:  activationFunction'(netInput) * nextLayerErrorValueFactor

					lastDeltaVectorOutputLayer.getViennaclValueForEditing().resize(netInputs[layerIndex].getViennaclValue().size());
					lastDeltaVectorOutputLayer.getViennaclValueForEditing() = viennacl::linalg::element_prod(networkTopology.getInnerNeuronDescription().getActivationFunction().executeDerivation(netInputs[layerIndex]).getViennaclValue(), nextLayerErrorValueFactor.getViennaclValue());
				}

				gradientToUse->at(layerIndex - 1).getViennaclValueForEditing() = gradientToUse->at(layerIndex - 1).getViennaclValue();
				gradientToUse->at(layerIndex - 1).getViennaclValueForEditing() += -1 * viennacl::linalg::outer_prod(lastDeltaVectorOutputLayer.getViennaclValue(), activations[layerIndex - 1].getViennaclValue());
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

	AbstractCloneable* Backpropagation::clone() const
	{
		return new Backpropagation(*this);
	}
}
