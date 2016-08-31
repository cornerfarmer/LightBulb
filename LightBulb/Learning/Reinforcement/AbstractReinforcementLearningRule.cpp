// Includes
#include "Learning/Reinforcement/AbstractReinforcementLearningRule.hpp"
// Library includes
#include "AbstractReinforcementWorld.hpp"

AbstractReinforcementLearningRule::AbstractReinforcementLearningRule(AbstractReinforcementLearningRuleOptions* options_)
	: AbstractLearningRule(options_)
{
	options_->world->setRandomGenerator(randomGenerator.get());
}


bool AbstractReinforcementLearningRule::hasLearningSucceeded()
{
	return false;
}

std::vector<std::string> AbstractReinforcementLearningRule::getDataSetLabels()
{
	std::vector<std::string> labels = AbstractLearningRule::getDataSetLabels();
	labels.push_back(DATA_SET_REWARD);
	std::vector<std::string> worldLabels = getOptions()->world->getDataSetLabels();
	labels.insert(labels.end(), worldLabels.begin(), worldLabels.end());
	return labels;
}


AbstractReinforcementLearningRuleOptions* AbstractReinforcementLearningRule::getOptions()
{
	return static_cast<AbstractReinforcementLearningRuleOptions*>(options.get());
}
