#include "FunctionEvolutionExample.hpp"
#include "Examples/FunctionEvolution/FunctionSimulator.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"
#include "LightBulb/Learning/Evolution/EvolutionLearningRule.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/Evolution/EvolutionLearningRulePreferenceGroup.hpp"

using namespace LightBulb;

void FunctionEvolutionExample::sixHumpCamelFunction(const LightBulb::Vector<>& pos, LightBulb::Scalar<>& value, const CalculatorType& calculatorType)
{
	if (calculatorType == CT_GPU)
	{
		viennacl::ocl::enqueue(sixHumpCamelFunctionKernel->use()(
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

	return new FunctionSimulator(simulatorOptions, &FunctionEvolutionExample::sixHumpCamelFunction, this);
}

FunctionEvolutionExample::FunctionEvolutionExample()
{
	addPreferenceGroup(new EvolutionLearningRulePreferenceGroup());
	sixHumpCamelFunctionKernel.reset(new Kernel("function_evolution_example", "six_hump_camel_function"));
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

