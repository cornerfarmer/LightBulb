#pragma once

#ifndef _ABSTRACTCOEVOLUTIONTRAININGPLANIO_H_
#define _ABSTRACTCOEVOLUTIONTRAININGPLANIO_H_

// Includes
#include "TrainingPlans/AbstractCoevolutionTrainingPlan.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>

template <class Archive>
void save(Archive& archive, AbstractCoevolutionTrainingPlan const& trainingPlan)
{
	archive(cereal::make_nvp("parasiteWorld", trainingPlan.parasiteWorld));
	archive(cereal::base_class<AbstractEvolutionTrainingPlan>(&trainingPlan));
}

template <class Archive>
void load(Archive& archive, AbstractCoevolutionTrainingPlan& trainingPlan)
{
	archive(cereal::make_nvp("parasiteWorld", trainingPlan.parasiteWorld));
	archive(cereal::base_class<AbstractEvolutionTrainingPlan>(&trainingPlan));
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(AbstractCoevolutionTrainingPlan);

#endif