#pragma once

#ifndef _ABSTRACTEVOLUTIONTRAININGPLANIO_H_
#define _ABSTRACTEVOLUTIONTRAININGPLANIO_H_

// Includes
#include "TrainingPlans/AbstractEvolutionTrainingPlan.hpp"
#include "Learning/Evolution/AbstractEvolutionWorld.hpp"
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
	IOStorage<AbstractEvolutionWorld>::push(trainingPlan.createWorld());
	archive(cereal::make_nvp("world", trainingPlan.world));
	trainingPlan.world.reset(IOStorage<AbstractEvolutionWorld>::pop());

	archive(cereal::base_class<AbstractLearningRuleTrainingPlan>(&trainingPlan));

	trainingPlan.world->setLearningState(trainingPlan.getLearningState());
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(AbstractEvolutionTrainingPlan);

#endif