// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/Learning/Evolution/AbstractEvolutionLearningRule.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/Teaching/AbstractTeachingLesson.hpp"
#include "LightBulb/Random/ZigguratGenerator.hpp"
// Library includes
#include <vector>

namespace LightBulb
{
	const AbstractEvolutionLearningRuleOptions& AbstractEvolutionLearningRule::getOptions() const
	{
		return static_cast<AbstractEvolutionLearningRuleOptions&>(*options.get());
	}

	AbstractEvolutionLearningRule::~AbstractEvolutionLearningRule() = default;


	AbstractEvolutionLearningRule::AbstractEvolutionLearningRule(AbstractEvolutionLearningRuleOptions& options_)
		: AbstractLearningRule(new AbstractEvolutionLearningRuleOptions(options_))
	{
		zigguratGenerator.reset(new ZigguratGenerator(options->seed));
	}

	AbstractEvolutionLearningRule::AbstractEvolutionLearningRule(AbstractEvolutionLearningRuleOptions* options_)
		: AbstractLearningRule(options_)
	{
		zigguratGenerator.reset(new ZigguratGenerator(options->seed));
	}

	std::vector<std::string> AbstractEvolutionLearningRule::getDataSetLabels() const
	{
		return AbstractLearningRule::getDataSetLabels();
	}

	const AbstractEvolutionEnvironment& AbstractEvolutionLearningRule::getEnvironment() const
	{
		return *static_cast<AbstractEvolutionLearningRuleOptions*>(options.get())->environment;
	}

	AbstractEvolutionEnvironment& AbstractEvolutionLearningRule::getEnvironment()
	{
		return *static_cast<AbstractEvolutionLearningRuleOptions*>(options.get())->environment;
	}
}
