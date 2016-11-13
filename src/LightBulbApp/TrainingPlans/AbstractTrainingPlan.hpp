#pragma once

#ifndef _ABSTRACTTRAININGPLAN_H_
#define _ABSTRACTTRAININGPLAN_H_

// Includes
#include <Event/Observable.hpp>
#include <Logging/StorageLogger.hpp>
#include <Windows/AbstractCustomSubAppFactory.hpp>
#include "Preferences/AbstractPreference.hpp"
#include "Preferences/PreferenceGroup.hpp"

// Library includes
#include <string>
#include <thread>
#include <vector>
#include <cereal/cereal.hpp>

namespace LightBulb
{
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

#define DEFAULT_PREFERENCE_GROUP "Default"

	class AbstractTrainingPlan : public LightBulb::Observable<TrainingPlanEvents, AbstractTrainingPlan>
	{
		template <class Archive>
		friend void save(Archive& archive, AbstractTrainingPlan const& trainingPlan);
		template <class Archive>
		friend void load(Archive& archive, AbstractTrainingPlan& trainingPlan);
	private:
		std::chrono::time_point<std::chrono::system_clock> currentStartTime;
		std::chrono::duration<double> concludedRunTime;
		std::thread thread;
		std::string patternName;
		TrainingPlanState state;
		std::string name;
		void runThread(bool initial);
		bool threadShouldBeJoinedBeforeReuse;
		std::vector<std::unique_ptr<AbstractCustomSubAppFactory>> customSubApps;
		std::unique_ptr<PreferenceGroup> preferenceGroup;
	protected:
		std::unique_ptr<StorageLogger> logger;
		virtual void run(bool initial) = 0;
		virtual AbstractTrainingPlan* createNewFromSameType() const = 0;
		virtual void tryToPause() = 0;
		void pausingFinished();
		void finished();
		virtual void initializeStart() {};
		void addCustomSubApp(AbstractCustomSubAppFactory* customSubApp);
		void addPreference(AbstractPreference* newPreference);
		void addPreferenceGroup(PreferenceGroup* newPreferenceGroup);
		PreferenceGroup& getPreferenceGroup(const std::string& groupName);
		const PreferenceGroup& getPreferenceGroup(const std::string& groupName) const;
		const AbstractPreference& getPreference(const std::string& name, const std::string& groupName = DEFAULT_PREFERENCE_GROUP) const;
		double getDoublePreference(const std::string& name, const std::string& groupName = DEFAULT_PREFERENCE_GROUP) const;
		int getIntegerPreference(const std::string& name, const std::string& groupName = DEFAULT_PREFERENCE_GROUP) const;
		bool getBooleanPreference(const std::string& name, const std::string& groupName = DEFAULT_PREFERENCE_GROUP) const;
		template<class OptionsClass, class PreferenceGroupClass>
		OptionsClass createOptions() const
		{
			return preferenceGroup->createFromGroup<OptionsClass, PreferenceGroupClass>();
		}
		template<class OptionsClass, class PreferenceGroupClass>
		OptionsClass createOptions(std::string groupName) const
		{
			return preferenceGroup->createFromGroup<OptionsClass, PreferenceGroupClass>(groupName);
		}
	public:
		virtual ~AbstractTrainingPlan()
		{
			if (threadShouldBeJoinedBeforeReuse)
			{
				thread.join();
			}
		}
		AbstractTrainingPlan();
		void start();
		std::string getName() const;
		virtual std::string getDefaultName() const = 0;
		virtual std::string getDescription() const = 0;
		virtual std::string getLearningRuleName() const = 0;
		std::string getStateAsString() const;
		AbstractTrainingPlan* getCopyForExecute();
		const std::string& getTrainingPlanPatternName() const;
		void pause();
		bool isPaused() const;
		bool isPausing() const;
		bool isRunning() const;
		virtual std::vector<std::string> getDataSetLabels() const = 0;
		virtual LearningState& getLearningState() = 0;
		StorageLogger& getLogger();
		const std::vector<std::unique_ptr<AbstractCustomSubAppFactory>>& getCustomSubApps() const;
		std::chrono::duration<double> getRunTime() const;
		const std::vector<std::unique_ptr<AbstractPreferenceElement>>& getPreferenceGroups() const;
		void setName(const std::string& newName);
		virtual int getSeed() const = 0;
	};
}

#include "IO/AbstractTrainingPlanIO.hpp"

#endif
