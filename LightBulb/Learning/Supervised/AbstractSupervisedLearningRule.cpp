// Includes
#include "Learning/Supervised/AbstractSupervisedLearningRule.hpp"
#include "NeuralNetwork/AbstractNeuralNetwork.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
#include "Teaching/Teacher.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
// Library includes
#include <iomanip>
#include <vector>
#include "Learning/Supervised/SupervisedLearningResult.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"

AbstractSupervisedLearningRule::AbstractSupervisedLearningRule(AbstractSupervisedLearningRuleOptions& options_)
	: AbstractLearningRule(new AbstractSupervisedLearningRuleOptions(options_))
{
	validateOptions();
}

AbstractSupervisedLearningRule::AbstractSupervisedLearningRule(AbstractSupervisedLearningRuleOptions* options_)
	: AbstractLearningRule(options_)
{
	validateOptions();
}

void AbstractSupervisedLearningRule::validateOptions()
{
	// Check if all given options are correct
	if (getOptions()->maxTotalErrorValue <= getOptions()->totalErrorGoal)
		throw std::invalid_argument("The maxTotalErrorValue has to be greater than the totalErrorGoal");
}

AbstractSupervisedLearningRuleOptions* AbstractSupervisedLearningRule::getOptions()
{
	return static_cast<AbstractSupervisedLearningRuleOptions*>(options.get());
}

void AbstractSupervisedLearningRule::initializeStartLearningAlgoritm()
{
	getOptions()->teacher = initializeTeacher(*getOptions()->teacher);
	getOptions()->neuralNetwork = initializeNeuralNetwork(*getOptions()->neuralNetwork);

	currentActivationOrder.reset(new TopologicalOrder());

	totalError = 0;
}

bool AbstractSupervisedLearningRule::doIteration()
{
	if (!options->disabledDataSets[options->dataSetsPrefix + DATA_SET_TRAINING_ERROR])
		learningState->addData(options->dataSetsPrefix + DATA_SET_TRAINING_ERROR, totalError);

	// If its not the first iteration and the learning process has stopped, skip that try
	if (learningState->iterations > 1 && learningHasStopped())
	{
		// If debug is enabled, print a short debug info
		log("Skip that try (learning has stopped with totalError: " + std::to_string(totalError) + ")", LL_MEDIUM);
		return false;
	}

	// If we had more iterations than minIterationsPerTry and the totalError is still greater than the maxTotalErrorValue, skip that try
	if (learningState->iterations > getOptions()->minIterationsPerTry && totalError > getOptions()->maxTotalErrorValue)
	{
		// If debug is enabled, print a short debug info
		log("Skip that try (totalError: " + std::to_string(totalError) + " > " + std::to_string(getOptions()->maxTotalErrorValue) + ")", LL_MEDIUM);
		return false;
	}

	// If debug is enabled, print every n-th iteration a short debug info
	if (learningState->iterations % options->debugOutputInterval == 0)
	{
		log("TotalError: " + std::to_string(totalError) + " Iteration: " + std::to_string(learningState->iterations) + " " + printDebugOutput(), LL_LOW);
	}

	// If offlineLearning is activated, reset the offlineLearningGradients
	if (getOptions()->offlineLearning)
	{
		offlineLearningWeights = *getCurrentNetworkTopology()->getWeights();
		// Adjust all hidden/output layers except 
		for (int l = 0; l < offlineLearningWeights.size(); l++)
		{
			offlineLearningWeights[l].setZero();
		}
	}

	// Do some work before every iteration
	initializeIteration();

	// Go through every TeachingLesson
	int lessonIndex = 0;
	for (auto teachingLesson = getOptions()->teacher->getTeachingLessons()->begin(); teachingLesson != getOptions()->teacher->getTeachingLessons()->end(); teachingLesson++, lessonIndex++)
	{
		// Do some work before every teaching lesson
		initializeTeachingLesson(**teachingLesson);

		// Do some work before all weights will be adjusted
		if (!getOptions()->offlineLearning)
			initializeAllWeightAdjustments();

		// Set start and time counter to default values
		int nextStartTime = -1;
		int nextTimeStepCount = -1;

		// While the learning rule wants do some calculation with the current teaching lesson
		while (configureNextErroMapCalculation(&nextStartTime, &nextTimeStepCount, **teachingLesson))
		{
			// Calculate the errormap and also fill - if needed - the output and netInput values map
			std::unique_ptr<ErrorMap_t> errormap = (*teachingLesson)->getErrormap(*getOptions()->neuralNetwork, *currentActivationOrder, NULL, NULL, getOptions()->clipError/*, nextStartTime, nextTimeStepCount,  getOutputValuesInTime(), getNetInputValuesInTime()*/);

			std::vector<Eigen::MatrixXd> deltaWeight = calculateDeltaWeight(*teachingLesson->get(), lessonIndex, errormap.get());

			for (int l = getCurrentNetworkTopology()->getLayerCount() - 1; l > 0; l--)
			{
				// If offline learning is activated, add the weight to the offlineLearningWeight, else adjust the weight right now
				if (getOptions()->offlineLearning)
					offlineLearningWeights[l - 1] += deltaWeight[l - 1];
				else
					offlineLearningWeights[l - 1] = deltaWeight[l - 1];
			}

			// If offline learning is activated, adjust all weights
			if (!getOptions()->offlineLearning)
			{
				// Adjust the every hidden/output layer
				for (int l = getCurrentNetworkTopology()->getLayerCount() - 1; l > 0; l--)
				{
					// Adjust the weight depending on the sum of all calculated gradients
					adjustWeights(l, offlineLearningWeights[l - 1]);
				}
			}

		}

		// Do some work after all weights were adjusted
		if (!getOptions()->offlineLearning)
			doCalculationAfterAllWeightAdjustments();
	}

	// If offline learning is activated, adjust all weights
	if (getOptions()->offlineLearning)
	{
		// Do some work before all weights will be adjusted
		initializeAllWeightAdjustments();

		// Adjust the every hidden/output layer
		for (int l = getCurrentNetworkTopology()->getLayerCount() - 1; l > 0; l--)
		{
			// Adjust the weight depending on the sum of all calculated gradients
			adjustWeights(l, offlineLearningWeights[l - 1]);
		}

		// Do some work after all weights were adjusted
		doCalculationAfterAllWeightAdjustments();
	}

	return true;
}

