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
#include "CascadeCorrelationNetwork.hpp"

CascadeCorrelationLearningRule::CascadeCorrelationLearningRule(CascadeCorrelationLearningRuleOptions& options_) 
	: AbstractLearningRule(new CascadeCorrelationLearningRuleOptions(options_))
{
	options->offlineLearning = true;
	getOptions()->backpropagationLearningRuleOptions.offlineLearning = true;
	// Create a new ResilientLearningRateHelper
	backpropagationLearningRule.reset(new BackpropagationLearningRule(&getOptions()->backpropagationLearningRuleOptions));
}


void CascadeCorrelationLearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
{
	backpropagationLearningRule->initializeLearningAlgoritm(neuralNetwork, teacher, activationOrder);
	currentNetworkTopology = dynamic_cast<CascadeCorrelationNetwork*>(neuralNetwork.getNetworkTopology());
}


float CascadeCorrelationLearningRule::calculateDeltaWeightFromEdge(Edge* edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, ErrorMap_t* errormap)
{
	if (currentMode == OUTPUTNEURONSLEARNINGMODE && layerIndex == currentNetworkTopology->getNeurons()->size() - 1)
		return backpropagationLearningRule->calculateDeltaWeightFromEdge(edge, lessonIndex, layerIndex, neuronIndex, edgeIndex, layerCount, neuronsInLayerCount, errormap);
	else if (currentMode == CANDIDATEUNITLEARNINGMODE && edge->getNextNeuron() == currentCandidateUnit)
	{
		float gradient = 0;

		for (std::vector<StandardNeuron*>::iterator outputNeuron = currentNetworkTopology->getOutputNeurons()->begin(); outputNeuron != currentNetworkTopology->getOutputNeurons()->end(); outputNeuron++)
		{
			gradient = correlationSigns[*outputNeuron] * currentCandidateUnit->executeDerivationOnActivationFunction(currentCandidateUnit->getNetInput()) * edge->getPrevNeuron()->getActivation() * ((*errormap)[0][*outputNeuron] - meanErrorValues[*outputNeuron]);
		}

		return gradient;
	}
	else 
		return 0;
}

void CascadeCorrelationLearningRule::initializeNeuronWeightCalculation(StandardNeuron* neuron, int lessonIndex, int layerIndex, int neuronIndex, int layerCount, int neuronsInLayerCount, ErrorMap_t* errormap)
{
	if (currentMode == OUTPUTNEURONSLEARNINGMODE && layerIndex == currentNetworkTopology->getNeurons()->size() - 1)
		backpropagationLearningRule->initializeNeuronWeightCalculation(neuron, lessonIndex, layerIndex, neuronIndex, layerCount, neuronsInLayerCount, errormap);
}


AbstractActivationOrder* CascadeCorrelationLearningRule::getNewActivationOrder(NeuralNetwork &neuralNetwork)
{
	return new TopologicalOrder();
}

void CascadeCorrelationLearningRule::adjustWeight(Edge* edge, float gradient)
{
	if (gradient != 0)
		gradient = gradient;
	backpropagationLearningRule->adjustWeight(edge, gradient);
}

void CascadeCorrelationLearningRule::printDebugOutput()
{
	backpropagationLearningRule->printDebugOutput();
}

bool CascadeCorrelationLearningRule::learningHasStopped()
{
	return false;
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

void CascadeCorrelationLearningRule::initializeIteration(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder) 
{
	if (iteration % 10000 == 0 && iteration != 0)
	{
		if (currentMode == OUTPUTNEURONSLEARNINGMODE)
		{
			currentMode = CANDIDATEUNITLEARNINGMODE;
			currentNetworkTopology->addNewLayer(currentNetworkTopology->getNeurons()->size(), 0);
			currentCandidateUnit = static_cast<StandardNeuron*>(currentNetworkTopology->addNeuronIntoLayer(currentNetworkTopology->getNeurons()->size() - 1, true, true));
		
			for (std::list<Edge*>::iterator edge = currentCandidateUnit->getEfferentEdges()->begin(); edge != currentCandidateUnit->getEfferentEdges()->end(); edge++)
			{
				(*edge)->setWeight(0);
			}
			for (std::list<Edge*>::iterator edge = currentCandidateUnit->getAfferentEdges()->begin(); edge != currentCandidateUnit->getAfferentEdges()->end(); edge++)
			{
				(*edge)->randomizeWeight(options->minRandomWeightValue, options->maxRandomWeightValue);
			}

			std::map<AbstractTeachingLesson*, std::unique_ptr<ErrorMap_t>> errorMaps;
			std::map<AbstractTeachingLesson*, float> candidateOutputs;
			for (std::vector<std::unique_ptr<AbstractTeachingLesson>>::iterator teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++)
			{
				errorMaps[teachingLesson->get()] = (*teachingLesson)->getErrormap(neuralNetwork, activationOrder);
				candidateOutputs[teachingLesson->get()] = currentCandidateUnit->getActivation();
			}

			float meanCandidateOutput = 0;
			for (std::vector<std::unique_ptr<AbstractTeachingLesson>>::iterator teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++)
			{
				meanCandidateOutput += candidateOutputs[teachingLesson->get()];
			}
			meanCandidateOutput /= teacher.getTeachingLessons()->size();	

			for (std::vector<StandardNeuron*>::iterator outputNeuron = currentNetworkTopology->getOutputNeurons()->begin(); outputNeuron != currentNetworkTopology->getOutputNeurons()->end(); outputNeuron++)
			{
				meanErrorValues[*outputNeuron] = 0;
				for (std::vector<std::unique_ptr<AbstractTeachingLesson>>::iterator teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++)
				{
					meanErrorValues[*outputNeuron] += (*errorMaps[teachingLesson->get()])[0][*outputNeuron];
				}
				meanErrorValues[*outputNeuron] /= teacher.getTeachingLessons()->size();	

				float correlationSum = 0;
				for (std::vector<std::unique_ptr<AbstractTeachingLesson>>::iterator teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++)
				{
					correlationSum += (candidateOutputs[teachingLesson->get()] - meanCandidateOutput) *  ((*errorMaps[teachingLesson->get()])[0][*outputNeuron] - meanErrorValues[*outputNeuron]);
				}
				correlationSigns[*outputNeuron] = (correlationSum > 0 ? 1 : (correlationSum < 0 ? -1 : 0));
			}
		}
		else if (currentMode == CANDIDATEUNITLEARNINGMODE)
		{
			currentMode = OUTPUTNEURONSLEARNINGMODE;
		}
	}
}