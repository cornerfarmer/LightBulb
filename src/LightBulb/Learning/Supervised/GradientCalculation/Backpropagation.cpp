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

	void Backpropagation::calcGradient(const AbstractNetworkTopology& networkTopology, const std::vector<Eigen::VectorXd>& netInputs, const std::vector<Eigen::VectorBlock<Eigen::VectorXd>>& activations, const Eigen::VectorXd& errorVector)
	{
		for (int layerIndex = networkTopology.getLayerCount() - 1; layerIndex > 0; layerIndex--)
		{
			// If its the last layer
			if (layerIndex == networkTopology.getLayerCount() - 1)
			{
				// Compute the delta value: activationFunction'(netInput) * errorValue
				lastDeltaVectorOutputLayer = (networkTopology.getOutputNeuronDescription().getActivationFunction().executeDerivation(netInputs[layerIndex]).array() + flatSpotEliminationFac) * errorVector.array();
			}
			else
			{
				Eigen::VectorXd nextLayerErrorValueFactor = networkTopology.getEfferentWeightsPerLayer(layerIndex) * lastDeltaVectorOutputLayer;

				// Compute the delta value:  activationFunction'(netInput) * nextLayerErrorValueFactor
				lastDeltaVectorOutputLayer = (networkTopology.getInnerNeuronDescription().getActivationFunction().executeDerivation(netInputs[layerIndex]).array() + flatSpotEliminationFac) * nextLayerErrorValueFactor.tail(nextLayerErrorValueFactor.rows() - networkTopology.usesBiasNeuron()).array();
			}

			gradientToUse->at(layerIndex - 1).noalias() = gradientToUse->at(layerIndex - 1) + -1 * (lastDeltaVectorOutputLayer * activations[layerIndex - 1].transpose()).matrix();
		}
	}

	AbstractCloneable* Backpropagation::clone() const
	{
		return new Backpropagation(*this);
	}
}
