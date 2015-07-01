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
#include <algorithm>

CascadeCorrelationLearningRule::CascadeCorrelationLearningRule(CascadeCorrelationLearningRuleOptions& options_) 
	: AbstractLearningRule(new CascadeCorrelationLearningRuleOptions(options_))
{
	options->offlineLearning = true;
	options->maxTries = 1;
	getOptions()->outputNeuronsLearningRuleOptions.offlineLearning = true;
	getOptions()->candidateUnitsLearningRuleOptions.offlineLearning = true;
	// Create a new ResilientLearningRateHelper
	outputNeuronsBackpropagationLearningRule.reset(new BackpropagationLearningRule(getOptions()->outputNeuronsLearningRuleOptions));
	candidateUnitsBackpropagationLearningRule.reset(new BackpropagationLearningRule(getOptions()->candidateUnitsLearningRuleOptions));
}


void CascadeCorrelationLearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
{
	outputNeuronsBackpropagationLearningRule->initializeLearningAlgoritm(neuralNetwork, teacher, activationOrder);
	candidateUnitsBackpropagationLearningRule->initializeLearningAlgoritm(neuralNetwork, teacher, activationOrder);
	currentNetworkTopology = dynamic_cast<CascadeCorrelationNetwork*>(neuralNetwork.getNetworkTopology());
	currentTeacher = &teacher;
	currentCandidateUnits.resize(getOptions()->candidateUnitCount);
}


float CascadeCorrelationLearningRule::calculateDeltaWeightFromEdge(Edge* edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, ErrorMap_t* errormap)
{
	if (currentMode == OUTPUTNEURONSLEARNINGMODE && layerIndex == currentNetworkTopology->getNeurons()->size() - 1)
		return outputNeuronsBackpropagationLearningRule->calculateDeltaWeightFromEdge(edge, lessonIndex, layerIndex, neuronIndex, edgeIndex, layerCount, neuronsInLayerCount, errormap);
	else if (currentMode == CANDIDATEUNITLEARNINGMODE && std::find(currentCandidateUnits.begin(), currentCandidateUnits.end(), edge->getNextNeuron()) != currentCandidateUnits.end())
	{
		float gradient = 0;

		for (std::vector<StandardNeuron*>::iterator outputNeuron = currentNetworkTopology->getOutputNeurons()->begin(); outputNeuron != currentNetworkTopology->getOutputNeurons()->end(); outputNeuron++)
		{
			gradient = (correlations[edge->getNextNeuron()][*outputNeuron] > 0 ? 1 : (correlations[edge->getNextNeuron()][*outputNeuron] < 0 ? -1 : 0)) * getOutputGradient(edge, (*currentTeacher->getTeachingLessons())[lessonIndex]->getMaxTimeStep(), lessonIndex) * errorFactors[(*currentTeacher->getTeachingLessons())[lessonIndex].get()][*outputNeuron];
		}

		return -gradient;
	}
	else 
		return 0;
}

float CascadeCorrelationLearningRule::getOutputGradient(Edge* edge, int time, int lessonIndex)
{
	float outputSum = 0;
	if (edge->getNextNeuron() != edge->getPrevNeuron() || time != 0)
		outputSum += neuronOutputCache[(*currentTeacher->getTeachingLessons())[lessonIndex].get()][edge->getNextNeuron() != edge->getPrevNeuron() ? time : time - 1][edge->getPrevNeuron()];
	if (getOptions()->recurrent && time != 0)
		outputSum += getOutputGradient(edge, time - 1, lessonIndex) * edge->getNextNeuron()->getEfferentEdges()->back()->getWeight();
	return edge->getNextNeuron()->executeDerivationOnActivationFunction(candidatesNetInputCache[edge->getNextNeuron()][(*currentTeacher->getTeachingLessons())[lessonIndex].get()][time]) * outputSum;
}

void CascadeCorrelationLearningRule::initializeNeuronWeightCalculation(StandardNeuron* neuron, int lessonIndex, int layerIndex, int neuronIndex, int layerCount, int neuronsInLayerCount, ErrorMap_t* errormap)
{
	if (currentMode == OUTPUTNEURONSLEARNINGMODE && layerIndex == currentNetworkTopology->getNeurons()->size() - 1)
		outputNeuronsBackpropagationLearningRule->initializeNeuronWeightCalculation(neuron, lessonIndex, layerIndex, neuronIndex, layerCount, neuronsInLayerCount, errormap);
}


AbstractActivationOrder* CascadeCorrelationLearningRule::getNewActivationOrder(NeuralNetwork &neuralNetwork)
{
	return new TopologicalOrder();
}

void CascadeCorrelationLearningRule::adjustWeight(Edge* edge, float gradient)
{
	if (currentMode == OUTPUTNEURONSLEARNINGMODE)
		outputNeuronsBackpropagationLearningRule->adjustWeight(edge, gradient);
	else
		candidateUnitsBackpropagationLearningRule->adjustWeight(edge, gradient);

}

