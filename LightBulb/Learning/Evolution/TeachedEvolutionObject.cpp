// Includes
#include "Learning/Evolution/TeachedEvolutionObject.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "Teaching/Teacher.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "Learning/Evolution/TeachingEvolutionWorld.hpp"


TeachedEvolutionObject::TeachedEvolutionObject(TeachingEvolutionWorld* teachingEvolutionWorld_, LayeredNetworkOptions& options)
{
	teachingEvolutionWorld = teachingEvolutionWorld_;
	currentTotalError = 0;


	// Create a new network after the given options
	LayeredNetwork* layeredNetwork = new LayeredNetwork(options);
	neuralNetwork = new NeuralNetwork(layeredNetwork);
	// Randomize all weights
	neuralNetwork->getNetworkTopology()->randomizeWeights(-0.5,0.5);

	// Initialize mutation strengths
	resizeMutationStrength(neuralNetwork->getNetworkTopology()->getEdgeCount());
	randomizeMutationStrength();
}

NeuralNetwork* TeachedEvolutionObject::getNeuralNetwork()
{
	return neuralNetwork;
}

void TeachedEvolutionObject::doNNCalculation(EvolutionLearningRule& learningRule)
{
	// Just recalculate the total error
	TopologicalOrder activationOrder;
	currentTotalError = teachingEvolutionWorld->getTeacher()->getTotalError(*neuralNetwork, activationOrder);
}

TeachedEvolutionObject::~TeachedEvolutionObject()
{
	delete(neuralNetwork);
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
