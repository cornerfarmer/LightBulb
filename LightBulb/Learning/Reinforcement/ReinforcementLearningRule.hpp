#pragma once

#ifndef _REINFORCEMENTLEARNINGRULE_H_
#define _REINFORCEMENTLEARNINGRULE_H_

// Includes
#include "Learning/AbstractEvolutionLearningRule.hpp"

// Library Includes
#include <vector>

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
	std::vector<Eigen::MatrixXd> gradientsPositive;
	std::vector<Eigen::MatrixXd> gradientsNegative;
	int stepsSinceLastReward;
	void addGradients(AbstractNetworkTopology* networkTopology, std::vector<Eigen::MatrixXd>& gradients);
	void computeGradients(AbstractNetworkTopology* networkTopology);
	void computeGradientsForError(AbstractNetworkTopology* networkTopology, Eigen::VectorXd& errorVector, std::vector<Eigen::MatrixXd>& gradients);
	void resetGradients();
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
