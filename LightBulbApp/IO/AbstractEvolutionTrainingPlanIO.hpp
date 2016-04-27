#pragma once

#ifndef _ABSTRACTEVOLUTIONTRAININGPLANIO_H_
#define _ABSTRACTEVOLUTIONTRAININGPLANIO_H_

// Includes
#include "TrainingPlans/AbstractEvolutionTrainingPlan.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>
#include <IO/IOStorage.hpp>

template <class Archive>
void save(Archive& archive, AbstractEvolutionTrainingPlan const& trainingPlan)
{
	archive(cereal::make_nvp("world", trainingPlan.world));
	archive(cereal::base_class<AbstractLearningRuleTrainingPlan>(&trainingPlan));
}

template <class Archive>
void load(Archive& archive, AbstractEvolutionTrainingPlan& trainingPlan)
{
	archive(cereal::make_nvp("world", trainingPlan.world));
	archive(cereal::base_class<AbstractLearningRuleTrainingPlan>(&trainingPlan));

	trainingPlan.world->setLearningState(trainingPlan.getLearningState());
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(AbstractEvolutionTrainingPlan);

#endif