void AbstractSupervisedLearningRule::initializeResumeLearningAlgoritm()
{
	currentActivationOrder.reset(new TopologicalOrder());
}

void AbstractSupervisedLearningRule::initializeLearningAlgoritm()
{
	//offlineLearningWeights.clear();
	// Create a vector which will contain all weights for offline learning
	offlineLearningWeights.resize(getCurrentNetworkTopology()->getLayerCount());
}

void AbstractSupervisedLearningRule::doCalculationAfterLearningProcess()
{
	if (!options->disabledDataSets[options->dataSetsPrefix + DATA_SET_TRAINING_ERROR])
		learningState->addData(options->dataSetsPrefix + DATA_SET_TRAINING_ERROR, totalError);
}

bool AbstractSupervisedLearningRule::hasLearningSucceeded()
{
	return (totalError <= getOptions()->totalErrorGoal);
}

void AbstractSupervisedLearningRule::rateLearning()
{
	totalError = getOptions()->teacher->getTotalError(*getOptions()->neuralNetwork, *currentActivationOrder);
}

AbstractNetworkTopology* AbstractSupervisedLearningRule::getCurrentNetworkTopology()
{
	return getOptions()->neuralNetwork->getNetworkTopology();
}

AbstractLearningResult* AbstractSupervisedLearningRule::getLearningResult()
{
	SupervisedLearningResult* learningResult = new SupervisedLearningResult();
	fillDefaultResults(learningResult);
	learningResult->quality = totalError;
	learningResult->qualityLabel = "Total error";
	learningResult->trainedNetwork = getOptions()->neuralNetwork;
	
	return learningResult;
}

bool AbstractSupervisedLearningRule::configureNextErroMapCalculation(int* nextStartTime, int* nextTimeStepCount, AbstractTeachingLesson& teachingLesson)
{
	// Per default only calculate every teaching lesson once in all possible timesteps
	if (*nextStartTime != -1)
		return false;
	else
	{
		*nextStartTime = 0;
		*nextTimeStepCount = -1;
		return true;
	}
}

std::vector<std::string> AbstractSupervisedLearningRule::getDataSetLabels()
{
	std::vector<std::string> labels = AbstractLearningRule::getDataSetLabels();
	labels.push_back(options->dataSetsPrefix + DATA_SET_TRAINING_ERROR);
	return labels;
}
