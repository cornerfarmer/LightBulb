// Includes
#include "TrainingPlans/AbstractTrainingPlan.hpp"
#include "Preferences/DoublePreference.hpp"
#include "Preferences/IntegerPreference.hpp"
#include "Preferences/BooleanPreference.hpp"
#include <thread>

namespace LightBulb
{
	void AbstractTrainingPlan::addCustomSubApp(AbstractCustomSubAppFactory* customSubApp)
	{
		customSubApps.push_back(std::unique_ptr<AbstractCustomSubAppFactory>(customSubApp));
	}

	void AbstractTrainingPlan::addPreference(AbstractPreference* newPreference)
	{
		preferenceGroup->getPreferenceGroup(DEFAULT_PREFERENCE_GROUP)->addPreference(newPreference);
	}

	void AbstractTrainingPlan::addPreferenceGroup(PreferenceGroup* newPreferenceGroup)
	{
		preferenceGroup->addPreference(newPreferenceGroup);
	}

	PreferenceGroup* AbstractTrainingPlan::getPreferenceGroup(std::string groupName)
	{
		return preferenceGroup->getPreferenceGroup(groupName);
	}

	AbstractPreference* AbstractTrainingPlan::getPreference(std::string name, std::string groupName)
	{
		PreferenceGroup* preferenceGroup = getPreferenceGroup(groupName);
		if (preferenceGroup)
			return preferenceGroup->getPreference(name);
		else
			return nullptr;
	}

	double AbstractTrainingPlan::getDoublePreference(std::string name, std::string groupName)
	{
		PreferenceGroup* preferenceGroup = getPreferenceGroup(groupName);
		if (preferenceGroup)
			return preferenceGroup->getDoublePreference(name);
		else
			return 0;
	}


	int AbstractTrainingPlan::getIntegerPreference(std::string name, std::string groupName)
	{
		PreferenceGroup* preferenceGroup = getPreferenceGroup(groupName);
		if (preferenceGroup)
			return preferenceGroup->getIntegerPreference(name);
		else
			return 0;
	}

	bool AbstractTrainingPlan::getBooleanPreference(std::string name, std::string groupName)
	{
		PreferenceGroup* preferenceGroup = getPreferenceGroup(groupName);
		if (preferenceGroup)
			return preferenceGroup->getBooleanPreference(name);
		else
			return false;
	}

	std::chrono::duration<double> AbstractTrainingPlan::getRunTime()
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

	std::string AbstractTrainingPlan::getName()
	{
		if (name != "")
			return name;
		else
			return getDefaultName();
	}

	std::string AbstractTrainingPlan::getStateAsString()
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
		AbstractTrainingPlan* copy = getCopy();
		copy->pattern = this;
		copy->preferenceGroup.reset(static_cast<PreferenceGroup*>(preferenceGroup->getCopy()));
		return copy;
	}

	AbstractTrainingPlan* AbstractTrainingPlan::getTrainingPlanPattern()
	{
		return pattern;
	}

	void AbstractTrainingPlan::pause()
	{
		if (state == TP_RUNNING)
		{
			state = TP_PAUSING;
			tryToPause();
		}
	}

	bool AbstractTrainingPlan::isPaused()
	{
		return state == TP_PAUSED;
	}

	bool AbstractTrainingPlan::isPausing()
	{
		return state == TP_PAUSING;
	}

	bool AbstractTrainingPlan::isRunning()
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
		throwEvent(EVT_TP_PAUSED, this);
	}

	void AbstractTrainingPlan::finished()
	{
		state = TP_FINISHED;
		throwEvent(EVT_TP_FINISHED, this);
	}


	StorageLogger* AbstractTrainingPlan::getLogger()
	{
		return logger.get();
	}

	std::vector<std::unique_ptr<AbstractCustomSubAppFactory>>* AbstractTrainingPlan::getCustomSubApps()
	{
		return &customSubApps;
	}

	std::vector<std::unique_ptr<AbstractPreferenceElement>>& AbstractTrainingPlan::getPreferenceGroups()
	{
		return preferenceGroup->getPreferenceElements();
	}

	void AbstractTrainingPlan::setName(std::string newName)
	{
		name = newName;
	}
}