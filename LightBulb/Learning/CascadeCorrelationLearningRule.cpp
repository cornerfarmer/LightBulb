#include "Learning\CascadeCorrelationLearningRule.hpp"
#include "Teaching\Teacher.hpp"
#include "ActivationOrder\TopologicalOrder.hpp"
#include "Teaching\AbstractTeachingLesson.hpp"
#include "NeuralNetwork\NeuralNetwork.hpp"
#include "NetworkTopology\LayeredNetwork.hpp"
#include "Neuron\AbstractNeuron.hpp"
#include "NetworkTopology\AbstractNetworkTopology.hpp"
#include "Neuron\StandardNeuron.hpp"
#include "Neuron\Edge.hpp"
#include "NetworkTopology\CascadeCorrelationNetwork.hpp"
#include <algorithm>

CascadeCorrelationLearningRule::CascadeCorrelationLearningRule(CascadeCorrelationLearningRuleOptions& options_) 
	: AbstractLearningRule(new CascadeCorrelationLearningRuleOptions(options_))
{
	// Always use offline learning
	options->offlineLearning = true;
	getOptions()->outputNeuronsLearningRuleOptions.offlineLearning = true;
	getOptions()->candidateUnitsLearningRuleOptions.offlineLearning = true;
	// The learning process only needs one try
	options->maxTries = 1;

	// Create new BackpropagationLearningRules
	outputNeuronsBackpropagationLearningRule.reset(new TruncatedBackpropagationThroughTimeLearningRule(getOptions()->outputNeuronsLearningRuleOptions));
	candidateUnitsBackpropagationLearningRule.reset(new BackpropagationLearningRule(getOptions()->candidateUnitsLearningRuleOptions));
}


void CascadeCorrelationLearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
{
	currentNetworkTopology = dynamic_cast<CascadeCorrelationNetwork*>(neuralNetwork.getNetworkTopology());
	currentTeacher = &teacher;
	outputNeuronsBackpropagationLearningRule->getOptions()->maxTimeSteps = teacher.getMaxTimeStep() + 1;
	// Initialize the BackpropagationLearningRules
	outputNeuronsBackpropagationLearningRule->initializeLearningAlgoritm(neuralNetwork, teacher, activationOrder);
	candidateUnitsBackpropagationLearningRule->initializeLearningAlgoritm(neuralNetwork, teacher, activationOrder);
	// Adjust the candidate units vector
	currentCandidateUnits.resize(getOptions()->candidateUnitCount);
}


double CascadeCorrelationLearningRule::calculateDeltaWeightFromEdge(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, Edge& edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, ErrorMap_t* errormap)
{
	// If the learning rule is in output neurons learning mode, let the backpropagation learning rule do the work
	if (currentMode == OUTPUTNEURONSLEARNINGMODE && layerIndex == currentNetworkTopology->getNeurons()->size() - 1)	
	{
		double gradient = 0;

		gradient += outputNeuronsBackpropagationLearningRule->calculateDeltaWeightFromEdge(lesson, layer, neuron, edge, lessonIndex, layerIndex, neuronIndex, edgeIndex, errormap);

		return gradient;
	}
	else if (currentMode == CANDIDATEUNITLEARNINGMODE && std::find(currentCandidateUnits.begin(), currentCandidateUnits.end(), edge.getNextNeuron()) != currentCandidateUnits.end())
	{
		// If we are in candidate unit learning mode and the current edge points to a candidate unit
		double gradient = 0;
	
		for (auto errorFactor = errorFactors[&lesson].begin(); errorFactor != errorFactors[&lesson].end(); errorFactor++)
		{
			// Go through all output neurons  
			for (auto outputNeuron = currentNetworkTopology->getOutputNeurons()->begin(); outputNeuron != currentNetworkTopology->getOutputNeurons()->end(); outputNeuron++)
			{
				// Add to the gradient: sign(correlation) * outputgradient * errorfac
				gradient += (correlations[edge.getNextNeuron()][*outputNeuron] > 0 ? 1 : (correlations[edge.getNextNeuron()][*outputNeuron] < 0 ? -1 : 0)) * getOutputGradient(&edge, errorFactor->first, &lesson) * errorFactor->second[*outputNeuron];
			}			
		}

		// Return the negativ gradient (we want to a gradient ascent not a descent)
		return -gradient / 6;
	}
	else // If the current neuron does not have to be trained now, return zero
		return 0;
}

