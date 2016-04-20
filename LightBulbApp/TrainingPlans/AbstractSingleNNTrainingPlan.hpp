#pragma once

#ifndef _ABSTRACTSINGLENNTRAININGPLAN_H_
#define _ABSTRACTSINGLENNTRAININGPLAN_H_

// Includes
#include "TrainingPlans/AbstractLearningRuleTrainingPlan.hpp"

// Library includes


// Forward declarations
class AbstractNeuralNetwork;

class AbstractSingleNNTrainingPlan : public AbstractLearningRuleTrainingPlan
{
	template <class Archive>
	friend void save(Archive& archive, AbstractSingleNNTrainingPlan const& trainingPlan);
	template <class Archive>
	friend void load(Archive& archive, AbstractSingleNNTrainingPlan& trainingPlan);
protected:
	AbstractNeuralNetwork* network;
	virtual AbstractNeuralNetwork* createNeuralNetwork() = 0;
	void fillDefaultLearningRuleOptions(AbstractSupervisedLearningRuleOptions* options);
public:
	AbstractSingleNNTrainingPlan();
	void initializeStart();
	AbstractNeuralNetwork* getNeuralNetwork();
	virtual int getRequiredInputSize() = 0;
	virtual int getRequiredOutputSize() = 0;
	void setNeuralNetwork(AbstractNeuralNetwork* network_);
};

#include "IO/AbstractSingleNNTrainingPlanIO.hpp"

#endif
