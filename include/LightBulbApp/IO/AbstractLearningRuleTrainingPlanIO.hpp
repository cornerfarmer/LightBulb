#pragma once

#ifndef _ABSTRACTLEARNINGRULETRAININGPLANIO_H_
#define _ABSTRACTLEARNINGRULETRAININGPLANIO_H_

// Includes
#include "LightBulbApp/TrainingPlans/AbstractLearningRuleTrainingPlan.hpp"

namespace LightBulb
{
	/**
	* \brief Saves an AbstractLearningRuleTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractLearningRuleTrainingPlan to save.
	*/
	template <class Archive>
	extern void save(Archive& archive, AbstractLearningRuleTrainingPlan const& trainingPlan);

	/**
	* \brief Loads an AbstractLearningRuleTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractLearningRuleTrainingPlan to load.
	*/
	template <class Archive>
	extern void load(Archive& archive, AbstractLearningRuleTrainingPlan& trainingPlan);
}

#include "LightBulb/IO/TemplateDeclaration.hpp"
CEREAL_FORCE_DYNAMIC_INIT_FIXED(AbstractLearningRuleTrainingPlan)

#endif