#pragma once

#ifndef _ABSTRACTCOEVOLUTIONTRAININGPLANIO_H_
#define _ABSTRACTCOEVOLUTIONTRAININGPLANIO_H_

// Includes
#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"
#include <Learning/Evolution/AbstractCoevolutionWorld.hpp>

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	/**
	 * \brief Saves an AbstractCoevolutionTrainingPlan.
	 * \tparam Archive The archive type.
	 * \param archive The archive which should be used.
	 * \param trainingPlan The AbstractCoevolutionTrainingPlan to save.
	 */
	template <class Archive>
	void save(Archive& archive, AbstractCoevolutionTrainingPlan const& trainingPlan)
	{
		archive(cereal::make_nvp("parasiteWorld", trainingPlan.parasiteWorld));
		archive(cereal::base_class<AbstractEvolutionTrainingPlan>(&trainingPlan));
	}

	/**
	* \brief Loads an AbstractCoevolutionTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractCoevolutionTrainingPlan to load.
	*/
	template <class Archive>
	void load(Archive& archive, AbstractCoevolutionTrainingPlan& trainingPlan)
	{
		IOStorage<AbstractEvolutionWorld>::push(trainingPlan.createParasiteWorld());
		archive(cereal::make_nvp("parasiteWorld", trainingPlan.parasiteWorld));
		trainingPlan.parasiteWorld.reset(IOStorage<AbstractEvolutionWorld>::pop());

		archive(cereal::base_class<AbstractEvolutionTrainingPlan>(&trainingPlan));

		trainingPlan.parasiteWorld->setLearningState(trainingPlan.getLearningState());
		static_cast<AbstractCoevolutionWorld*>(trainingPlan.parasiteWorld.get())->getCombiningStrategy().setSecondWorld(static_cast<AbstractCoevolutionWorld&>(*trainingPlan.world.get()));
		static_cast<AbstractCoevolutionWorld*>(trainingPlan.world.get())->getCombiningStrategy().setSecondWorld(static_cast<AbstractCoevolutionWorld&>(*trainingPlan.parasiteWorld.get()));
	}
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::AbstractCoevolutionTrainingPlan);

#endif