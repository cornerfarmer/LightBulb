// Includes
#include "Learning/Reinforcement/AbstractReinforcementLearningRule.hpp"
// Library includes
#include "AbstractReinforcementWorld.hpp"

namespace LightBulb
{
	AbstractReinforcementLearningRule::AbstractReinforcementLearningRule(AbstractReinforcementLearningRuleOptions* options_)
		: AbstractLearningRule(options_)
	{
		randomGeneretorHasChanged();
	}

	void AbstractReinforcementLearningRule::randomGeneretorHasChanged()
	{
		if (getOptions().world)
			getOptions().world->setRandomGenerator(*randomGenerator.get());
	}

	bool AbstractReinforcementLearningRule::hasLearningSucceeded()
	{
		return false;
	}

	std::vector<std::string> AbstractReinforcementLearningRule::getDataSetLabels() const
	{
		std::vector<std::string> labels = AbstractLearningRule::getDataSetLabels();
		labels.push_back(DATA_SET_REWARD);
		std::vector<std::string> worldLabels = getOptions().world->getDataSetLabels();
		labels.insert(labels.end(), worldLabels.begin(), worldLabels.end());
		return labels;
	}


	const AbstractReinforcementLearningRuleOptions& AbstractReinforcementLearningRule::getOptions() const
	{
		return static_cast<AbstractReinforcementLearningRuleOptions&>(*options.get());
	}
}