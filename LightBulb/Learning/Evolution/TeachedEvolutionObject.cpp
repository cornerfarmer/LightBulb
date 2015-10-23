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

	LayeredNetwork* layeredNetwork = new LayeredNetwork(options);

	neuralNetwork = new NeuralNetwork(layeredNetwork);
	neuralNetwork->getNetworkTopology()->randomizeWeights(-0.5,0.5);

	resizeMutationStrength(neuralNetwork->getNetworkTopology()->getEdgeCount());

	randomizeMutationStrength();

	currentTotalError = 0;
}


NeuralNetwork* TeachedEvolutionObject::getNeuralNetwork()
{
	return neuralNetwork;
}

void TeachedEvolutionObject::doNNCalculation(EvolutionLearningRule& learningRule)
{
	TopologicalOrder activationOrder;
	currentTotalError = teachingEvolutionWorld->getTeacher()->getTotalError(*neuralNetwork, activationOrder);
}

TeachedEvolutionObject::~TeachedEvolutionObject()
{
	delete(neuralNetwork);
}


void TeachedEvolutionObject::resetNN()
{
	neuralNetwork->getNetworkTopology()->resetActivation();
}

AbstractEvolutionObject* TeachedEvolutionObject::clone()
{
	AbstractEvolutionObject* newObject = teachingEvolutionWorld->addNewObject();
	newObject->getNeuralNetwork()->getNetworkTopology()->copyWeightsFrom(*neuralNetwork->getNetworkTopology());
	newObject->setMutationStrength(getMutationStrength());
	return newObject;
}

double TeachedEvolutionObject::getCurrentTotalError()
{
	return currentTotalError;
}
