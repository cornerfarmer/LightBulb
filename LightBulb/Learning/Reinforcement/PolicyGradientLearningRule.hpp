#pragma once

#ifndef _POLICYGRADIENTLEARNINGRULE_H_
#define _POLICYGRADIENTLEARNINGRULE_H_

// Includes
#include "Learning/Reinforcement/AbstractReinforcementLearningRule.hpp"
#include "Learning/Supervised/GradientCalculation/AbstractGradientCalculation.hpp"
#include "Learning/Supervised/GradientDecentAlgorithms/AbstractGradientDecentAlgorithm.hpp"
#include "Learning/Supervised/GradientDecentAlgorithms/RMSPropLearningRate.hpp"

// Library Includes
#include <vector>

namespace LightBulb
{
	// Forward declarations
	class AbstractNetworkTopology;

	struct PolicyGradientLearningRuleOptions : public AbstractReinforcementLearningRuleOptions
	{
		int episodeSize;
		RMSPropLearningRateOptions rmsPropLearningRateOptions;
		PolicyGradientLearningRuleOptions()
		{
			episodeSize = 10;
			rmsPropLearningRateOptions.deltaWeightsMomentum = 0;
			rmsPropLearningRateOptions.gradientMomentum = 1;
			rmsPropLearningRateOptions.squaredGradientMomentum = 0.99;
			rmsPropLearningRateOptions.learningRate = 1e-4;
			rmsPropLearningRateOptions.minSquaredGradient = 1e-5;
		}
	};

	class PolicyGradientLearningRule : public AbstractReinforcementLearningRule
	{
	private:
		std::vector<std::vector<Eigen::VectorXd>> netInputRecord;
		std::vector<std::vector<Eigen::VectorXd>> activationRecord;
		std::vector<Eigen::VectorXd> errorVectorRecord;
		std::unique_ptr<AbstractGradientCalculation> gradientCalculation;
		std::unique_ptr<AbstractGradientDecentAlgorithm> gradientDecentAlgorithm;

		int stepsSinceLastReward;
		void addGradients(AbstractNetworkTopology* networkTopology);
		void computeGradients(AbstractNetworkTopology* networkTopology, int stepsSinceLastReward, double reward);
		void computeGradientsForError(AbstractNetworkTopology* networkTopology, Eigen::VectorXd& errorVector, std::vector<Eigen::VectorXd>& netInputs, std::vector<Eigen::VectorXd>& activations);
		void initialize();
		void recordStep(AbstractNetworkTopology* networkTopology);
		std::vector<Eigen::MatrixXd> checkGradient(AbstractNetworkTopology* networkTopology);
		Eigen::VectorXd getErrorVector(AbstractNetworkTopology* networkTopology);
	protected:
		bool doIteration() override;
		PolicyGradientLearningRuleOptions* getOptions() override;
		void doCalculationAfterLearningProcess() override;
		AbstractLearningResult* getLearningResult() override;
		void initializeLearningAlgoritm() override;
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
