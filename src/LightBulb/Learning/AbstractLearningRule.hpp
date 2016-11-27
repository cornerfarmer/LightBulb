#pragma once

#ifndef _ABSTRACTLEARNINGRULE_H_
#define _ABSTRACTLEARNINGRULE_H_

// Library Includes´
#include <Eigen/Dense>
#include <vector>
#include <memory>
#include <Logging/AbstractLogger.hpp>

// Includes
#include "LearningState.hpp"
#include "Random/AbstractRandomGenerator.hpp"

namespace LightBulb
{
	// Forward declarations
	struct AbstractLearningResult;

	/**
	 * \brief All general options which are the same for all learning rules.
	 */
	struct AbstractLearningRuleOptions
	{
		/**
		 * \brief Sets the maximum iterations per try
		 * \details Default value: 10000 
		 */
		unsigned int maxIterationsPerTry;
		/**
		 * \brief Sets the maximum number of tries
		 * \details Default value: 100
		 */
		unsigned int maxTries;
		/**
		 * \brief The logger which should be used in the learning process.
		 */
		AbstractLogger* logger;
		/**
		 * \brief Determines after how many iterations the training error should be logged.
		 */
		unsigned int debugOutputInterval;
		/**
		 * \brief Determines after how many iterations the data sets should be filled.
		 * \details Default value: 1
		 */
		int dataSaveInterval;
		/**
		 * \brief Contains all dataset labels which should be completely disabled.
		 * \details Default value: empty
		 */
		std::map<std::string, bool> disabledDataSets;
		/**
		 * \brief A string which will be put in front of every dataset label.
		 * \details Default value: ''
		 */
		std::string dataSetsPrefix;
		/**
		 * \brief The starting seed
		 * \details Default value: random
		 */
		int seed;
		/**
		 * \brief Creates the options and fills them with default options.
		 */
		AbstractLearningRuleOptions()
		{
			maxIterationsPerTry = 10000;
			maxTries = 1;
			logger = nullptr;
			debugOutputInterval = 1000;
			dataSaveInterval = 1;
			dataSetsPrefix = "";
			seed = -1;
		}
		virtual ~AbstractLearningRuleOptions() {}
	};

	/**
	 * \brief A learning rule describes a process how to train one or multiple neural networks.
	 */
	class AbstractLearningRule
	{
		template <class Archive>
		friend void serialize(Archive& archive, AbstractLearningRule& learningRule);
	private:
		/**
		 * \brief Is true, if the learning process should pause after the current iteration.
		 */
		bool pauseRequest;
	protected:
		/**
		 * \brief The options which configure the learning rule.
		 */
		std::unique_ptr<AbstractLearningRuleOptions> options;
		/**
		 * \brief Holds the current learning state.
		 */
		std::shared_ptr<LearningState> learningState;
		/**
		 * \brief The random generator which provides all random numbers for the learning process.
		 */
		std::shared_ptr<AbstractRandomGenerator> randomGenerator;
		/**
		 * \brief Executes one iteration.
		 */
		virtual void doIteration() = 0;
		/**
		 * \brief This method will be called before starting the learning algorithm.
		 * \note Is not called when resuming a paused learning process.
		 */
		virtual void initializeStartLearningAlgoritm() {};
		/**
		 * \brief Initialize learning before resuming a paused learning process.
		 */
		virtual void initializeResumeLearningAlgoritm() {};
		/**
		 * \brief Is called before resuming or starting the learning process.
		 */
		virtual void initializeLearningAlgoritm() {};
		/**
		 * \brief Is called at the beginning of every try.
		 */
		virtual void initializeTry() = 0;
		/**
		 * \brief Is called after the learning process has finished.
		 */
		virtual void doCalculationAfterLearningProcess() {};
		/**
		 * \brief Rate the current learning state independently.
		 */
		virtual void rateLearning() {};
		/**
		 * \brief Logs the given message with the configured logger.
		 * \param message The message the log.
		 * \param level The log level of the message.
		 */
		void log(const std::string& message, const LogLevel& level);
		/**
		 * \brief Returns if the learning has succeeded.
		 * \return True, if the learning has been successful.
		 */
		virtual bool hasLearningSucceeded() = 0;
		/**
		* \brief Returns if the try should be skipped.
		* \return True, if the try should be skipped.
		*/
		virtual bool shouldSkipTry() { return false; };
		/**
		 * \brief Returns the learning result.
		 * \return The learning result
		 */
		virtual AbstractLearningResult* getLearningResult() = 0;
		/**
		 * \brief Fills in the default learning result properties.
		 * \param learningResult A pointer to a existing learning result which should be modified.
		 */
		virtual void fillDefaultResults(AbstractLearningResult& learningResult);
		/**
		 * \brief Does learning.
		 * \param resume True, if the learning process just resumes.
		 * \return The result of the learning process.
		 */
		AbstractLearningResult* learn(bool resume);
	public:
		virtual ~AbstractLearningRule() {};
		/**
		 * \brief Creates the learning rule.
		 * \param options_ The options which configure the learning rule.
		 */
		AbstractLearningRule(AbstractLearningRuleOptions* options_);
		/**
		 * \brief Starts the learning from the scratch.
		 * \return The result of the learning process.
		 */
		AbstractLearningResult* start();
		/**
		* \brief Resumes the learning process which was paused before.
		* \return The result of the learning process.
		*/
		AbstractLearningResult* resume();
		/**
		 * \brief Tell the learning process to pause after the next iteration.
		 */
		void sendPauseRequest();
		/**
		 * \brief Can be used to change the logger after creating the learning rule.
		 * \param logger The new logger.
		 */
		virtual void setLogger(AbstractLogger& logger);
		/**
		 * \brief Returns the current learning state.
		 * \return The current learning state.
		 */
		LearningState& getLearningState();
		/**
		 * \brief Returns a vector of all data set labels which are available in the learning state of this learning rule.
		 * \return The labels of all available data sets.
		 */
		virtual std::vector<std::string> getDataSetLabels() const;
		/**
		 * \brief Returns the starting seed of the random generator which is used by the learning rule.
		 * \return The seed.
		 */
		int getSeed() const;
	};
}

#include "IO/AbstractLearningRuleIO.hpp"

#endif


