#pragma once

#ifndef _BACKPROPAGATIONXOREXAMPLEIO_H_
#define _BACKPROPAGATIONXOREXAMPLEIO_H_

// Includes
#include "IO/AbstractLearningRuleTrainingPlanIO.hpp"
#include "IO/BackpropagationLearningRuleIO.hpp"
#include "Examples/BackpropagationXorExample.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>
#include <IO/IOStorage.hpp>


template <class Archive>
void save(Archive& archive, BackpropagationXorExample const& trainingPlan)
{
	archive(cereal::base_class<AbstractLearningRuleTrainingPlan>(&trainingPlan));
}

template <class Archive>
void load(Archive& archive, BackpropagationXorExample& trainingPlan)
{
	archive(cereal::base_class<AbstractLearningRuleTrainingPlan>(&trainingPlan));
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(BackpropagationXorExample);

#endif