#pragma once

#ifndef _RBFNETWORKBIGGEREXAMPLEIO_H_
#define _RBFNETWORKBIGGEREXAMPLEIO_H_

// Includes
#include "IO/AbstractLearningRuleTrainingPlanIO.hpp"
#include "IO/BackpropagationLearningRuleIO.hpp"
#include "Examples/RBFNetworkBiggerExample.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>

template <class Archive>
void save(Archive& archive, RBFNetworkBiggerExample const& trainingPlan)
{
	archive(cereal::base_class<AbstractLearningRuleTrainingPlan>(&trainingPlan));
}

template <class Archive>
void load(Archive& archive, RBFNetworkBiggerExample& trainingPlan)
{
	archive(cereal::base_class<AbstractLearningRuleTrainingPlan>(&trainingPlan));
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(RBFNetworkBiggerExample);

#endif