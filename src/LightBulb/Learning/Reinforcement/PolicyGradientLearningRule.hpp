#pragma once

#ifndef _POLICYGRADIENTLEARNINGRULE_H_
#define _POLICYGRADIENTLEARNINGRULE_H_

// Includes
#include "Learning/Reinforcement/AbstractReinforcementLearningRule.hpp"
#include "Learning/Supervised/GradientCalculation/AbstractGradientCalculation.hpp"
#include "Learning/Supervised/GradientDescentAlgorithms/AbstractGradientDescentAlgorithm.hpp"
#include "Learning/Supervised/GradientDescentAlgorithms/RMSPropLearningRate.hpp"

// Library Includes
#include <vector>

namespace LightBulb
{
	// Forward declarations
	class AbstractNetworkTopology;

	struct PolicyGradientLearningRuleOptions : public AbstractReinforcementLearningRuleOptions
	{
		int episodeSize;
		int ratingInterval;
		RMSPropLearningRateOptions rmsPropLearningRateOptions;
		RMSPropLearningRateOptions valueRmsPropLearningRateOptions;
		bool valueFunctionAsBase;
		PolicyGradientLearningRuleOptions()
		{
			episodeSize = 10;
			ratingInterval = 10;
			rmsPropLearningRateOptions.learningRate = 1e-4;
			valueFunctionAsBase = true;
		}
	};

	#define DATA_SET_ERROR_AVG "Error avg"
	#define DATA_SET_VALUE_ERROR_AVG "Value error avg"

	class PolicyGradientLearningRule : public AbstractReinforcementLearningRule
	{
	private:
		std::vector<std::vector<double>> stateRecord;
		std::vector<std::vector<Eigen::MatrixXd>> gradientRecord;
		std::vector<Eigen::MatrixXd> gradient;
		std::unique_ptr<AbstractGradientCalculation> gradientCalculation;
		std::unique_ptr<AbstractGradientDescentAlgorithm> gradientDescentAlgorithm;
		std::unique_ptr<AbstractGradientCalculation> valueFunctionGradientCalculation;
		std::unique_ptr<AbstractGradientDescentAlgorithm> valueFunctionGradientDescentAlgorithm;
		std::unique_ptr<AbstractNeuralNetwork> valueFunctionNetwork;
		std::vector<double> lastOutput;
		double errorSum;
		double valueErrorSum;
		int stepsSinceLastReward;
		int errorSteps;
		int valueErrorSteps;
		void addGradients(AbstractNetworkTopology& networkTopology);
		void computeGradients(AbstractNetworkTopology& networkTopology, int stepsSinceLastReward, double reward);
		void computeGradientsForError(AbstractNetworkTopology& networkTopology, Eigen::VectorXd& errorVector, std::vector<Eigen::VectorXd>& netInputs, std::vector<Eigen::VectorXd>& activations);
		void initialize(PolicyGradientLearningRuleOptions& options);
		void recordStep(AbstractNetworkTopology& networkTopology);
		void getErrorVector(AbstractNetworkTopology& networkTopology, Eigen::VectorXd& errorVector);
	protected:
		bool doIteration() override;
		const PolicyGradientLearningRuleOptions& getOptions() const override;
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
		std::vector<std::string> getDataSetLabels() const override;
	};
}


#endif
