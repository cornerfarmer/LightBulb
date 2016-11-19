#include "TeachedEvolutionExample.hpp"
#include <Learning/Evolution/RateDifferenceCondition.hpp>
#include <Learning/Evolution/ConstantMutationCommand.hpp>
#include <Learning/Evolution/EvolutionStrategy/MutationAlgorithm.hpp>
#include <Learning/Evolution/BestSelectionCommand.hpp>
#include <Learning/Evolution/ConstantReuseCommand.hpp>
#include <Learning/Evolution/ConstantRecombinationCommand.hpp>
#include <Learning/Evolution/EvolutionStrategy/RecombinationAlgorithm.hpp>
#include <Learning/Evolution/ConstantCreationCommand.hpp>
#include <Learning/Evolution/EvolutionLearningRule.hpp>
#include <Teaching/TeachingLessonBooleanInput.hpp>
#include <Teaching/Teacher.hpp>
#include <NetworkTopology/FeedForwardNetworkTopology.hpp>
#include <NeuronDescription/DifferentNeuronDescriptionFactory.hpp>
#include <Function/InputFunction/WeightedSumFunction.hpp>
#include <Function/ActivationFunction/FermiFunction.hpp>
#include <Learning/Evolution/TeachingEvolutionEnvironment.hpp>
#include <Learning/Evolution/RandomSelector.hpp>
#include <NeuronDescription/NeuronDescription.hpp>
#include <Learning/Evolution/BestReuseSelector.hpp>
#include <Learning/Evolution/ScoreCondition.hpp>

using namespace LightBulb;

AbstractLearningRule* TeachedEvolutionExample::createLearningRate()
{
	

	EvolutionLearningRuleOptions options;
	RateDifferenceCondition* rateDifferenceCondition = new RateDifferenceCondition(0.00001, 50);
	options.exitConditions.push_back(rateDifferenceCondition);
	options.exitConditions.push_back(new ScoreCondition(-0.1));
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

