#pragma once

#ifndef _TRAININGPLANREPOSITORY_H_
#define _TRAININGPLANREPOSITORY_H_

// Library includes
#include <vector>
#include <memory>

// Includes
#include "LightBulb/Event/Observable.hpp"

namespace LightBulb
{
	class AbstractTrainingPlan;
	/**
	 * \brief All events the training plan repository can throw.
	 */
	enum TrainingPlanRepositoryEvents : unsigned int
	{
		/**
		 * \brief Is thrown if the training plans have been changed.
		 */
		EVT_TP_CHANGED
	};
	/**
	 * \brief A repository which stores all training plans which are currently executed in the LightBulbApp.
	 */
	class TrainingPlanRepository : public LightBulb::Observable<TrainingPlanRepositoryEvents, TrainingPlanRepository>
	{
		template <class Archive>
		friend void serialize(Archive& archive, TrainingPlanRepository& trainingPlanRepository);
	private:
		/**
		 * \brief The training plan storage.
		 */
		std::vector<std::unique_ptr<AbstractTrainingPlan>> trainingPlans;
	public:
		/**
		 * \brief Returns all training plans.
		 * \return A vector of all training plans.
		 */
		const std::vector<std::unique_ptr<AbstractTrainingPlan>>& getTrainingPlans() const;
		/**
		 * \brief Returns the index of a given training plan.
		 * \param trainingPlan The training plan.
		 * \return The index of the training plan in the training plan storage vector.
		 */
		int getIndexOfTrainingPlan(const AbstractTrainingPlan& trainingPlan) const;
		/**
		 * \brief Adds a new training plan to the repository.
		 * \param trainingPlan The new training plan.
		 */
		void Add(AbstractTrainingPlan* trainingPlan);
		/**
		* \brief Saves the training plan with the given index as a file.
		* \param path The path where to store the file.
		* \param trainingPlanIndex The index of the training plan to save.
		*/
		void save(const std::string& path, int trainingPlanIndex) const;
		/**
		* \brief Loads a training plan from file and stores it in the repository.
		* \param path The path of the file to load.
		*/
		AbstractTrainingPlan& load(const std::string& path);
		/**
		 * \brief Returns the training plan with the given name.
		 * \param name The name to search for.
		 * \return The training plan with the given name.
		 * \note If no training plan can be found, an exception is thrown.
		 */
		AbstractTrainingPlan& getByName(const std::string& name) const;
		/**
		 * \brief Sets the name of the training plan with the given index.
		 * \param trainingPlanIndex The index of the training plan.
		 * \param newName The new name.
		 */
		void setTrainingPlanName(int trainingPlanIndex, const std::string& newName);
		/**
		 * \brief Returns if a training plan with the given name exists.
		 * \param name The name to search for.
		 * \return True, if a training plan with this name exists.
		 */
		bool exists(const std::string& name) const;
		void clear();
	};
}

#include "LightBulbApp/IO/TrainingPlanRepositoryIO.hpp"

#endif
