#pragma once

#ifndef _ABSTRACTLEARNINGRULE_H_
#define _ABSTRACTLEARNINGRULE_H_

// Library Includes´
#include <EigenSrc/Dense>
#include <vector>
#include <memory>
#include <Logging/AbstractLogger.hpp>

// Includes
#include "LearningState.hpp"

// Forward declarations


struct AbstractLearningResult;

struct AbstractLearningRuleOptions
{
	// Sets the maximum iterations per try
	unsigned int maxIterationsPerTry;
	// Sets the maximum number of tries, until the algorithm should abort
	unsigned int maxTries;
	// Enable debug output
	AbstractLogger* logger;
	// Sets the debug output interval
	unsigned int debugOutputInterval;

	int dataSaveInterval;

	AbstractLearningRuleOptions()
	{
		maxIterationsPerTry = 10000;
		maxTries = 100;
		logger = NULL;
		debugOutputInterval = 1000;	
		dataSaveInterval = 1;
	}
	virtual ~AbstractLearningRuleOptions() {}
};



// A LearningRule is used to improve a AbstractNeuralNetwork
class AbstractLearningRule 
{
	template <class Archive>
	friend void serialize(Archive& archive, AbstractLearningRule& learningRule);
private:
	bool pauseRequest;
protected:
	std::unique_ptr<AbstractLearningRuleOptions> options;

	std::shared_ptr<LearningState> learningState;

	virtual bool doIteration() = 0;
	// This method will be called in front of the actual learning algorithm
	virtual void initializeStartLearningAlgoritm() {};

	virtual void initializeResumeLearningAlgoritm() {};

	virtual void initializeLearningAlgoritm() {};
	// This method should do something like randomizing all weight
	virtual void initializeTry() = 0;
	// This method could be used to do something after the learning process
	virtual void doCalculationAfterLearningProcess() {};

	virtual void rateLearning() {};

	void log(std::string message, LogLevel level);

	virtual bool hasLearningSucceeded() = 0;

	virtual AbstractLearningResult* getLearningResult() = 0;

	virtual void fillDefaultResults(AbstractLearningResult* learningResult);

	AbstractLearningResult* learn(bool resume);
public:	
	AbstractLearningRule(AbstractLearningRuleOptions* options_);
	// Execute the learning process on the given AbstractNeuralNetwork
	// If the learning process succeded the method will return true
	AbstractLearningResult* start();

	AbstractLearningResult* resume();

	void sendPauseRequest();
	
	virtual void setLogger(AbstractLogger* logger);

	LearningState* getLearningState();

	virtual std::vector<std::string> getDataSetLabels();
};

#include "IO/AbstractLearningRuleIO.hpp"

#endif


