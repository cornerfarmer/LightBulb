#pragma once

#ifndef _ABSTRACTEVOLUTIONTRAININGPLANIO_H_
#define _ABSTRACTEVOLUTIONTRAININGPLANIO_H_

// Includes
#include "LightBulbApp/TrainingPlans/AbstractEvolutionTrainingPlan.hpp"

namespace LightBulb
{
	/**
	* \brief Saves an AbstractEvolutionTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractEvolutionTrainingPlan to save.
	*/
	template <class Archive>
	extern void save(Archive& archive, AbstractEvolutionTrainingPlan const& trainingPlan);

	/**
	* \brief Loads an AbstractEvolutionTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractEvolutionTrainingPlan to load.
	*/
	template <class Archive>
	extern void load(Archive& archive, AbstractEvolutionTrainingPlan& trainingPlan);
}

#endif