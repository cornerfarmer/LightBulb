#pragma once

#ifndef _ABSTRACTCOEVOLUTIONTRAININGPLANIO_H_
#define _ABSTRACTCOEVOLUTIONTRAININGPLANIO_H_

// Includes
#include "LightBulbApp/TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"

namespace LightBulb
{
	/**
	 * \brief Saves an AbstractCoevolutionTrainingPlan.
	 * \tparam Archive The archive type.
	 * \param archive The archive which should be used.
	 * \param trainingPlan The AbstractCoevolutionTrainingPlan to save.
	 */
	template <class Archive>
	extern void save(Archive& archive, AbstractCoevolutionTrainingPlan const& trainingPlan);

	/**
	* \brief Loads an AbstractCoevolutionTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractCoevolutionTrainingPlan to load.
	*/
	template <class Archive>
	extern void load(Archive& archive, AbstractCoevolutionTrainingPlan& trainingPlan);
}

#endif