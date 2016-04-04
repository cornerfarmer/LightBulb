#pragma once

#ifndef _BACKPROPAGATIONXOREXAMPLEIO_H_
#define _BACKPROPAGATIONXOREXAMPLEIO_H_

// Includes
#include "IO/AbstractTrainingPlanIO.hpp"
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
	archive(cereal::base_class<AbstractTrainingPlan>(&trainingPlan));
	archive(trainingPlan.learningRule);
}

template <class Archive>
void load(Archive& archive, BackpropagationXorExample& trainingPlan)
{
	archive(cereal::base_class<AbstractTrainingPlan>(&trainingPlan));

	trainingPlan.initializeLearningRate();
	IOStorage<BackpropagationLearningRule>::push(trainingPlan.learningRule.release());
	archive(trainingPlan.learningRule);
	trainingPlan.learningRule.reset(IOStorage<BackpropagationLearningRule>::pop());

	trainingPlan.learningRule->setCurrentNeuralNetwork(*trainingPlan.network);
	trainingPlan.learningRule->setCurrentTeacher(*trainingPlan.teacher);
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(BackpropagationXorExample);

#endif