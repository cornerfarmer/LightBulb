// Includes
#include "Learning/Evolution/AbstractEvolutionLearningRule.hpp"
#include "NeuralNetwork/AbstractNeuralNetwork.hpp"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "Teaching/Teacher.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
// Library includes
#include <iomanip>
#include <vector>

namespace LightBulb
{
	const AbstractEvolutionLearningRuleOptions& AbstractEvolutionLearningRule::getOptions() const
	{
		return static_cast<AbstractEvolutionLearningRuleOptions&>(*options.get());
	}

	AbstractEvolutionLearningRule::AbstractEvolutionLearningRule(AbstractEvolutionLearningRuleOptions& options_)
		: AbstractLearningRule(new AbstractEvolutionLearningRuleOptions(options_))
	{
	}

	AbstractEvolutionLearningRule::AbstractEvolutionLearningRule(AbstractEvolutionLearningRuleOptions* options_)
		: AbstractLearningRule(options_)
	{
	}

	std::vector<std::string> AbstractEvolutionLearningRule::getDataSetLabels() const
	{
		return AbstractLearningRule::getDataSetLabels();
	}

	const AbstractEvolutionWorld& AbstractEvolutionLearningRule::getWorld() const
	{
		return *static_cast<AbstractEvolutionLearningRuleOptions*>(options.get())->world;
	}

	AbstractEvolutionWorld& AbstractEvolutionLearningRule::getWorld()
	{
		return *static_cast<AbstractEvolutionLearningRuleOptions*>(options.get())->world;
	}
}