double CascadeCorrelationLearningRule::calcOutputGradient(Edge* edge, int time, AbstractTeachingLesson* lesson)
{
	double outputSum = 0;
	// Calculate the output gradient of the current time step
	if (edge->getNextNeuron() != edge->getPrevNeuron() || time != 0)
		outputSum += neuronOutputCache[lesson][edge->getNextNeuron() != edge->getPrevNeuron() ? time : time - 1][edge->getPrevNeuron()];
	// Calculate the output gradient of the previous (only needed for recurrent mode)
	if (getOptions()->recurrent && time != 0)
		outputSum += getOutputGradient(edge, time - 1, lesson) * edge->getNextNeuron()->getEfferentEdges()->back()->getWeight();
	// Calculate the whole gradient: activationFunction'(netInput) * outputSum
	return edge->getNextNeuron()->executeDerivationOnActivationFunction(candidatesNetInputCache[edge->getNextNeuron()][lesson][time]) * outputSum;
}

double CascadeCorrelationLearningRule::getOutputGradientCached(Edge* edge, int time, AbstractTeachingLesson* lesson)
{
	if (!outputGradientCache[lesson][edge][time].second)
	{
		outputGradientCache[lesson][edge][time].first = calcOutputGradient(edge, time, lesson);
		outputGradientCache[lesson][edge][time].second = true;
	}
	return outputGradientCache[lesson][edge][time].first;
}

double CascadeCorrelationLearningRule::getOutputGradient(Edge* edge, int time, AbstractTeachingLesson* lesson)
{
	if (getOptions()->recurrent)
		return getOutputGradientCached(edge, time, lesson);
	else
		return calcOutputGradient(edge, time, lesson);
}

void CascadeCorrelationLearningRule::initializeNeuronWeightCalculation(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, int lessonIndex, int layerIndex, int neuronIndex, ErrorMap_t* errormap)
{
	// If we are in output neurons learning mode, let the backpropagation learning rule do some work
	if (currentMode == OUTPUTNEURONSLEARNINGMODE && layerIndex == currentNetworkTopology->getNeurons()->size() - 1)
		outputNeuronsBackpropagationLearningRule->initializeNeuronWeightCalculation(lesson, layer, neuron, lessonIndex, layerIndex, neuronIndex, errormap);
}


AbstractActivationOrder* CascadeCorrelationLearningRule::getNewActivationOrder(NeuralNetwork &neuralNetwork)
{
	return new TopologicalOrder();
}

void CascadeCorrelationLearningRule::adjustWeight(Edge* edge, double gradient)
{
	// Let the backpropagation learning rules adjust the weight
	if (currentMode == OUTPUTNEURONSLEARNINGMODE)
		outputNeuronsBackpropagationLearningRule->adjustWeight(edge, gradient);
	else
		candidateUnitsBackpropagationLearningRule->adjustWeight(edge, gradient);

}

void CascadeCorrelationLearningRule::printDebugOutput()
{
	// Let the backpropagation learning rules print the debug output 
	if (currentMode == OUTPUTNEURONSLEARNINGMODE)
		outputNeuronsBackpropagationLearningRule->printDebugOutput();
	else
		candidateUnitsBackpropagationLearningRule->printDebugOutput();
	/*if (currentMode == CANDIDATEUNITLEARNINGMODE)
		std::cout << "cor :" << std::fixed << std::setprecision(10) << getTotalCorrelation() << " ";*/
}

double CascadeCorrelationLearningRule::getTotalCorrelationOfUnit(StandardNeuron* candidateUnit)
{
	double totalCorrelation = 0;
	// Go through all correlation values of the given candidate unit and add it
	for (auto correlation = correlations[candidateUnit].begin(); correlation != correlations[candidateUnit].end(); correlation++)
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
	// Initialize the backpropagation learning rules
	outputNeuronsBackpropagationLearningRule->initializeTry(neuralNetwork, teacher);	
	candidateUnitsBackpropagationLearningRule->initializeTry(neuralNetwork, teacher);

	outputGradientCache.clear();

	// Set the mode to output neurons learning mode at the beginning
	currentMode = OUTPUTNEURONSLEARNINGMODE;
}

