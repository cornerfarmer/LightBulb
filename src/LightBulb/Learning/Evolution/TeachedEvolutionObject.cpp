// Includes
#include "LightBulb/Learning/Evolution/TeachedIndividual.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/Teaching/Teacher.hpp"
#include "LightBulb/ActivationOrder/TopologicalOrder.hpp"
#include "LightBulb/Learning/Evolution/TeachingEvolutionEnvironment.hpp"

namespace LightBulb
{
	TeachedIndividual::TeachedIndividual(TeachingEvolutionEnvironment& teachingEvolutionEnvironment_, FeedForwardNetworkTopologyOptions& options)
	{
		teachingEvolutionEnvironment = &teachingEvolutionEnvironment_;
		currentTotalError = 0;

		// Create a new network after the given options
		FeedForwardNetworkTopology* networkTopology = new FeedForwardNetworkTopology(options);
		neuralNetwork.reset(new NeuralNetwork(networkTopology));
		// Randomize all weights
		neuralNetwork->getNetworkTopology().randomizeWeights(teachingEvolutionEnvironment->getRandomGenerator(), -0.5, 0.5);

		// Initialize mutation strengths
		resizeMutationStrength(neuralNetwork->getNetworkTopology().getEdgeCount());
		randomizeMutationStrength();


	}

	AbstractNeuralNetwork& TeachedIndividual::getNeuralNetwork()
	{
		return *neuralNetwork.get();
	}

	void TeachedIndividual::doNNCalculation()
	{
		// Just recalculate the total error
		TopologicalOrder activationOrder;
		currentTeachingError = teachingEvolutionEnvironment->getTeacher().getTeachingError(*neuralNetwork, activationOrder);
		currentWeightDecayError = teachingEvolutionEnvironment->getTeacher().getWeightDecayError(*neuralNetwork);
		currentTotalError = currentTeachingError + currentWeightDecayError;
	}

	void TeachedIndividual::resetNN()
	{
		// Only reset all activations
		neuralNetwork->getNetworkTopology().resetActivation();
	}

	AbstractIndividual* TeachedIndividual::clone(bool addToEnvironment) const
	{
		// Create a new individual
		AbstractIndividual* newIndividual = teachingEvolutionEnvironment->addNewIndividual(addToEnvironment);
		// Copy all weights
		newIndividual->getNeuralNetwork().getNetworkTopology().copyWeightsFrom(neuralNetwork->getNetworkTopology());
		// Copy all mutation strengths
		newIndividual->setMutationStrength(getMutationStrength());
		return newIndividual;
	}

	double TeachedIndividual::getCurrentTotalError() const
	{
		return currentTotalError;
	}


	double TeachedIndividual::getCurrentTeachingError() const
	{
		return currentTeachingError;
	}

	double TeachedIndividual::getCurrentWeightDecayError() const
	{
		return currentWeightDecayError;
	}
}