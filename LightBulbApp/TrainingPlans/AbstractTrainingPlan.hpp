#pragma once

#ifndef _ABSTRACTTRAININGPLAN_H_
#define _ABSTRACTTRAININGPLAN_H_

// Includes
#include <Event/Observable.hpp>
#include <Logging/StorageLogger.hpp>

// Library includes
#include <string>
#include <thread>
#include <vector>
#include <cereal/cereal.hpp>
#include <Windows/AbstractCustomSubAppFactory.hpp>

// Forward declarations
class AbstractLogger;
struct LearningState;

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
	std::vector<std::unique_ptr<AbstractCustomSubAppFactory>> customSubApps;
protected:
	std::unique_ptr<StorageLogger> logger;
	virtual void run(bool initial) = 0;
	virtual AbstractTrainingPlan* getCopy() = 0;
	virtual void tryToPause() = 0;
	void pausingFinished();
	void finished();
	virtual void initializeStart() {};
	void addCustomSubApp(AbstractCustomSubAppFactory* customSubApp);
public:
	AbstractTrainingPlan();
	void start();
	virtual std::string getName() = 0;
	virtual std::string getDescription() = 0;
	virtual std::string getLearningRuleName() = 0;
	std::string getStateAsString();
	AbstractTrainingPlan* getCopyForExecute();
	AbstractTrainingPlan* getTrainingPlanPattern();
	void pause();
	bool isPaused();
	bool isPausing();
	bool isRunning();
	virtual std::vector<std::string> getDataSetLabels() = 0;
	virtual LearningState* getLearningState() = 0;
	StorageLogger* getLogger();
	std::vector<std::unique_ptr<AbstractCustomSubAppFactory>>* getCustomSubApps();
};

#include "IO/AbstractTrainingPlanIO.hpp"

#endif
