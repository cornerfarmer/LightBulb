// Includes
#include "Learning/Evolution/TeachedEvolutionObject.hpp"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "Teaching/Teacher.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "Learning/Evolution/TeachingEvolutionWorld.hpp"


TeachedEvolutionObject::TeachedEvolutionObject(TeachingEvolutionWorld* teachingEvolutionWorld_, FeedForwardNetworkTopologyOptions& options)
{
	teachingEvolutionWorld = teachingEvolutionWorld_;
	currentTotalError = 0;

	// Create a new network after the given options
	FeedForwardNetworkTopology* networkTopology = new FeedForwardNetworkTopology(options);
	neuralNetwork.reset(new NeuralNetwork(networkTopology));
	// Randomize all weights
	neuralNetwork->getNetworkTopology()->randomizeWeights(teachingEvolutionWorld->getRandomGenerator(), -0.5,0.5);

	// Initialize mutation strengths
	resizeMutationStrength(neuralNetwork->getNetworkTopology()->getEdgeCount());
	randomizeMutationStrength();


}

AbstractNeuralNetwork* TeachedEvolutionObject::getNeuralNetwork()
{
	return neuralNetwork.get();
}

void TeachedEvolutionObject::doNNCalculation()
{
	// Just recalculate the total error
	TopologicalOrder activationOrder;
	currentTeachingError = teachingEvolutionWorld->getTeacher()->getTeachingError(*neuralNetwork, activationOrder);
	currentWeightDecayError = teachingEvolutionWorld->getTeacher()->getWeightDecayError(*neuralNetwork);
	currentTotalError = currentTeachingError + currentWeightDecayError;
}

void TeachedEvolutionObject::resetNN()
{
	// Only reset all activations
	neuralNetwork->getNetworkTopology()->resetActivation();
}

AbstractEvolutionObject* TeachedEvolutionObject::clone(bool addToWorld)
{
	// Create a new object
	AbstractEvolutionObject* newObject = teachingEvolutionWorld->addNewObject(addToWorld);
	// Copy all weights
	newObject->getNeuralNetwork()->getNetworkTopology()->copyWeightsFrom(*neuralNetwork->getNetworkTopology());
	// Copy all mutation strengths
	newObject->setMutationStrength(getMutationStrength());
	return newObject;
}

double TeachedEvolutionObject::getCurrentTotalError()
{
	return currentTotalError;
}


double TeachedEvolutionObject::getCurrentTeachingError()
{
	return currentTeachingError;
}

double TeachedEvolutionObject::getCurrentWeightDecayError()
{
	return currentWeightDecayError;
}
