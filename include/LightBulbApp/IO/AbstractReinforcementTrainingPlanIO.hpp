#pragma once

#ifndef _ABSTRACTREINFORCEMENTTRAININGPLANIO_H_
#define _ABSTRACTREINFORCEMENTTRAININGPLANIO_H_

// Includes
#include "LightBulbApp/TrainingPlans/AbstractReinforcementTrainingPlan.hpp"

namespace LightBulb
{
	/**
	* \brief Saves an AbstractReinforcementTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractReinforcementTrainingPlan to save.
	*/
	template <class Archive>
	extern void save(Archive& archive, AbstractReinforcementTrainingPlan const& trainingPlan);

	/**
	* \brief Loads an AbstractReinforcementTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractReinforcementTrainingPlan to load.
	*/
	template <class Archive>
	extern void load(Archive& archive, AbstractReinforcementTrainingPlan& trainingPlan);
}

#include "LightBulb/IO/TemplateDeclaration.hpp"
CEREAL_FORCE_DYNAMIC_INIT_FIXED(AbstractReinforcementTrainingPlan)

#endif