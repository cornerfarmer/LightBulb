#pragma once

#ifndef _TRAININGPLANREPOSITORYIO_H_
#define _TRAININGPLANREPOSITORYIO_H_

// Includes
#include "IO/BackpropagationXorExampleIO.hpp"
#include "IO/RBFNetworkBiggerExampleIO.hpp"
#include "Repositories/TrainingPlanRepository.hpp"
// Libraray includes
#include <cereal/cereal.hpp>

template <class Archive>
void serialize(Archive& archive, TrainingPlanRepository& trainingPlanRepository)
{
	onlyUseNeuralNetworkIndex = true;
	archive(cereal::make_nvp("trainingPlans", trainingPlanRepository.trainingPlans));
	trainingPlanRepository.throwEvent(EVT_TP_CHANGED, &trainingPlanRepository);
}

#endif