#pragma once

#ifndef _ABSTRACTSINGLENNTRAININGPLAN_H_
#define _ABSTRACTSINGLENNTRAININGPLAN_H_

// Includes
#include "TrainingPlans/AbstractLearningRuleTrainingPlan.hpp"

// Library includes

namespace LightBulb
{
	// Forward declarations
	class AbstractNeuralNetwork;
	struct AbstractSupervisedLearningRuleOptions;

	class AbstractSingleNNTrainingPlan : public AbstractLearningRuleTrainingPlan
	{
		template <class Archive>
		friend void save(Archive& archive, AbstractSingleNNTrainingPlan const& trainingPlan);
		template <class Archive>
		friend void load(Archive& archive, AbstractSingleNNTrainingPlan& trainingPlan);
	protected:
		AbstractNeuralNetwork* network;
		virtual AbstractNeuralNetwork* createNeuralNetwork() = 0;
		void fillDefaultLearningRuleOptions(AbstractSupervisedLearningRuleOptions* options) const;
	public:
		AbstractSingleNNTrainingPlan();
		void initializeStart() override;
		AbstractNeuralNetwork* getNeuralNetwork();
		virtual int getRequiredInputSize() const = 0;
		virtual int getRequiredOutputSize() const = 0;
		void setNeuralNetwork(AbstractNeuralNetwork* network_);
	};
}

#include "IO/AbstractSingleNNTrainingPlanIO.hpp"

#endif
