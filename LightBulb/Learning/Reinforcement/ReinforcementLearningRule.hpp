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
	}
};

class ReinforcementLearningRule : public AbstractLearningRule
{
private:
	std::vector<Eigen::MatrixXd> gradients;
	void addGradients(AbstractNetworkTopology* networkTopology);
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