void CascadeCorrelationLearningRule::printDebugOutput()
{
	if (currentMode == OUTPUTNEURONSLEARNINGMODE)
		outputNeuronsBackpropagationLearningRule->printDebugOutput();
	else
		candidateUnitsBackpropagationLearningRule->printDebugOutput();
	/*if (currentMode == CANDIDATEUNITLEARNINGMODE)
		std::cout << "cor :" << std::fixed << std::setprecision(10) << getTotalCorrelation() << " ";*/
}

float CascadeCorrelationLearningRule::getTotalCorrelationOfUnit(StandardNeuron* candidateUnit)
{
	float totalCorrelation = 0;

	for (std::map<StandardNeuron*, float>::iterator correlation = correlations[candidateUnit].begin(); correlation != correlations[candidateUnit].end(); correlation++)
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
	outputNeuronsBackpropagationLearningRule->initializeTry(neuralNetwork, teacher);	
	candidateUnitsBackpropagationLearningRule->initializeTry(neuralNetwork, teacher);

	currentMode = OUTPUTNEURONSLEARNINGMODE;
}

void CascadeCorrelationLearningRule::initializeTeachingLesson(NeuralNetwork &neuralNetwork, AbstractTeachingLesson &teachingLesson)
{
	
}

void CascadeCorrelationLearningRule::calcAllCorrelations(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder, bool calcErrorFactor)
{	
	std::map<AbstractTeachingLesson*, std::unique_ptr<ErrorMap_t>> errorMaps;
	for (std::vector<std::unique_ptr<AbstractTeachingLesson>>::iterator teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++)
	{
		if (correlations.empty())
		{
			neuronOutputCache[teachingLesson->get()].resize((*teachingLesson)->getMaxTimeStep() + 1);
			std::vector<std::map<AbstractNeuron*, float>> neuronInputs((*teachingLesson)->getMaxTimeStep() + 1);
			errorMaps[teachingLesson->get()] = (*teachingLesson)->getErrormap(neuralNetwork, activationOrder, 0 , 0, &neuronOutputCache[teachingLesson->get()], &neuronInputs);
						
			for (std::vector<StandardNeuron*>::iterator currentCandidateUnit = currentCandidateUnits.begin(); currentCandidateUnit != currentCandidateUnits.end(); currentCandidateUnit++)
			{				
				for (int t = 0; t <= (*teachingLesson)->getMaxTimeStep(); t++)
				{
					candidatesNetInputCache[*currentCandidateUnit][teachingLesson->get()][t] = neuronInputs[t][*currentCandidateUnit];
				}
			}
		}
		else
		{
			for (std::vector<StandardNeuron*>::iterator currentCandidateUnit = currentCandidateUnits.begin(); currentCandidateUnit != currentCandidateUnits.end(); currentCandidateUnit++)
			{
				for (int t = 0; t <= (*teachingLesson)->getMaxTimeStep(); t++)
				{
					(*currentCandidateUnit)->refreshNetInput(&neuronOutputCache[teachingLesson->get()][t]);
					(*currentCandidateUnit)->refreshActivation();
					neuronOutputCache[teachingLesson->get()][t][*currentCandidateUnit] = (*currentCandidateUnit)->getActivation();	
					candidatesNetInputCache[*currentCandidateUnit][teachingLesson->get()][t] = (*currentCandidateUnit)->getNetInput();	
				}
			}
			
			if (calcErrorFactor)
			{
				NeuralNetworkIO<float> outputVector;
				for (std::vector<StandardNeuron*>::iterator outputNeuron = currentNetworkTopology->getOutputNeurons()->begin(); outputNeuron != currentNetworkTopology->getOutputNeurons()->end(); outputNeuron++)
				{
					for (int t = 0; t <= (*teachingLesson)->getMaxTimeStep(); t++)
					{
						(*outputNeuron)->refreshNetInput(&neuronOutputCache[teachingLesson->get()][t]);
						(*outputNeuron)->refreshActivation();
						outputVector[t].push_back((*outputNeuron)->getActivation());
					}
				}
				errorMaps[teachingLesson->get()] = (*teachingLesson)->getErrormapFromOutputVector(outputVector, neuralNetwork);
			}
		}		
	}

	std::map<StandardNeuron*, float> meanCandidateOutput;
	for (std::vector<StandardNeuron*>::iterator currentCandidateUnit = currentCandidateUnits.begin(); currentCandidateUnit != currentCandidateUnits.end(); currentCandidateUnit++)
	{		
		for (std::vector<std::unique_ptr<AbstractTeachingLesson>>::iterator teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++)
		{
			meanCandidateOutput[*currentCandidateUnit] += neuronOutputCache[teachingLesson->get()].back()[*currentCandidateUnit];
		}
		meanCandidateOutput[*currentCandidateUnit] /= teacher.getTeachingLessons()->size();	
	}

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

		for (std::vector<StandardNeuron*>::iterator currentCandidateUnit = currentCandidateUnits.begin(); currentCandidateUnit != currentCandidateUnits.end(); currentCandidateUnit++)
		{
			correlations[*currentCandidateUnit][*outputNeuron] = 0;
		}

		for (std::vector<std::unique_ptr<AbstractTeachingLesson>>::iterator teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++)
		{
			if (calcErrorFactor)
			{
				errorFactors[teachingLesson->get()][*outputNeuron] = ((*errorMaps[teachingLesson->get()]).rbegin()->second[*outputNeuron] - meanErrorValue);
			}

			for (std::vector<StandardNeuron*>::iterator currentCandidateUnit = currentCandidateUnits.begin(); currentCandidateUnit != currentCandidateUnits.end(); currentCandidateUnit++)
			{
				correlations[*currentCandidateUnit][*outputNeuron] += (neuronOutputCache[teachingLesson->get()].back()[*currentCandidateUnit] - meanCandidateOutput[*currentCandidateUnit]) * errorFactors[teachingLesson->get()][*outputNeuron];
			}
		}
	}
}

