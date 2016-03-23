#pragma once

#ifndef _TRAININGCONTROLLER_H_
#define _TRAININGCONTROLLER_H_
#include <vector>
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>
#include <Teaching/AbstractTrainingPlan.hpp>

// Includes

// Forward declarations

class TrainingController
{
private:
	std::vector<AbstractNeuralNetwork*> neuralNetworks;
	std::vector<AbstractTrainingPlan*> trainingPlanPatterns;
	std::vector<AbstractTrainingPlan*> trainingPlans;
public:
	TrainingController();
	std::vector<AbstractNeuralNetwork*>* getNeuralNetworks();
	std::vector<AbstractTrainingPlan*>* getTrainingPlanPatterns();
	std::vector<AbstractTrainingPlan*>* getTrainingPlans();
};

#endif
