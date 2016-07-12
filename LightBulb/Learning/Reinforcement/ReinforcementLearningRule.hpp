#pragma once

#ifndef _REINFORCEMENTLEARNINGRULE_H_
#define _REINFORCEMENTLEARNINGRULE_H_

// Includes
#include "Learning/AbstractEvolutionLearningRule.hpp"

// Library Includes
#include <vector>
#include <Learning/ResilientLearningRateHelper.hpp>

class AbstractNetworkTopology;
// Forward declarations
class AbstractReinforcementWorld;

struct ReinforcementLearningRuleOptions : public AbstractLearningRuleOptions
{
	AbstractReinforcementWorld* world;
	ReinforcementLearningRuleOptions()
	{
		world = NULL;
		maxIterationsPerTry = 10000000000;
	}
};

#define DATA_SET_REWARD "Reward"

class ReinforcementLearningRule : public AbstractLearningRule
{
private:
	std::vector<std::vector<Eigen::VectorXd>> netInputRecord;
	std::vector<std::vector<Eigen::VectorXd>> activationRecord;
	std::vector<Eigen::VectorXd> errorVectorRecord;
	std::vector<Eigen::MatrixXd> gradients;

	std::unique_ptr<ResilientLearningRateHelper> resilientLearningRateHelper;
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
	bool doIteration();
	bool hasLearningSucceeded();
	ReinforcementLearningRuleOptions* getOptions();
	void doCalculationAfterLearningProcess();
	AbstractLearningResult* getLearningResult();
public:
	ReinforcementLearningRule(ReinforcementLearningRuleOptions& options_);
	ReinforcementLearningRule(ReinforcementLearningRuleOptions* options_);
	ReinforcementLearningRule();
	// Executes the learning process
	void initializeTry();
	static std::string getName();
	std::vector<std::string> getDataSetLabels();
};


#endif
