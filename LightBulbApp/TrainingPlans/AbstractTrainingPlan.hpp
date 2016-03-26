#pragma once

#ifndef _ABSTRACTTRAININGPLAN_H_
#define _ABSTRACTTRAININGPLAN_H_

// Includes
#include <Event/Observable.hpp>

// Library includes
#include <string>
#include <thread>
#include <vector>

// Forward declarations

class AbstractNeuralNetwork;

enum TrainingPlanState
{
	TP_RUNNING,
	TP_PAUSING,
	TP_PAUSED,
	TP_IDLE
};

enum TrainingPlanEvents
{
	EVT_TP_PAUSED
};

// A techer manages many techingLessons
class AbstractTrainingPlan : public Observable<TrainingPlanEvents, AbstractTrainingPlan>
{
private:
	std::thread thread;
	AbstractTrainingPlan* pattern;
	TrainingPlanState state;
protected:
	AbstractNeuralNetwork* network;
	virtual void run() = 0;
	virtual AbstractTrainingPlan* getCopy() = 0;
	virtual AbstractNeuralNetwork* createNeuralNetwork() = 0;
	virtual void tryToPause() = 0;
	void pausingFinished();
public:
	AbstractTrainingPlan();
	void start(AbstractNeuralNetwork* network = NULL);
	virtual std::string getName() = 0;
	AbstractNeuralNetwork* getNeuralNetwork();
	virtual std::string getDescription() = 0;
	virtual std::string getLearningRateName() = 0;
	std::string getStateAsString();
	AbstractTrainingPlan* getCopyForExecute();
	AbstractTrainingPlan* getTrainingPlanPattern();
	void pause();
	bool isPaused();
	bool isRunning();
	virtual int getRequiredInputSize() = 0;
	virtual int getRequiredOutputSize() = 0;
};

#endif
