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

	AbstractCloneable* Backpropagation::clone() const
	{
		return new Backpropagation(*this);
	}
}
