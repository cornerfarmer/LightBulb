#pragma once

#ifndef _ABSTRACTLEARNINGRULETRAININGPLANIO_H_
#define _ABSTRACTLEARNINGRULETRAININGPLANIO_H_

// Includes
#include "TrainingPlans/AbstractLearningRuleTrainingPlan.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>
#include <IO/IOStorage.hpp>

template <class Archive>
void save(Archive& archive, AbstractLearningRuleTrainingPlan const& trainingPlan)
{
	archive(cereal::base_class<AbstractTrainingPlan>(&trainingPlan));
	archive(cereal::make_nvp("learningRule", trainingPlan.learningRule));
}

template <class Archive>
void load(Archive& archive, AbstractLearningRuleTrainingPlan& trainingPlan)
{
	archive(cereal::base_class<AbstractTrainingPlan>(&trainingPlan));

	IOStorage<AbstractLearningRule>::push(trainingPlan.createLearningRate());
	archive(cereal::make_nvp("learningRule", trainingPlan.learningRule));
	trainingPlan.learningRule.reset(IOStorage<AbstractLearningRule>::pop());
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(AbstractLearningRuleTrainingPlan);

#endif