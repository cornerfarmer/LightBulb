// Includes
#include "Learning/AbstractEvolutionLearningRule.hpp"
#include "NeuralNetwork/AbstractNeuralNetwork.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
#include "Teaching/Teacher.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
// Library includes
#include <iomanip>
#include <vector>

AbstractEvolutionLearningRuleOptions* AbstractEvolutionLearningRule::getOptions()
{
	return static_cast<AbstractEvolutionLearningRuleOptions*>(options.get());
}

AbstractEvolutionLearningRule::AbstractEvolutionLearningRule(AbstractEvolutionLearningRuleOptions& options_)
	: AbstractLearningRule(new AbstractEvolutionLearningRuleOptions(options_))
{
}

AbstractEvolutionLearningRule::AbstractEvolutionLearningRule(AbstractEvolutionLearningRuleOptions* options_)
	: AbstractLearningRule(options_)
{
}

std::vector<std::string> AbstractEvolutionLearningRule::getDataSetLabels()
{
	return AbstractLearningRule::getDataSetLabels();
}

AbstractEvolutionWorld* AbstractEvolutionLearningRule::getWorld()
{
	return getOptions()->world;
}
