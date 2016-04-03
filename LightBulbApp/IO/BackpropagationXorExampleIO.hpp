#pragma once

#ifndef _BACKPROPAGATIONXOREXAMPLEIO_H_
#define _BACKPROPAGATIONXOREXAMPLEIO_H_

// Includes
#include "IO/AbstractTrainingPlanIO.hpp"
#include "Examples/BackpropagationXorExample.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/base_class.hpp>

template <class Archive>
void serialize(Archive& archive, BackpropagationXorExample& trainingPlan)
{
	archive(cereal::base_class<AbstractTrainingPlan>(&trainingPlan));
	archive(trainingPlan.learningRule);
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(BackpropagationXorExample);

#endif