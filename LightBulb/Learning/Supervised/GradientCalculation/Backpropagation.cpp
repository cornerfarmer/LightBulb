// Includes
#include "Learning/Supervised/GradientCalculation/Backpropagation.hpp"
#include "Teaching/Teacher.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"


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
			lastDeltaVectorOutputLayer = (networkTopology->getOutputActivationFunction()->executeDerivation(networkTopology->getNetInputVector(layerIndex)).array() + flatSpotEliminationFac) * errormap->back().array();
		}
		else
		{
			Eigen::VectorXd nextLayerErrorValueFactor = networkTopology->getEfferentWeightsPerLayer(layerIndex) * lastDeltaVectorOutputLayer;

			// Compute the delta value:  activationFunction'(netInput) * nextLayerErrorValueFactor
			lastDeltaVectorOutputLayer = (networkTopology->getInnerActivationFunction()->executeDerivation(networkTopology->getNetInputVector(layerIndex)).array() + flatSpotEliminationFac) * nextLayerErrorValueFactor.tail(nextLayerErrorValueFactor.rows() - networkTopology->usesBiasNeuron()).array();
		}

		gradient[layerIndex - 1] = (lastDeltaVectorOutputLayer * networkTopology->getActivationVector(layerIndex - 1).transpose()).matrix();
	}
}
