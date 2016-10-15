// Includes
#include "Learning/SOMLearningRule.hpp"
#include "Teaching/Teacher.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "Neuron/AbstractNeuron.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "Neuron/StandardNeuron.hpp"
#include "Neuron/AbstractNeuron.hpp"
#include "Neuron/Edge.hpp"
#include "NetworkTopology/RBFNetwork.hpp"
#include "Neuron/NeuronCompareThreshold.hpp"
#include "Function/AbstractActivationFunction.hpp"
#include "Function/AbstractNeighborhoodFunction.hpp"
#include "Function/AbstractShrinkFunction.hpp"
#include "NetworkTopology/SOMNetwork.hpp"

namespace LightBulb
{
	SOMLearningRuleOptions::~SOMLearningRuleOptions()
	{
		delete(neighborhoodFunction);
		delete(distanceShrinkFunction);
	}

	SOMLearningRuleOptions::SOMLearningRuleOptions(const SOMLearningRuleOptions &obj)
	{
		*this = obj;
		neighborhoodFunction = obj.neighborhoodFunction->getNeighborhoodFunctionCopy();
		distanceShrinkFunction = obj.distanceShrinkFunction->getShrinkFunctionCopy();
	}


	SOMLearningRule::SOMLearningRule(SOMLearningRuleOptions &options_)
		: AbstractLearningRule(new SOMLearningRuleOptions(options_))
	{

	}

	void SOMLearningRule::adjustWeight(Edge* edge, double deltaWeight)
	{
		// Set the calculated weight as new weight
		edge->setWeight(edge->getWeight() + deltaWeight);
	}

	void SOMLearningRule::printDebugOutput()
	{

	}

	bool SOMLearningRule::learningHasStopped()
	{
		return false;
	}

	void SOMLearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
	{
		// If we can change the weights before learning
		if (options->changeWeightsBeforeLearning)
		{
			// Divide neurons into classes
			static_cast<SOMNetwork*>(neuralNetwork.getNetworkTopology())->randomizeWeights(options->minRandomWeightValue, options->maxRandomWeightValue);
		}
	}

	void SOMLearningRule::initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher)
	{
		currentTimestep = 0;
	}

	void SOMLearningRule::initializeIteration(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
	{
		currentTimestep++;
	}

	AbstractActivationOrder* SOMLearningRule::getNewActivationOrder(NeuralNetwork &neuralNetwork)
	{
		return new TopologicalOrder();
	}

	void SOMLearningRule::initializeTeachingLesson(NeuralNetwork &neuralNetwork, AbstractTeachingLesson &teachingLesson)
	{
		currentActivatedNeuron = nullptr;
	}

	double SOMLearningRule::calculateDeltaWeightFromEdge(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, Edge& edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, ErrorMap_t* errormap)
	{
		// If needed calcualte the current activated neuron
		if (currentActivatedNeuron == nullptr)
		{
			for (auto neuron = currentNeuralNetwork->getNetworkTopology()->getNeurons()->front().begin(); neuron != currentNeuralNetwork->getNetworkTopology()->getNeurons()->front().end(); neuron++)
			{
				if ((*neuron)->getActivation() == (*neuron)->getActivationFunction()->getMaximum())
				{
					currentActivatedNeuron = *neuron;
					break;
				}
			}
		}
		// Change the weight depending on the distance between the current neuron and the current activated one
		return getOptions()->learningRate * getOptions()->neighborhoodFunction->execute(&neuron, currentActivatedNeuron, static_cast<SOMNetwork*>(currentNeuralNetwork->getNetworkTopology())->getStructure(), static_cast<NeuronCompareThreshold*>(neuron.getThreshold()), getOptions()->distanceShrinkFunction->execute(currentTimestep)) * (lesson.getTeachingPattern()->get(0, edgeIndex) - edge.getWeight());
	}

	SOMLearningRuleOptions* SOMLearningRule::getOptions()
	{
		return static_cast<SOMLearningRuleOptions*>(options.get());
	}
}