void CascadeCorrelationLearningRule::initializeIteration(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder) 
{
	if ((getOptions()->addNeuronAfterIterationInterval != 0 && iteration % getOptions()->addNeuronAfterIterationInterval == 0) || (getOptions()->addNeuronAfterLearningHasStopped && (currentMode == OUTPUTNEURONSLEARNINGMODE ? outputNeuronsBackpropagationLearningRule->learningHasStopped() : candidateUnitsBackpropagationLearningRule->learningHasStopped())))
	{
		if (currentMode == OUTPUTNEURONSLEARNINGMODE)
		{
			currentMode = CANDIDATEUNITLEARNINGMODE;
			int newLayerIndex = currentNetworkTopology->getNeurons()->size();
			currentNetworkTopology->addNewLayer(newLayerIndex, 0);

			correlations.clear();
			candidatesNetInputCache.clear();

			for (std::vector<StandardNeuron*>::iterator currentCandidateUnit = currentCandidateUnits.begin(); currentCandidateUnit != currentCandidateUnits.end(); currentCandidateUnit++)
			{
				*currentCandidateUnit = static_cast<StandardNeuron*>(currentNetworkTopology->addNeuronIntoLayer(newLayerIndex, true, true));
				(*currentCandidateUnit)->addNextNeuron(*currentCandidateUnit, 1);
				for (std::list<Edge*>::iterator edge = (*currentCandidateUnit)->getEfferentEdges()->begin(); edge != (*currentCandidateUnit)->getEfferentEdges()->end(); edge++)
				{
					(*edge)->setWeight(0);
				}
				for (std::list<Edge*>::iterator edge = (*currentCandidateUnit)->getAfferentEdges()->begin(); edge != (*currentCandidateUnit)->getAfferentEdges()->end(); edge++)
				{
					(*edge)->randomizeWeight(options->minRandomWeightValue, options->maxRandomWeightValue);
				}

				for (std::vector<std::unique_ptr<AbstractTeachingLesson>>::iterator teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++)
				{
					candidatesNetInputCache[*currentCandidateUnit][teachingLesson->get()].resize((*teachingLesson)->getMaxTimeStep() + 1);
				}
			}

			calcAllCorrelations(neuralNetwork, teacher, activationOrder, true);

			std::cout << "Adds a new neuron and starts to train it:" << std::endl;
		}
		else if (currentMode == CANDIDATEUNITLEARNINGMODE)
		{
			currentMode = OUTPUTNEURONSLEARNINGMODE;

			float maxCorrelation = 0;
			StandardNeuron* bestCandidateUnit = NULL;
			for (std::vector<StandardNeuron*>::iterator currentCandidateUnit = currentCandidateUnits.begin(); currentCandidateUnit != currentCandidateUnits.end(); currentCandidateUnit++)
			{
				if (bestCandidateUnit == NULL || maxCorrelation < getTotalCorrelationOfUnit(*currentCandidateUnit))
				{
					bestCandidateUnit = *currentCandidateUnit;
					maxCorrelation = getTotalCorrelationOfUnit(*currentCandidateUnit);
				}
			}

			for (std::vector<StandardNeuron*>::iterator currentCandidateUnit = currentCandidateUnits.begin(); currentCandidateUnit != currentCandidateUnits.end(); currentCandidateUnit++)
			{
				if (bestCandidateUnit != *currentCandidateUnit)
					currentNetworkTopology->removeNeuronFromLayer(currentNetworkTopology->getNeurons()->size() - 2, *currentCandidateUnit);
			}

			std::cout << "Stops neuron training and starts the training of the output layer:" << std::endl;
		}
		// If used, initialize the learning rate helper
		if (candidateUnitsBackpropagationLearningRule->getOptions()->resilientLearningRate)
			candidateUnitsBackpropagationLearningRule->resilientLearningRateHelper->initialize(neuralNetwork);
		if (outputNeuronsBackpropagationLearningRule->getOptions()->resilientLearningRate)
			outputNeuronsBackpropagationLearningRule->resilientLearningRateHelper->initialize(neuralNetwork);
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