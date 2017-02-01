#pragma once

#ifndef _ABSTRACTTRAININGPLAN_H_
#define _ABSTRACTTRAININGPLAN_H_

// Includes
#include "LightBulb/Event/Observable.hpp"
#include "LightBulb/Logging/StorageLogger.hpp"
#include "LightBulbApp/Windows/AbstractCustomSubAppFactory.hpp"
#include "Preferences/AbstractPreference.hpp"
#include "Preferences/PreferenceGroup.hpp"

// Library includes
#include <thread>
#include <vector>

namespace LightBulb
{
	// Forward declarations
	class AbstractLogger;
	struct LearningState;
	/**
	 * \brief All possible training plan states.
	 */
	enum TrainingPlanState
	{
		/**
		 * \brief The training plan is running.
		 */
		TP_RUNNING,
		/**
		* \brief The training plan is pausing.
		*/
		TP_PAUSING,
		/**
		* \brief The training plan is paused.
		*/
		TP_PAUSED,
		/**
		* \brief The training plan is in idle state.
		*/
		TP_IDLE,
		/**
		* \brief The training plan has been finished.
		*/
		TP_FINISHED
	};
	/**
	* \brief All events the TrainingPlanEvents can throw.
	*/
	enum TrainingPlanEvents
	{
		/**
		 * \brief Thrown, if the training plan has been paused.
		 */
		EVT_TP_PAUSED,
		/**
		 * \brief Thrown, if the training plan has been finished.
		 */
		EVT_TP_FINISHED
	};

#define DEFAULT_PREFERENCE_GROUP "Default"
	/**
	 * \brief A training plan describes a learning process which can be managed inside the LightBulbApp.
	 */
	class AbstractTrainingPlan : public LightBulb::Observable<TrainingPlanEvents, AbstractTrainingPlan>
	{
		template <class Archive>
		friend void save(Archive& archive, AbstractTrainingPlan const& trainingPlan);
		template <class Archive>
		friend void load(Archive& archive, AbstractTrainingPlan& trainingPlan);
	private:
		/**
		 * \brief The time when the current run has started.
		 */
		std::chrono::time_point<std::chrono::system_clock> currentStartTime;
		/**
		 * \brief The total run time of the training plan.
		 */
		std::chrono::duration<double> concludedRunTime;
		/**
		 * \brief The thread for running this training plan independently.
		 */
		std::thread thread;
		/**
		 * \brief The name of the training plan pattern which is the origin of this training plan.
		 */
		std::string patternName;
		/**
		 * \brief The current state.
		 */
		TrainingPlanState state;
		/**
		 * \brief The name of the training plan.
		 */
		std::string name;
		/**
		 * \brief The method which will be runned inside the own thread.
		 * \param initial True, if its the initial run.
		 */
		void runThread(bool initial);
		/**
		 * \brief True, if the thread should be joined before the next reuse.
		 */
		bool threadShouldBeJoinedBeforeReuse;
		/**
		 * \brief Contains all sub apps which are offered by this training plan.
		 */
		std::vector<std::unique_ptr<AbstractCustomSubAppFactory>> customSubApps;
		/**
		 * \brief Contains the root prefernece group of the training plan.
		 */
		std::unique_ptr<PreferenceGroup> preferenceGroup;
	protected:
		/**
		 * \brief The logger which is used by the training plan.
		 */
		std::unique_ptr<StorageLogger> logger;
		/**
		 * \brief Runs the training plan.
		 * \param initial True, if its the initial run.
		 */
		virtual void run(bool initial) = 0;
		/**
		 * \brief Creates a new training plan from the same type.
		 * \return The new training plan.
		 */
		virtual AbstractTrainingPlan* createNewFromSameType() const = 0;
		/**
		 * \brief Requests a pause.
		 */
		virtual void tryToPause() = 0;
		/**
		 * \brief Called after the pausing has been finished.
		 */
		virtual void pausingFinished();
		/**
		 * \brief Called if the training plan has been finished.
		 */
		virtual void finished();
		/**
		 * \brief Initializes the training plan before starting it.
		 */
		virtual void initializeStart() {};
		/**
		 * \brief Adds a custom sub app to the training plan.
		 * \param customSubApp The new sub app.
		 */
		void addCustomSubApp(AbstractCustomSubAppFactory* customSubApp);
		/**
		 * \brief Adds a new preference to the default preference group.
		 * \param newPreference The new preference.
		 */
		void addPreference(AbstractPreference* newPreference);
		/**
		 * \brief Adds a new preference group to the default preference group.
		 * \param newPreferenceGroup The new preference group.
		 */
		void addPreferenceGroup(PreferenceGroup* newPreferenceGroup);
		/**
		 * \brief Returns the preference group with the given name.
		 * \param groupName The name to search for.
		 * \return The preference group.
		 */
		PreferenceGroup& getPreferenceGroup(const std::string& groupName);
		/**
		* \brief Returns the preference group with the given name.
		* \param groupName The name to search for.
		* \return The preference group.
		*/
		const PreferenceGroup& getPreferenceGroup(const std::string& groupName) const;
		/**
		 * \brief Returns the preference with the given name from the group with the given name.
		 * \param name The preference name to search for.
		 * \param groupName The preference group name to search for.
		 * \return The preference.
		 */
		const AbstractPreference& getPreference(const std::string& name, const std::string& groupName = DEFAULT_PREFERENCE_GROUP) const;
		/**
		* \brief Returns the value of the double preference with the given name from the group with the given name.
		* \param name The preference name to search for.
		* \param groupName The preference group name to search for.
		* \return The value of the double preference.
		*/
		double getDoublePreference(const std::string& name, const std::string& groupName = DEFAULT_PREFERENCE_GROUP) const;
		/**
		* \brief Returns the value of the int preference with the given name from the group with the given name.
		* \param name The preference name to search for.
		* \param groupName The preference group name to search for.
		* \return The value of the int preference.
		*/
		int getIntegerPreference(const std::string& name, const std::string& groupName = DEFAULT_PREFERENCE_GROUP) const;
		/**
		* \brief Returns the value of the boolean preference with the given name from the group with the given name.
		* \param name The preference name to search for.
		* \param groupName The preference group name to search for.
		* \return The value of the boolean preference.
		*/
		bool getBooleanPreference(const std::string& name, const std::string& groupName = DEFAULT_PREFERENCE_GROUP) const;
		/**
		* \brief Calls the createFromGroup() method on the first preference group with the given type and returns the retrieved object.
		* \tparam Class The class of the object which should be returned.
		* \tparam PreferenceGroupClass The class of the preference group to serach for.
		* \return The created object.
		* \throws std::invalid_argument If there is no group with the given type.
		*/
		template<class OptionsClass, class PreferenceGroupClass>
		OptionsClass createOptions() const
		{
			return preferenceGroup->createFromGroup<OptionsClass, PreferenceGroupClass>();
		}
		/**
		* \brief Calls the createFromGroup() method on the preference group with the given type and the given name and returns the retrieved object.
		* \tparam Class The class of the object which should be returned.
		* \tparam PreferenceGroupClass The class of the preference group to serach for.
		* \param groupName The name of the preference group to serach for.
		* \return The created object.
		* \throws std::invalid_argument If there is no preference group with the given name.
		*/
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
		/**
		 * \brief Creates the training plan.
		 */
		AbstractTrainingPlan();
		/**
		 * \brief Starts the training plan.
		 */
		void start();
		/**
		 * \brief Returns the name of the training plan.
		 * \return The name.
		 */
		std::string getName() const;
		/**
		 * \brief Returns the original name of the training plan.
		 * \return The original name.
		 */
		virtual std::string getOriginalName() const = 0;
		/**
		 * \brief Returns the description.
		 * \return The description.
		 */
		virtual std::string getDescription() const = 0;
		/**
		 * \brief Returns the name of the learning rule.
		 * \return The learning rule.
		 */
		virtual std::string getLearningRuleName() const = 0;
		/**
		 * \brief Returns the current state as string.
		 * \return The state as string.
		 */
		std::string getStateAsString() const;
		/**
		 * \brief Creates the new copy for execute.
		 * \return The new copy which can be executed.
		 */
		AbstractTrainingPlan* getCopyForExecute();
		/**
		 * \brief Returns the name of the origin training plan pattern.
		 * \return The name.
		 */
		const std::string& getTrainingPlanPatternName() const;
		/**
		* \brief Requests a pause.
		*/
		void pause();
		/**
		 * \brief Returns if the training plan has been paused.
		 * \return True, if it has been paused.
		 */
		bool isPaused() const;
		/**
		 * \brief Returns if the training plan is currently pausing.
		 * \return True, if its pausing.
		 */
		bool isPausing() const;
		/**
		* \brief Returns if the training plan is currently running.
		* \return True, if its running.
		*/
		bool isRunning() const;
		/**
		* \brief Returns a vector of all data set labels which are available in the learning state of this learning rule.
		* \return The labels of all available data sets.
		*/
		virtual std::vector<std::string> getDataSetLabels() const = 0;
		/**
		 * \brief Returns the current learning state.
		 * \return The state.
		 */
		virtual LearningState& getLearningState() = 0;
		/**
		* \brief Returns if there is already a learning state.
		* \return True, if there is one.
		*/
		virtual bool hasLearningState() = 0;
		/**
		 * \brief Returns the logger of the training plan.
		 * \return The logger.
		 */
		StorageLogger& getLogger();
		/**
		 * \brief Returns all available custom sub apps.
		 * \return A vector of all custom sub apps.
		 */
		const std::vector<std::unique_ptr<AbstractCustomSubAppFactory>>& getCustomSubApps() const;
		/**
		 * \brief Returns the current run time.
		 * \return The run time.
		 */
		std::chrono::duration<double> getRunTime() const;
		/**
		 * \brief Returns all preference groups.
		 * \return All preference groups.
		 */
		const std::vector<std::unique_ptr<AbstractPreferenceElement>>& getPreferenceGroups() const;
		/**
		 * \brief Sets the name of the training plan.
		 * \param newName The new name.
		 */
		void setName(const std::string& newName);
		/**
		 * \brief Returns the seed of the training plan.
		 * \return The used seed.
		 */
		virtual int getSeed() const = 0;
	};
}
#include "LightBulbApp/IO/AbstractTrainingPlanIO.hpp"
#endif
