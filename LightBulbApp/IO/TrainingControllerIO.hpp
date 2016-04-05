#pragma once

#ifndef _TRAININGCONTROLLERIO_H_
#define _TRAININGCONTROLLERIO_H_

// Includes
#include "IO/NeuralNetworkIO.hpp"
#include "Windows/TrainingController.hpp"
// Libraray includes
#include <cereal/cereal.hpp>

template <class Archive>
void serialize(Archive& archive, TrainingController& trainingController)
{
	archive(cereal::make_nvp("neuralNetworks", *trainingController.neuralNetworkRepository->getNeuralNetworks()));
	archive(cereal::make_nvp("trainingPlans", *trainingController.trainingPlanRepository->getTrainingPlans()));
}


#endif