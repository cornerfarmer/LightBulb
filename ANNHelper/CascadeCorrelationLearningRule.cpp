#include "CascadeCorrelationLearningRule.hpp"
#include "Teacher.hpp"
#include "TopologicalOrder.hpp"
#include "AbstractTeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "LayeredNetwork.hpp"
#include "AbstractNeuron.hpp"
#include "AbstractNetworkTopology.hpp"
#include "StandardNeuron.hpp"
#include "Edge.hpp"

CascadeCorrelationLearningRule::CascadeCorrelationLearningRule(CascadeCorrelationLearningRuleOptions& options_) 
	: AbstractLearningRule(new CascadeCorrelationLearningRuleOptions(options_))
{
	// Create a new ResilientLearningRateHelper
	backpropagationLearningRule.reset(new BackpropagationLearningRule(&getOptions()->backpropagationLearningRuleOptions));
}


void CascadeCorrelationLearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
{
	backpropagationLearningRule->initializeLearningAlgoritm(neuralNetwork, teacher, activationOrder);
	currentNetworkTopology = neuralNetwork.getNetworkTopology();
}


float CascadeCorrelationLearningRule::calculateDeltaWeightFromEdge(Edge* edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, ErrorMap_t* errormap)
{
	if (currentMode == OUTPUTNEURONSLEARNINGMODE)
		return backpropagationLearningRule->calculateDeltaWeightFromEdge(edge, lessonIndex, layerIndex, neuronIndex, edgeIndex, layerCount, neuronsInLayerCount, errormap);
	else if (currentMode == CANDIDATEUNITLEARNINGMODE)
	{
		
	}
	else
		return 0;
}

void CascadeCorrelationLearningRule::initializeNeuronWeightCalculation(StandardNeuron* neuron, int lessonIndex, int layerIndex, int neuronIndex, int layerCount, int neuronsInLayerCount, ErrorMap_t* errormap)
{
	if (currentMode == OUTPUTNEURONSLEARNINGMODE)
		backpropagationLearningRule->initializeNeuronWeightCalculation(neuron, lessonIndex, layerIndex, neuronIndex, layerCount, neuronsInLayerCount, errormap);
	else if (currentMode == MEANCALCULATIONMODE)
	{
		if (layerIndex != currentNetworkTopology->getNeurons()->size())
		{
			meanOutputs[neuron] += neuron->getActivation();
		}
		else
		{
			meanErrorValues[neuron] += (*errormap)[0][neuron];
		}
	}
}


AbstractActivationOrder* CascadeCorrelationLearningRule::getNewActivationOrder(NeuralNetwork &neuralNetwork)
{
	return new TopologicalOrder();
}

void CascadeCorrelationLearningRule::adjustWeight(Edge* edge, float gradient)
{
	backpropagationLearningRule->adjustWeight(edge, gradient);
}

void CascadeCorrelationLearningRule::printDebugOutput()
{
	backpropagationLearningRule->printDebugOutput();
}

bool CascadeCorrelationLearningRule::learningHasStopped()
{
	return backpropagationLearningRule->learningHasStopped();
}

CascadeCorrelationLearningRuleOptions* CascadeCorrelationLearningRule::getOptions()
{
	return static_cast<CascadeCorrelationLearningRuleOptions*>(options.get());
}

void CascadeCorrelationLearningRule::initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	backpropagationLearningRule->initializeTry(neuralNetwork, teacher);
	currentMode = OUTPUTNEURONSLEARNINGMODE;
}

void CascadeCorrelationLearningRule::initializeTeachingLesson(NeuralNetwork &neuralNetwork, AbstractTeachingLesson &teachingLesson)
{
	
}

void CascadeCorrelationLearningRule::initializeIteration(NeuralNetwork &neuralNetwork, Teacher &teacher) 
{
	if (currentMode == MEANCALCULATIONMODE)
	{
		for (std::map<StandardNeuron*, float>::iterator meanOutput = meanOutputs.begin(); meanOutput != meanOutputs.end(); meanOutput++)
		{
			meanOutput->second /= teacher.getTeachingLessons()->size();
		}

		for (std::map<StandardNeuron*, float>::iterator meanErrorValue = meanErrorValues.begin(); meanErrorValue != meanErrorValues.end(); meanErrorValue++)
		{
			meanErrorValue->second /= teacher.getTeachingLessons()->size();
		}

		currentMode = CANDIDATEUNITLEARNINGMODE;
	}
	if (currentMode == CANDIDATEUNITLEARNINGMODE)
	{
		for (std::vector<StandardNeuron*>::iterator outputNeuron = currentNetworkTopology->getOutputNeurons()->begin(); outputNeuron != currentNetworkTopology->getOutputNeurons()->end(); outputNeuron++)
		{
			correlationSigns[*outputNeuron] = 0;

			for (std::vector<std::unique_ptr<AbstractTeachingLesson>>::iterator teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++)
			{
				correlationSigns[*outputNeuron] += (
			}
		}
	}
}