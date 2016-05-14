#pragma once

#ifndef _ABSTRACTTRAININGPLANIO_H_
#define _ABSTRACTTRAININGPLANIO_H_

// Includes
#include "TrainingPlans/AbstractTrainingPlan.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>

template <class Archive>
void save(Archive& archive, AbstractTrainingPlan const& trainingPlan)
{
	archive(cereal::make_nvp("state", trainingPlan.state));
	archive(cereal::make_nvp("logger", trainingPlan.logger));
	archive(cereal::make_nvp("name", trainingPlan.name));
	archive(cereal::make_nvp("preferences", trainingPlan.preferences));
	archive(cereal::make_nvp("concludedRunTime", trainingPlan.concludedRunTime.count()));
}

template <class Archive>
void load(Archive& archive, AbstractTrainingPlan& trainingPlan)
{
	archive(cereal::make_nvp("state", trainingPlan.state));
	archive(cereal::make_nvp("logger", trainingPlan.logger));
	archive(cereal::make_nvp("name", trainingPlan.name));
	archive(cereal::make_nvp("preferences", trainingPlan.preferences));
	double concludedRunTime;
	archive(cereal::make_nvp("concludedRunTime", concludedRunTime));
	trainingPlan.concludedRunTime = std::chrono::duration<double>(concludedRunTime);
}

#endif