#pragma once

#ifndef _ABSTRACTTRAININGPLANIO_H_
#define _ABSTRACTTRAININGPLANIO_H_

// Includes
#include "LightBulbApp/TrainingPlans/AbstractTrainingPlan.hpp"

namespace LightBulb
{
	/**
	* \brief Saves an AbstractTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractTrainingPlan to save.
	*/
	template <class Archive>
	extern void save(Archive& archive, AbstractTrainingPlan const& trainingPlan);

	/**
	* \brief Loads an AbstractTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractTrainingPlan to load.
	*/
	template <class Archive>
	extern void load(Archive& archive, AbstractTrainingPlan& trainingPlan);
}

#endif