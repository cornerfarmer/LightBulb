// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/Learning/Supervised/AbstractSupervisedLearningRule.hpp"
#include "LightBulb/NeuralNetwork/AbstractNeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/Teaching/Teacher.hpp"
#include "LightBulb/Teaching/AbstractTeachingLesson.hpp"
// Library includes
#include <vector>
#include "LightBulb/Learning/Supervised/SupervisedLearningResult.hpp"
#include "LightBulb/ActivationOrder/TopologicalOrder.hpp"
#include "LightBulb/Logging/AbstractLogger.hpp"
#include "LightBulb/Learning/LearningState.hpp"

namespace LightBulb
{
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

	AbstractSupervisedLearningRule::~AbstractSupervisedLearningRule() = default;

	void AbstractSupervisedLearningRule::validateOptions()
	{
		// Check if all given options are correct
		if (getOptions().maxTotalErrorValue <= getOptions().totalErrorGoal)
			throw std::invalid_argument("The maxTotalErrorValue has to be greater than the totalErrorGoal");

		static_cast<AbstractSupervisedLearningRuleOptions&>(*options.get()).teacher->setCalculatorType(options->calculatorType);
	}

	const AbstractSupervisedLearningRuleOptions& AbstractSupervisedLearningRule::getOptions() const
	{
		return static_cast<AbstractSupervisedLearningRuleOptions&>(*options.get());
	}

	void AbstractSupervisedLearningRule::initializeStartLearningAlgoritm()
	{
		initializeTeacher(*getOptions().teacher);
		initializeNeuralNetwork(*getOptions().neuralNetwork);

		currentActivationOrder.reset(new TopologicalOrder());

		totalError = 0;
	}

	bool AbstractSupervisedLearningRule::shouldSkipTry()
	{
		return (learningState->iterations > 1 && learningHasStopped()) || (learningState->iterations > getOptions().minIterationsPerTry && totalError > getOptions().maxTotalErrorValue);
	}

	void AbstractSupervisedLearningRule::doIteration()
	{
		if (!options->disabledDataSets[options->dataSetsPrefix + DATA_SET_TRAINING_ERROR])
			learningState->addData(options->dataSetsPrefix + DATA_SET_TRAINING_ERROR, totalError);

		// If debug is enabled, print every n-th iteration a short debug info
		if (learningState->iterations % options->debugOutputInterval == 0)
		{
			log("TotalError: " + std::to_string(totalError) + " Iteration: " + std::to_string(learningState->iterations), LL_LOW);
		}

		if (getOptions().offlineLearning)
		{
			clearGradient();
		}

		// Do some work before every iteration
		initializeIteration();

		// Go through every TeachingLesson
		int lessonIndex = 0;
		for (auto teachingLesson = getOptions().teacher->getTeachingLessons().begin(); teachingLesson != getOptions().teacher->getTeachingLessons().end(); teachingLesson++, lessonIndex++)
		{
			// Do some work before every teaching lesson
			initializeTeachingLesson(**teachingLesson);

			// Do some work before all weights will be adjusted
			if (!getOptions().offlineLearning)
				initializeAllWeightAdjustments();

			// Set start and time counter to default values
			int nextStartTime = -1;
			int nextTimeStepCount = -1;

			// While the learning rule wants do some calculation with the current teaching lesson
			while (configureNextErroMapCalculation(&nextStartTime, &nextTimeStepCount, **teachingLesson))
			{
				if (!getOptions().offlineLearning)
				{
					clearGradient();
				}

				// Calculate the errorVector and also fill - if needed - the output and netInput values map
				const Vector<>& errorVector = (*teachingLesson)->getErrorVector(*getOptions().neuralNetwork, *currentActivationOrder, getOptions().clipError);

				calculateDeltaWeight(*teachingLesson->get(), lessonIndex, errorVector);

				// If offline learning is activated, adjust all weights
				if (!getOptions().offlineLearning)
				{
					// Adjust the every hidden/output layer
					for (int l = getCurrentNetworkTopology().getLayerCount() - 1; l > 0; l--)
					{
						// Adjust the weight depending on the sum of all calculated gradients
						adjustWeights(l);
					}
				}
			}

			// Do some work after all weights were adjusted
			if (!getOptions().offlineLearning)
				doCalculationAfterAllWeightAdjustments();
		}

		// If offline learning is activated, adjust all weights
		if (getOptions().offlineLearning)
		{
			// Do some work before all weights will be adjusted
			initializeAllWeightAdjustments();

			// Adjust the every hidden/output layer
			for (int l = getCurrentNetworkTopology().getLayerCount() - 1; l > 0; l--)
			{
				// Adjust the weight depending on the sum of all calculated gradients
				adjustWeights(l);
			}

			// Do some work after all weights were adjusted
			doCalculationAfterAllWeightAdjustments();
		}
	}

	void AbstractSupervisedLearningRule::initializeResumeLearningAlgoritm()
	{
		currentActivationOrder.reset(new TopologicalOrder());
	}

	void AbstractSupervisedLearningRule::initializeLearningAlgoritm()
	{

	}

	void AbstractSupervisedLearningRule::doCalculationAfterLearningProcess()
	{
		if (!options->disabledDataSets[options->dataSetsPrefix + DATA_SET_TRAINING_ERROR])
			learningState->addData(options->dataSetsPrefix + DATA_SET_TRAINING_ERROR, totalError);
	}

	bool AbstractSupervisedLearningRule::hasLearningSucceeded()
	{
		return (getOptions().totalErrorGoal != -1 && totalError <= getOptions().totalErrorGoal);
	}

	void AbstractSupervisedLearningRule::rateLearning()
	{
		if (getOptions().totalErrorGoal != -1 && (getOptions().calculatorType == CT_CPU || learningState->iterations % getOptions().totalErrorCalculationInterval == 0)) {
			totalError = getOptions().teacher->getTotalError(*getOptions().neuralNetwork, *currentActivationOrder);
		}
	}

	AbstractNetworkTopology& AbstractSupervisedLearningRule::getCurrentNetworkTopology()
	{
		return getOptions().neuralNetwork->getNetworkTopology();
	}

	AbstractLearningResult* AbstractSupervisedLearningRule::getLearningResult()
	{
		SupervisedLearningResult* learningResult = new SupervisedLearningResult();
		fillDefaultResults(*learningResult);
		learningResult->totalError = totalError;
		learningResult->trainedNetwork = getOptions().neuralNetwork;

		return learningResult;
	}

	bool AbstractSupervisedLearningRule::configureNextErroMapCalculation(int* nextStartTime, int* nextTimeStepCount, const AbstractTeachingLesson& teachingLesson)
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

	std::vector<std::string> AbstractSupervisedLearningRule::getDataSetLabels() const
	{
		std::vector<std::string> labels = AbstractLearningRule::getDataSetLabels();
		labels.push_back(options->dataSetsPrefix + DATA_SET_TRAINING_ERROR);
		return labels;
	}
}
