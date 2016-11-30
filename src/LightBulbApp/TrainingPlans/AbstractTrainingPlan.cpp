// Includes
#include "TrainingPlans/AbstractTrainingPlan.hpp"
#include "TrainingPlans/Preferences/DoublePreference.hpp"
#include <thread>

namespace LightBulb
{
	void AbstractTrainingPlan::addCustomSubApp(AbstractCustomSubAppFactory* customSubApp)
	{
		customSubApps.push_back(std::unique_ptr<AbstractCustomSubAppFactory>(customSubApp));
	}

	void AbstractTrainingPlan::addPreference(AbstractPreference* newPreference)
	{
		preferenceGroup->getPreferenceGroup(DEFAULT_PREFERENCE_GROUP).addPreference(newPreference);
	}

	void AbstractTrainingPlan::addPreferenceGroup(PreferenceGroup* newPreferenceGroup)
	{
		preferenceGroup->addPreference(newPreferenceGroup);
	}

	PreferenceGroup& AbstractTrainingPlan::getPreferenceGroup(const std::string& groupName)
	{
		return preferenceGroup->getPreferenceGroup(groupName);
	}

	const PreferenceGroup& AbstractTrainingPlan::getPreferenceGroup(const std::string& groupName) const
	{
		return preferenceGroup->getPreferenceGroup(groupName);
	}

	const AbstractPreference& AbstractTrainingPlan::getPreference(const std::string& name, const std::string& groupName) const
	{
		return getPreferenceGroup(groupName).getPreference(name);
	}

	double AbstractTrainingPlan::getDoublePreference(const std::string& name, const std::string& groupName) const
	{
		return getPreferenceGroup(groupName).getDoublePreference(name);
	}


	int AbstractTrainingPlan::getIntegerPreference(const std::string& name, const std::string& groupName) const
	{
		return getPreferenceGroup(groupName).getIntegerPreference(name);
	}

	bool AbstractTrainingPlan::getBooleanPreference(const std::string& name, const std::string& groupName) const
	{
		return getPreferenceGroup(groupName).getBooleanPreference(name);
	}

	std::chrono::duration<double> AbstractTrainingPlan::getRunTime() const
	{
		return (isRunning() || isPausing() ? std::chrono::system_clock::now() - currentStartTime : std::chrono::duration<double>::zero()) + concludedRunTime;
	}

	AbstractTrainingPlan::AbstractTrainingPlan()
	{
		concludedRunTime = std::chrono::duration<double>(0);
		logger.reset(new StorageLogger());
		threadShouldBeJoinedBeforeReuse = false;
		state = TP_IDLE;
		preferenceGroup.reset(new PreferenceGroup("Root"));
		preferenceGroup->addPreference(new PreferenceGroup(DEFAULT_PREFERENCE_GROUP));
	}

	void AbstractTrainingPlan::start()
	{
		if (state == TP_IDLE)
		{
			initializeStart();
			state = TP_RUNNING;
			thread = std::thread(&AbstractTrainingPlan::runThread, this, true);
		}
		else if (state == TP_PAUSED)
		{
			state = TP_RUNNING;
			if (threadShouldBeJoinedBeforeReuse)
			{
				thread.join();
				threadShouldBeJoinedBeforeReuse = false;
			}
			thread = std::thread(&AbstractTrainingPlan::runThread, this, false);
		}
	}

	std::string AbstractTrainingPlan::getName() const
	{
		if (name != "")
			return name;
		else
			return getOriginalName();
	}

	std::string AbstractTrainingPlan::getStateAsString() const
	{
		switch (state)
		{
		case TP_IDLE:
			return "idle";
		case TP_PAUSING:
			return "pausing";
		case TP_RUNNING:
			return "running";
		case TP_PAUSED:
			return "paused";
		case TP_FINISHED:
			return "finished";
		default:
			return "";
		}
	}

	AbstractTrainingPlan* AbstractTrainingPlan::getCopyForExecute()
	{
		AbstractTrainingPlan* copy = createNewFromSameType();
		copy->patternName = getName();
		copy->preferenceGroup.reset(dynamic_cast<PreferenceGroup*>(preferenceGroup->clone()));
		return copy;
	}

	const std::string& AbstractTrainingPlan::getTrainingPlanPatternName() const
	{
		return patternName;
	}

	void AbstractTrainingPlan::pause()
	{
		if (state == TP_RUNNING)
		{
			state = TP_PAUSING;
			tryToPause();
		}
	}

	bool AbstractTrainingPlan::isPaused() const
	{
		return state == TP_PAUSED;
	}

	bool AbstractTrainingPlan::isPausing() const
	{
		return state == TP_PAUSING;
	}

	bool AbstractTrainingPlan::isRunning() const
	{
		return state == TP_RUNNING;
	}

	void AbstractTrainingPlan::runThread(bool initial)
	{
		currentStartTime = std::chrono::system_clock::now();

		run(initial);
		threadShouldBeJoinedBeforeReuse = true;

		concludedRunTime += std::chrono::system_clock::now() - currentStartTime;
	}

	void AbstractTrainingPlan::pausingFinished()
	{
		state = TP_PAUSED;
		throwEvent(EVT_TP_PAUSED, *this);
	}

	void AbstractTrainingPlan::finished()
	{
		state = TP_FINISHED;
		throwEvent(EVT_TP_FINISHED, *this);
	}


	StorageLogger& AbstractTrainingPlan::getLogger()
	{
		return *logger.get();
	}

	const std::vector<std::unique_ptr<AbstractCustomSubAppFactory>>& AbstractTrainingPlan::getCustomSubApps() const
	{
		return customSubApps;
	}

	const std::vector<std::unique_ptr<AbstractPreferenceElement>>& AbstractTrainingPlan::getPreferenceGroups() const
	{
		return preferenceGroup->getPreferenceElements();
	}

	void AbstractTrainingPlan::setName(const std::string& newName)
	{
		name = newName;
	}
}