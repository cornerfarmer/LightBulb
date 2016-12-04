#include "FunctionEvolutionExample.hpp"
#include <LightBulb/Learning/Evolution/EvolutionLearningRule.hpp>
#include <LightBulb/Learning/Evolution/EvolutionStrategy/MutationAlgorithm.hpp>
#include <Examples/FunctionEvolution/FunctionSimulator.hpp>
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/Evolution/EvolutionLearningRulePreferenceGroup.hpp"

using namespace LightBulb;

static double sixHumpCamelFunction(std::vector<float> pos)
{
	return -1 * (4 * pow(pos[0], 2) - 2.1 * pow(pos[0], 4) + pow(pos[0], 6) / 3 + pos[0] * pos[1] - 4 * pow(pos[1], 2) + 4 * pow(pos[1], 4));
}

AbstractLearningRule* FunctionEvolutionExample::createLearningRate()
{
	EvolutionLearningRuleOptions options = createOptions<EvolutionLearningRuleOptions, EvolutionLearningRulePreferenceGroup>();
	fillDefaultLearningRuleOptions(options);

	return new EvolutionLearningRule(options);
}

AbstractEvolutionEnvironment* FunctionEvolutionExample::createEnvironment()
{
	FunctionSimulatorOptions simulatorOptions;
	simulatorOptions.enableGraphics = false;

	return new FunctionSimulator(simulatorOptions, sixHumpCamelFunction);
}

FunctionEvolutionExample::FunctionEvolutionExample()
{
	addPreferenceGroup(new EvolutionLearningRulePreferenceGroup());
}

std::string FunctionEvolutionExample::getOriginalName() const
{
	return "Function evolution example";
}

std::string FunctionEvolutionExample::getDescription() const
{
	return "Finds the minimum of the six hump camel back function with the help of evolution!";
}

AbstractTrainingPlan* FunctionEvolutionExample::createNewFromSameType() const
{
	return new FunctionEvolutionExample();
}

std::string FunctionEvolutionExample::getLearningRuleName() const
{
	return EvolutionLearningRule::getName();
}