void CascadeCorrelationLearningRule::initializeTeachingLesson(NeuralNetwork &neuralNetwork, AbstractTeachingLesson &teachingLesson)
{
	if (currentMode == OUTPUTNEURONSLEARNINGMODE) 
		outputNeuronsBackpropagationLearningRule->initializeTeachingLesson(neuralNetwork, teachingLesson);
}

void CascadeCorrelationLearningRule::calcAllCorrelations(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder, bool calcErrorFactor)
{	
	// Create a map which should hold all errormaps of all teaching lessons (only needed if this is the first calculation)
	std::map<AbstractTeachingLesson*, std::unique_ptr<ErrorMap_t>> errorMaps;
	// Go through all teaching lessons
	for (auto teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++)
	{
		// If this is the first calculation
		if (correlations.empty())
		{
			// Resize the cache to be able hold all values in all timesteps
			neuronOutputCache[teachingLesson->get()].resize((*teachingLesson)->getMaxTimeStep() + 1);
			// Create temporary vector for all neuronInputs
			std::vector<std::map<AbstractNeuron*, double>> neuronInputs((*teachingLesson)->getMaxTimeStep() + 1);
			// Calculate the error map for the current teaching lesson
			errorMaps[teachingLesson->get()] = (*teachingLesson)->getErrormap(neuralNetwork, activationOrder, 0 , 0, &neuronOutputCache[teachingLesson->get()], &neuronInputs);
						
			// Go through all candidate units and save their netInputs into the candidatesNetInputCache
			for (auto currentCandidateUnit = currentCandidateUnits.begin(); currentCandidateUnit != currentCandidateUnits.end(); currentCandidateUnit++)
			{				
				for (int t = 0; t <= (*teachingLesson)->getMaxTimeStep(); t++)
				{
					candidatesNetInputCache[*currentCandidateUnit][teachingLesson->get()][t] = neuronInputs[t][*currentCandidateUnit];
				}
			}
		}
		else
		{
			// Go through all candidate units
			for (auto currentCandidateUnit = currentCandidateUnits.begin(); currentCandidateUnit != currentCandidateUnits.end(); currentCandidateUnit++)
			{
				// Reset the activation of this candidate unit
				(*currentCandidateUnit)->resetActivation();
				for (int t = 0; t <= (*teachingLesson)->getMaxTimeStep(); t++)
				{
					// Erase the cache for this unit (So self referencing edges will not used the old cached value)
					neuronOutputCache[teachingLesson->get()][t].erase(*currentCandidateUnit);
					// Refresh the input of this candidate unit from the output cache
					(*currentCandidateUnit)->refreshNetInput(&neuronOutputCache[teachingLesson->get()][t]);
					// Refresh the activation
					(*currentCandidateUnit)->refreshActivation();
					// Put the calculated activation into the cache
					neuronOutputCache[teachingLesson->get()][t][*currentCandidateUnit] = (*currentCandidateUnit)->getActivation();	
					// Put the calculated netInput into the cache
					candidatesNetInputCache[*currentCandidateUnit][teachingLesson->get()][t] = (*currentCandidateUnit)->getNetInput();	
				}
			}
			
			// If the error factors should be recalculated
			if (calcErrorFactor)
			{
				NeuralNetworkIO<double> outputVector;
				// Go through all output neurons
				for (auto outputNeuron = currentNetworkTopology->getOutputNeurons()->begin(); outputNeuron != currentNetworkTopology->getOutputNeurons()->end(); outputNeuron++)
				{
					for (int t = 0; t <= (*teachingLesson)->getMaxTimeStep(); t++)
					{
						// Refresh the activation and the netInput of the current output neuron
						(*outputNeuron)->refreshNetInput(&neuronOutputCache[teachingLesson->get()][t]);
						(*outputNeuron)->refreshActivation();
						outputVector[t].push_back((*outputNeuron)->getActivation());
					}
				}
				// Recalculate the errorMap from the calculated output values
				errorMaps[teachingLesson->get()] = (*teachingLesson)->getErrormapFromOutputVector(outputVector, neuralNetwork);
			}
		}		
	}

	std::map<StandardNeuron*, double> meanCandidateOutput;
	// Go through all candidate units
	for (auto currentCandidateUnit = currentCandidateUnits.begin(); currentCandidateUnit != currentCandidateUnits.end(); currentCandidateUnit++)
	{		
		// Go through all teaching lessons
		for (auto teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++)
		{
			// Add the output of the candidate unit to the sum
			meanCandidateOutput[*currentCandidateUnit] += neuronOutputCache[teachingLesson->get()].back()[*currentCandidateUnit];
		}
		// Divide the candidate ouput´sum through the value count to get the mean value
		meanCandidateOutput[*currentCandidateUnit] /= teacher.getTeachingLessons()->size();	
	}

	// Go through all output neuons
	for (auto outputNeuron = currentNetworkTopology->getOutputNeurons()->begin(); outputNeuron != currentNetworkTopology->getOutputNeurons()->end(); outputNeuron++)
	{
		double meanErrorValue = 0;
		// If we should recalculate the error factors
		if (calcErrorFactor)
		{
			int errorValuesCounter = 0;
			// Recalculate the mean error value from all recalculated error maps
			for (auto teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++)
			{
				for (auto errormapTimesteps = errorMaps[teachingLesson->get()]->begin(); errormapTimesteps != errorMaps[teachingLesson->get()]->end(); errormapTimesteps++)
				{
					meanErrorValue += errormapTimesteps->second[*outputNeuron];
					errorValuesCounter++;
				}
			}			
			meanErrorValue /= errorValuesCounter;				
		}

		// Reset all correlation values
		for (auto currentCandidateUnit = currentCandidateUnits.begin(); currentCandidateUnit != currentCandidateUnits.end(); currentCandidateUnit++)
		{
			correlations[*currentCandidateUnit][*outputNeuron] = 0;
		}

		// Go through all teaching lessons
		for (auto teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++)
		{
			// If we should recalculate the error factors
			if (calcErrorFactor)
			{
				for (auto errormapTimesteps = errorMaps[teachingLesson->get()]->begin(); errormapTimesteps != errorMaps[teachingLesson->get()]->end(); errormapTimesteps++)
				{
					// Recalculate the error factor: errorValue - meanErrorValue
					errorFactors[teachingLesson->get()][errormapTimesteps->first][*outputNeuron] = errormapTimesteps->second[*outputNeuron] - meanErrorValue;
				}
			}
			// Go through allo candidate units
			for (auto currentCandidateUnit = currentCandidateUnits.begin(); currentCandidateUnit != currentCandidateUnits.end(); currentCandidateUnit++)
			{
				for (auto errorFactor = errorFactors[teachingLesson->get()].begin(); errorFactor != errorFactors[teachingLesson->get()].end(); errorFactor++)
				{
					// Recalculate the correlation: (output - meanOutput) * errorFac
					correlations[*currentCandidateUnit][*outputNeuron] += (neuronOutputCache[teachingLesson->get()][errorFactor->first][*currentCandidateUnit] - meanCandidateOutput[*currentCandidateUnit]) * errorFactor->second[*outputNeuron];
				}
			}
		}
	}
}

