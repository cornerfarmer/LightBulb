#include "TeachedEvolutionExample.hpp"
#include <LightBulb/Learning/Evolution/RateDifferenceCondition.hpp>
#include <LightBulb/Learning/Evolution/ConstantMutationCommand.hpp>
#include <LightBulb/Learning/Evolution/EvolutionStrategy/MutationAlgorithm.hpp>
#include <LightBulb/Learning/Evolution/BestSelectionCommand.hpp>
#include <LightBulb/Learning/Evolution/ConstantReuseCommand.hpp>
#include <LightBulb/Learning/Evolution/ConstantRecombinationCommand.hpp>
#include <LightBulb/Learning/Evolution/EvolutionStrategy/RecombinationAlgorithm.hpp>
#include <LightBulb/Learning/Evolution/ConstantCreationCommand.hpp>
#include <LightBulb/Learning/Evolution/EvolutionLearningRule.hpp>
#include <LightBulb/Teaching/TeachingLessonBooleanInput.hpp>
#include <LightBulb/Teaching/Teacher.hpp>
#include <LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp>
#include <LightBulb/NeuronDescription/DifferentNeuronDescriptionFactory.hpp>
#include <LightBulb/Function/InputFunction/WeightedSumFunction.hpp>
#include <LightBulb/Function/ActivationFunction/FermiFunction.hpp>
#include <LightBulb/Learning/Evolution/TeachingEvolutionEnvironment.hpp>
#include <LightBulb/Learning/Evolution/RandomSelector.hpp>
#include <LightBulb/NeuronDescription/NeuronDescription.hpp>
#include <LightBulb/Learning/Evolution/BestReuseSelector.hpp>
#include <LightBulb/Learning/Evolution/FitnessCondition.hpp>
#include "LightBulb/Function/RandomFunction/RankBasedRandomFunction.hpp"

using namespace LightBulb;

AbstractLearningRule* TeachedEvolutionExample::createLearningRate()
{
	

	EvolutionLearningRuleOptions options;
	RateDifferenceCondition* rateDifferenceCondition = new RateDifferenceCondition(0.00001, 50);
	options.exitConditions.push_back(rateDifferenceCondition);
	options.exitConditions.push_back(new FitnessCondition(-0.1));
	ConstantCreationCommand* constantCreationCommand = new ConstantCreationCommand(80);
	options.creationCommands.push_back(constantCreationCommand);
	options.reuseCommands.push_back(new ConstantReuseCommand(new BestReuseSelector(), 1));
	BestSelectionCommand* bestSelectionCommand = new BestSelectionCommand(80);
	options.selectionCommands.push_back(bestSelectionCommand);
	MutationAlgorithm* mutationAlgorithm = new MutationAlgorithm(1.6);
	ConstantMutationCommand* constantMutationCommand = new ConstantMutationCommand(mutationAlgorithm, new RandomSelector(new RankBasedRandomFunction()), 2.0);
	options.mutationsCommands.push_back(constantMutationCommand);
	options.recombinationCommands.push_back(new ConstantRecombinationCommand(new RecombinationAlgorithm(), new RandomSelector(new RankBasedRandomFunction()), 0));
	options.maxTries = 100;
	fillDefaultLearningRuleOptions(options);

	return new EvolutionLearningRule(options);
}

AbstractEvolutionEnvironment* TeachedEvolutionExample::createEnvironment()
{
	FeedForwardNetworkTopologyOptions networkTopologyOptions;
	networkTopologyOptions.descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)), new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)));
	networkTopologyOptions.neuronsPerLayerCount = std::vector<unsigned int>(3);
	networkTopologyOptions.neuronsPerLayerCount[0] = 8;
	networkTopologyOptions.neuronsPerLayerCount[1] = 3;
	networkTopologyOptions.neuronsPerLayerCount[2] = 8;
	networkTopologyOptions.useBiasNeuron = true;

	Teacher* teacher = new Teacher();
	for (int i = 0; i<8; i += 1)
	{
		std::vector<double> teachingPattern(8);
		TeachingInput<bool>* teachingInput = new TeachingInput<bool>(8);
		for (int l = 0; l<8; l += 1)
		{
			teachingPattern[l] = i == l;
			(*teachingInput).set(l, i == l);
		}

		teacher->addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));
	}


	return new TeachingEvolutionEnvironment(teacher, networkTopologyOptions);
}

std::string TeachedEvolutionExample::getOriginalName() const
{
	return "Teached evolution example";
}

std::string TeachedEvolutionExample::getDescription() const
{
	return "Teaches the famous 8-3-8 en/decoder problem with the help of evoultion.";
}

AbstractTrainingPlan* TeachedEvolutionExample::createNewFromSameType() const
{
	return new TeachedEvolutionExample();
}

std::string TeachedEvolutionExample::getLearningRuleName() const
{
	return EvolutionLearningRule::getName();
}

