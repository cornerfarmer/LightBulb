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
	options->maxTries = 1;
	getOptions()->backpropagationLearningRuleOptions.offlineLearning = true;
	// Create a new ResilientLearningRateHelper
	backpropagationLearningRule.reset(new BackpropagationLearningRule(getOptions()->backpropagationLearningRuleOptions));
}


void CascadeCorrelationLearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
{
	backpropagationLearningRule->initializeLearningAlgoritm(neuralNetwork, teacher, activationOrder);
	currentNetworkTopology = dynamic_cast<CascadeCorrelationNetwork*>(neuralNetwork.getNetworkTopology());
	currentTeacher = &teacher;
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
			gradient = (correlations[*outputNeuron] > 0 ? 1 : (correlations[*outputNeuron] < 0 ? -1 : 0)) * currentCandidateUnit->executeDerivationOnActivationFunction(candidateNetInputCache[(*currentTeacher->getTeachingLessons())[lessonIndex].get()]) * neuronOutputCache[(*currentTeacher->getTeachingLessons())[lessonIndex].get()][edge->getPrevNeuron()] * errorFactors[(*currentTeacher->getTeachingLessons())[lessonIndex].get()][*outputNeuron];
		}

		return -gradient;
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
	backpropagationLearningRule->adjustWeight(edge, gradient);
}

void CascadeCorrelationLearningRule::printDebugOutput()
{
	backpropagationLearningRule->printDebugOutput();
	if (currentMode == CANDIDATEUNITLEARNINGMODE)
		std::cout << "cor :" << std::fixed << std::setprecision(10) << getTotalCorrelation() << " ";
}

float CascadeCorrelationLearningRule::getTotalCorrelation()
{
	float totalCorrelation = 0;
	for (std::map<StandardNeuron*, float>::iterator correlation = correlations.begin(); correlation != correlations.end(); correlation++)
	{
		totalCorrelation += std::abs(correlation->second);
	}
	return totalCorrelation;
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

void CascadeCorrelationLearningRule::calcAllCorrelations(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder, bool calcErrorFactor)
{	
	std::map<AbstractTeachingLesson*, std::unique_ptr<ErrorMap_t>> errorMaps;
	std::map<AbstractTeachingLesson*, float> candidateOutputs;
	for (std::vector<std::unique_ptr<AbstractTeachingLesson>>::iterator teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++)
	{
		errorMaps[teachingLesson->get()] = (*teachingLesson)->getErrormap(neuralNetwork, activationOrder);
		candidateOutputs[teachingLesson->get()] = currentCandidateUnit->getActivation();
		
		neuralNetwork.getNetworkTopology()->getAllNeuronOutputs(neuronOutputCache[teachingLesson->get()]);
		candidateNetInputCache[teachingLesson->get()] = currentCandidateUnit->getNetInput();
	}

	float meanCandidateOutput = 0;
	for (std::vector<std::unique_ptr<AbstractTeachingLesson>>::iterator teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++)
	{
		meanCandidateOutput += candidateOutputs[teachingLesson->get()];
	}
	meanCandidateOutput /= teacher.getTeachingLessons()->size();	

	for (std::vector<StandardNeuron*>::iterator outputNeuron = currentNetworkTopology->getOutputNeurons()->begin(); outputNeuron != currentNetworkTopology->getOutputNeurons()->end(); outputNeuron++)
	{
		float meanErrorValue = 0;
		if (calcErrorFactor)
		{
			for (std::vector<std::unique_ptr<AbstractTeachingLesson>>::iterator teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++)
			{
				meanErrorValue += (*errorMaps[teachingLesson->get()])[0][*outputNeuron];
			}
			meanErrorValue /= teacher.getTeachingLessons()->size();	
		}

		correlations[*outputNeuron] = 0;
		for (std::vector<std::unique_ptr<AbstractTeachingLesson>>::iterator teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++)
		{
			if (calcErrorFactor)
			{
				errorFactors[teachingLesson->get()][*outputNeuron] = ((*errorMaps[teachingLesson->get()])[0][*outputNeuron] - meanErrorValue);
			}

			correlations[*outputNeuron] += (candidateOutputs[teachingLesson->get()] - meanCandidateOutput) * errorFactors[teachingLesson->get()][*outputNeuron];
		}
	}
}

void CascadeCorrelationLearningRule::initializeIteration(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder) 
{
	if (iteration % getOptions()->addNeuronAfterIterationInterval == 0 || (getOptions()->addNeuronAfterLearningHasStopped && backpropagationLearningRule->learningHasStopped()))
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

			calcAllCorrelations(neuralNetwork, teacher, activationOrder, true);

			std::cout << "Adds a new neuron and starts to train it:" << std::endl;
		}
		else if (currentMode == CANDIDATEUNITLEARNINGMODE)
		{
			currentMode = OUTPUTNEURONSLEARNINGMODE;
			std::cout << "Stops neuron training and starts the training of the output layer:" << std::endl;
		}
		// If used, initialize the learning rate helper
		if (backpropagationLearningRule->getOptions()->resilientLearningRate)
			backpropagationLearningRule->resilientLearningRateHelper->initialize(neuralNetwork);
	}
	else if (currentMode == CANDIDATEUNITLEARNINGMODE)
	{
		calcAllCorrelations(neuralNetwork, teacher, activationOrder, false);
	}
}

bool CascadeCorrelationLearningRule::configureNextErroMapCalculation(int* nextStartTime, int* nextTimeStepCount, AbstractTeachingLesson& teachingLesson)
{
	if (*nextStartTime != -1)
		return false;
	else
	{
		if (currentMode == CANDIDATEUNITLEARNINGMODE) 
			*nextTimeStepCount = -1;
		else
			*nextTimeStepCount = 0;
		*nextStartTime = 0;		
		return true;
	}
}