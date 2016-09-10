// Includes
#include "Learning/Supervised/GradientCalculation/Backpropagation.hpp"
#include "Teaching/Teacher.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "NeuronDescription/NeuronDescription.hpp"

namespace LightBulb
{
	Backpropagation::Backpropagation(double flatSpotEliminationFac_)
	{
		flatSpotEliminationFac = flatSpotEliminationFac_;
	}

	void Backpropagation::calcGradient(AbstractNetworkTopology* networkTopology, ErrorMap_t* errormap, std::vector<Eigen::MatrixXd>& gradient)
	{
		for (int layerIndex = networkTopology->getLayerCount() - 1; layerIndex > 0; layerIndex--)
		{
			// If its the last layer
			if (layerIndex == networkTopology->getLayerCount() - 1)
			{
				// Compute the delta value: activationFunction'(netInput) * errorValue
				lastDeltaVectorOutputLayer = (networkTopology->getOutputNeuronDescription()->getActivationFunction()->executeDerivation(networkTopology->getNetInputsPerLayer(layerIndex)).array() + flatSpotEliminationFac) * errormap->back().array();
			}
			else
			{
				Eigen::VectorXd nextLayerErrorValueFactor = networkTopology->getEfferentWeightsPerLayer(layerIndex) * lastDeltaVectorOutputLayer;

				// Compute the delta value:  activationFunction'(netInput) * nextLayerErrorValueFactor
				lastDeltaVectorOutputLayer = (networkTopology->getInnerNeuronDescription()->getActivationFunction()->executeDerivation(networkTopology->getNetInputsPerLayer(layerIndex)).array() + flatSpotEliminationFac) * nextLayerErrorValueFactor.tail(nextLayerErrorValueFactor.rows() - networkTopology->usesBiasNeuron()).array();
			}

			gradient[layerIndex - 1] = (lastDeltaVectorOutputLayer * networkTopology->getActivationsPerLayer(layerIndex - 1).transpose()).matrix();
		}
	}
}