#pragma once

#ifndef _ABSTRACTEVOLUTIONTRAININGPLANIO_H_
#define _ABSTRACTEVOLUTIONTRAININGPLANIO_H_

// Includes
#include "TrainingPlans/AbstractEvolutionTrainingPlan.hpp"
#include "Learning/Evolution/AbstractEvolutionEnvironment.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>
#include <IO/IOStorage.hpp>

namespace LightBulb
{
	/**
	* \brief Saves an AbstractEvolutionTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractEvolutionTrainingPlan to save.
	*/
	template <class Archive>
	void save(Archive& archive, AbstractEvolutionTrainingPlan const& trainingPlan)
	{
		archive(cereal::make_nvp("environment", trainingPlan.environment));
		archive(cereal::base_class<AbstractLearningRuleTrainingPlan>(&trainingPlan));
	}

	/**
	* \brief Loads an AbstractEvolutionTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractEvolutionTrainingPlan to load.
	*/
	template <class Archive>
	void load(Archive& archive, AbstractEvolutionTrainingPlan& trainingPlan)
	{
		IOStorage<AbstractEvolutionEnvironment>::push(trainingPlan.createEnvironment());
		archive(cereal::make_nvp("environment", trainingPlan.environment));
		trainingPlan.environment.reset(IOStorage<AbstractEvolutionEnvironment>::pop());

		archive(cereal::base_class<AbstractLearningRuleTrainingPlan>(&trainingPlan));

		trainingPlan.environment->setLearningState(trainingPlan.getLearningState());
	}
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::AbstractEvolutionTrainingPlan);

#endif