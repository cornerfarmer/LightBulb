#pragma once

#ifndef _ABSTRACTTRAININGPLAN_H_
#define _ABSTRACTTRAININGPLAN_H_

// Includes
#include <Event/Observable.hpp>

// Library includes
#include <string>
#include <thread>
#include <vector>
#include <cereal/cereal.hpp>

// Forward declarations
class AbstractLogger;
class AbstractNeuralNetwork;

enum TrainingPlanState
{
	TP_RUNNING,
	TP_PAUSING,
	TP_PAUSED,
	TP_IDLE,
	TP_FINISHED
};

enum TrainingPlanEvents
{
	EVT_TP_PAUSED,
	EVT_TP_FINISHED
};

class AbstractTrainingPlan : public LightBulb::Observable<TrainingPlanEvents, AbstractTrainingPlan>
{
	template <class Archive>
	friend void save(Archive& archive, AbstractTrainingPlan const& trainingPlan);
	template <class Archive>
	friend void load(Archive& archive, AbstractTrainingPlan& trainingPlan);
private:
	std::thread thread;
	AbstractTrainingPlan* pattern;
	TrainingPlanState state;
	void runThread(bool initial);
	bool threadShouldBeJoinedBeforeReuse;
protected:
	AbstractNeuralNetwork* network;
	AbstractLogger* logger;
	virtual void run(bool initial) = 0;
	virtual AbstractTrainingPlan* getCopy() = 0;
	virtual AbstractNeuralNetwork* createNeuralNetwork() = 0;
	virtual void tryToPause() = 0;
	void pausingFinished();
	void finished();
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
	bool isPausing();
	bool isRunning();
	virtual void setLogger(AbstractLogger* newLogger);
	virtual int getRequiredInputSize() = 0;
	virtual int getRequiredOutputSize() = 0;
};

#endif