void CascadeCorrelationLearningRule::initializeIteration(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder) 
{
	// If the n-th iteration has been reached or the learning has stopped
	if ((getOptions()->addNeuronAfterIterationInterval != 0 && iteration % getOptions()->addNeuronAfterIterationInterval == 0) || (getOptions()->addNeuronAfterLearningHasStopped && (currentMode == OUTPUTNEURONSLEARNINGMODE ? outputNeuronsBackpropagationLearningRule->learningHasStopped() : candidateUnitsBackpropagationLearningRule->learningHasStopped())))
	{
		// If the current mode was output learning
		if (currentMode == OUTPUTNEURONSLEARNINGMODE)
		{
			// Switch to candidate unti learning
			currentMode = CANDIDATEUNITLEARNINGMODE;
			// The new layer index will be the (hidden + output) layer count
			int newLayerIndex = currentNetworkTopology->getNeurons()->size();
			// Add the new layer
			currentNetworkTopology->addNewLayer(newLayerIndex, 0);

			// Clear the caches
			correlations.clear();
			candidatesNetInputCache.clear();

			// Go through all candidate units
			for (auto currentCandidateUnit = currentCandidateUnits.begin(); currentCandidateUnit != currentCandidateUnits.end(); currentCandidateUnit++)
			{
				// Create a new candidate unit in the new layer
				*currentCandidateUnit = static_cast<StandardNeuron*>(currentNetworkTopology->addNeuronIntoLayer(newLayerIndex, true, true));
				// If the network should be recurrent add a self referencing edge
				if (getOptions()->recurrent)
					(*currentCandidateUnit)->addNextNeuron(*currentCandidateUnit, 1);
				// Go through allo efferent edges and set them to zero, so the candidate unit is at first not connected with the output
				for (auto edge = (*currentCandidateUnit)->getEfferentEdges()->begin(); edge != (*currentCandidateUnit)->getEfferentEdges()->end(); edge++)
				{
					(*edge)->setWeight(0);
				}
				// Go through all afferent edges and randomize them, because they will now be trained
				for (auto edge = (*currentCandidateUnit)->getAfferentEdges()->begin(); edge != (*currentCandidateUnit)->getAfferentEdges()->end(); edge++)
				{
					(*edge)->randomizeWeight(options->minRandomWeightValue, options->maxRandomWeightValue);
				}

				// Adjust the netInput caches
				for (auto teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++)
				{
					candidatesNetInputCache[*currentCandidateUnit][teachingLesson->get()].resize((*teachingLesson)->getMaxTimeStep() + 1);
				}
			}
			// Calc the new correlations
			calcAllCorrelations(neuralNetwork, teacher, activationOrder, true);

			std::cout << "Adds " << newLayerIndex << ". new neuron and starts to train it:" << std::endl;
		}
		else if (currentMode == CANDIDATEUNITLEARNINGMODE)
		{
			// If the current mode was candidate unit learning, switch to output neuron learning
			currentMode = OUTPUTNEURONSLEARNINGMODE;

			// Determine the candidate unit with the biggest correlation
			double maxCorrelation = 0;
			StandardNeuron* bestCandidateUnit = NULL;
			for (auto currentCandidateUnit = currentCandidateUnits.begin(); currentCandidateUnit != currentCandidateUnits.end(); currentCandidateUnit++)
			{
				if (bestCandidateUnit == NULL || maxCorrelation < getTotalCorrelationOfUnit(*currentCandidateUnit))
				{
					bestCandidateUnit = *currentCandidateUnit;
					maxCorrelation = getTotalCorrelationOfUnit(*currentCandidateUnit);
				}
			}

			// Remove all candidate units except the best one with the biggest correlation
			for (auto currentCandidateUnit = currentCandidateUnits.begin(); currentCandidateUnit != currentCandidateUnits.end(); currentCandidateUnit++)
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
		outputNeuronsBackpropagationLearningRule->initializeLearningAlgoritm(neuralNetwork, teacher, activationOrder);
	}
	else if (currentMode == CANDIDATEUNITLEARNINGMODE)
	{
		// If we are not switching the mode and the current mode is candidate unit learning, recalculate the correlations
		calcAllCorrelations(neuralNetwork, teacher, activationOrder, false);

		for (auto cacheOfLesson = outputGradientCache.begin(); cacheOfLesson != outputGradientCache.end(); cacheOfLesson++)
		{
			for (auto cacheOfEdge = cacheOfLesson->second.begin(); cacheOfEdge != cacheOfLesson->second.end(); cacheOfEdge++)
			{
				for (auto cacheOfTimestep = cacheOfEdge->second.begin(); cacheOfTimestep != cacheOfEdge->second.end(); cacheOfTimestep++)
				{
					cacheOfTimestep->second.second = false;
				}
			}
		}
	}	
}

bool CascadeCorrelationLearningRule::configureNextErroMapCalculation(int* nextStartTime, int* nextTimeStepCount, AbstractTeachingLesson& teachingLesson)
{
	// Only do one calculation per teaching lesson
	if (*nextStartTime != -1)
		return false;
	else
	{
		// Do not calculate anything. We do that inside the correaltion calculation
		if (currentMode == CANDIDATEUNITLEARNINGMODE) 
			*nextTimeStepCount = -1;
		else
			*nextTimeStepCount = 0;
		*nextStartTime = 0;		
		return true;
	}
}

std::vector<std::map<AbstractNeuron*, double>>* CascadeCorrelationLearningRule::getOutputValuesInTime()
{
	if (currentMode == OUTPUTNEURONSLEARNINGMODE) 
		return outputNeuronsBackpropagationLearningRule->getOutputValuesInTime();
	else
		return NULL;
}

std::vector<std::map<AbstractNeuron*, double>>* CascadeCorrelationLearningRule::getNetInputValuesInTime()
{
	if (currentMode == OUTPUTNEURONSLEARNINGMODE) 
		return outputNeuronsBackpropagationLearningRule->getNetInputValuesInTime();
	else
		return NULL;
}

