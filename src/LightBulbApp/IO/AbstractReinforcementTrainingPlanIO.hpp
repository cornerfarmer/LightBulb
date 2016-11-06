#pragma once

#ifndef _ABSTRACTREINFORCEMENTTRAININGPLANIO_H_
#define _ABSTRACTREINFORCEMENTTRAININGPLANIO_H_

// Includes
#include "TrainingPlans/AbstractReinforcementTrainingPlan.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>
#include <IO/IOStorage.hpp>

namespace LightBulb
{
	/**
	* \brief Saves an AbstractReinforcementTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractReinforcementTrainingPlan to save.
	*/
	template <class Archive>
	void save(Archive& archive, AbstractReinforcementTrainingPlan const& trainingPlan)
	{
		archive(cereal::make_nvp("world", trainingPlan.world));
		archive(cereal::base_class<AbstractLearningRuleTrainingPlan>(&trainingPlan));
	}

	/**
	* \brief Loads an AbstractReinforcementTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractReinforcementTrainingPlan to load.
	*/
	template <class Archive>
	void load(Archive& archive, AbstractReinforcementTrainingPlan& trainingPlan)
	{
		IOStorage<AbstractReinforcementWorld>::push(trainingPlan.createWorld());
		archive(cereal::make_nvp("world", trainingPlan.world));
		trainingPlan.world.reset(IOStorage<AbstractReinforcementWorld>::pop());

		archive(cereal::base_class<AbstractLearningRuleTrainingPlan>(&trainingPlan));

		trainingPlan.world->setLearningState(trainingPlan.getLearningState());
	}
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::AbstractReinforcementTrainingPlan);

#endif