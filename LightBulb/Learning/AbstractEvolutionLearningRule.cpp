// Includes
#include "Learning/AbstractEvolutionLearningRule.hpp"
#include "NeuralNetwork/AbstractNeuralNetwork.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
#include "Teaching/Teacher.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
// Library includes
#include <iomanip>
#include <vector>

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
