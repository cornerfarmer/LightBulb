#pragma once

#ifndef _POLICYGRADIENTLEARNINGRULE_H_
#define _POLICYGRADIENTLEARNINGRULE_H_

// Includes
#include "Learning/Reinforcement/AbstractReinforcementLearningRule.hpp"

// Library Includes
#include <vector>

namespace LightBulb
{
	// Forward declarations
	class AbstractNetworkTopology;

	struct PolicyGradientLearningRuleOptions : public AbstractReinforcementLearningRuleOptions
	{
		int episodeSize;
		PolicyGradientLearningRuleOptions()
		{
			episodeSize = 10;
		}
	};

#define DATA_SET_GRADIENT "Gradient"

	class PolicyGradientLearningRule : public AbstractReinforcementLearningRule
	{
	private:
		std::vector<std::vector<Eigen::VectorXd>> netInputRecord;
		std::vector<std::vector<Eigen::VectorXd>> activationRecord;
		std::vector<Eigen::VectorXd> errorVectorRecord;
		std::vector<Eigen::MatrixXd> gradients;

		int stepsSinceLastReward;
		void addGradients(AbstractNetworkTopology* networkTopology, std::vector<Eigen::MatrixXd>& gradients);
		void computeGradients(AbstractNetworkTopology* networkTopology, int stepsSinceLastReward, double reward);
		void computeGradientsForError(AbstractNetworkTopology* networkTopology, Eigen::VectorXd& errorVector, std::vector<Eigen::VectorXd>& netInputs, std::vector<Eigen::VectorXd>& activations);
		void resetGradients();
		void initialize();
		void recordStep(AbstractNetworkTopology* networkTopology);
		std::vector<Eigen::MatrixXd> checkGradient(AbstractNetworkTopology* networkTopology);
		Eigen::VectorXd getErrorVector(AbstractNetworkTopology* networkTopology);
	protected:
		bool doIteration() override;
		PolicyGradientLearningRuleOptions* getOptions() override;
		void doCalculationAfterLearningProcess() override;
		AbstractLearningResult* getLearningResult() override;
	public:
		PolicyGradientLearningRule(PolicyGradientLearningRuleOptions& options_);
		PolicyGradientLearningRule(PolicyGradientLearningRuleOptions* options_);
		PolicyGradientLearningRule();
		// Executes the learning process
		void initializeTry() override;
		static std::string getName();
		std::vector<std::string> getDataSetLabels() override;
	};
}


#endif
