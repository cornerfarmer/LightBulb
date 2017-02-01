#include "LightBulbExamplePrec.hpp"
#include "FunctionEvolutionExample.hpp"
#include <LightBulb/Learning/Evolution/EvolutionLearningRule.hpp>
#include <LightBulb/Learning/Evolution/EvolutionStrategy/MutationAlgorithm.hpp>
#include <Examples/FunctionEvolution/FunctionSimulator.hpp>
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/Evolution/EvolutionLearningRulePreferenceGroup.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"

using namespace LightBulb;

static void sixHumpCamelFunction(const LightBulb::Vector<>& pos, LightBulb::Scalar<>& value, const CalculatorType& calculatorType)
{
	if (calculatorType == CT_GPU)
	{
		static viennacl::ocl::kernel& kernel = getKernel("function_evolution_example", "six_hump_camel_function", "function_evolution_example.cl");

		viennacl::ocl::enqueue(kernel(
			viennacl::traits::opencl_handle(pos.getViennaclValue()),
			viennacl::traits::opencl_handle(value.getViennaclValueForEditing())
		));

	}
	else
	{
		value.getEigenValueForEditing() = -1 * (4 * pow(pos.getEigenValue()[0], 2) - 2.1 * pow(pos.getEigenValue()[0], 4) + pow(pos.getEigenValue()[0], 6) / 3 + pos.getEigenValue()[0] * pos.getEigenValue()[1] - 4 * pow(pos.getEigenValue()[1], 2) + 4 * pow(pos.getEigenValue()[1], 4));
	}
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

