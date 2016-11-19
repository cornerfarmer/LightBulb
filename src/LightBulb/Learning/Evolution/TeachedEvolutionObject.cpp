// Includes
#include "Learning/Evolution/TeachedIndividual.hpp"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "Teaching/Teacher.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "Learning/Evolution/TeachingEvolutionWorld.hpp"

namespace LightBulb
{
	TeachedIndividual::TeachedIndividual(TeachingEvolutionWorld& teachingEvolutionWorld_, FeedForwardNetworkTopologyOptions& options)
	{
		teachingEvolutionWorld = &teachingEvolutionWorld_;
		currentTotalError = 0;

		// Create a new network after the given options
		FeedForwardNetworkTopology* networkTopology = new FeedForwardNetworkTopology(options);
		neuralNetwork.reset(new NeuralNetwork(networkTopology));
		// Randomize all weights
		neuralNetwork->getNetworkTopology().randomizeWeights(teachingEvolutionWorld->getRandomGenerator(), -0.5, 0.5);

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
		currentTeachingError = teachingEvolutionWorld->getTeacher().getTeachingError(*neuralNetwork, activationOrder);
		currentWeightDecayError = teachingEvolutionWorld->getTeacher().getWeightDecayError(*neuralNetwork);
		currentTotalError = currentTeachingError + currentWeightDecayError;
	}

	void TeachedIndividual::resetNN()
	{
		// Only reset all activations
		neuralNetwork->getNetworkTopology().resetActivation();
	}

	AbstractIndividual* TeachedIndividual::clone(bool addToWorld) const
	{
		// Create a new individual
		AbstractIndividual* newIndividual = teachingEvolutionWorld->addNewIndividual(addToWorld);
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