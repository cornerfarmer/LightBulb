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
#include <NetworkTopology/LayeredNetwork.hpp>
#include <NeuronFactory/DifferentNeuronDescriptionFactory.hpp>
#include <Function/WeightedSumFunction.hpp>
#include <Function/FermiFunction.hpp>
#include <Learning/Evolution/TeachingEvolutionWorld.hpp>
#include <Learning/Evolution/RandomSelector.hpp>
#include <Neuron/NeuronDescription.hpp>
#include <Learning/Evolution/BestReuseSelector.hpp>
#include <Learning/Evolution/ScoreCondition.hpp>

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
	fillDefaultLearningRuleOptions(&options);

	return new EvolutionLearningRule(options);
}

AbstractEvolutionWorld* TeachedEvolutionExample::createWorld()
{
	LayeredNetworkOptions* layeredNetworkOptions = new LayeredNetworkOptions();
	layeredNetworkOptions->descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)), new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)));
	layeredNetworkOptions->neuronsPerLayerCount = std::vector<unsigned int>(3);
	layeredNetworkOptions->neuronsPerLayerCount[0] = 8;
	layeredNetworkOptions->neuronsPerLayerCount[1] = 3;
	layeredNetworkOptions->neuronsPerLayerCount[2] = 8;
	layeredNetworkOptions->useBiasNeuron = true;

	Teacher* teacher = new Teacher();
	for (int i = 0; i<8; i += 1)
	{
		std::vector<std::vector<double>> teachingPattern(1, std::vector<double>(8));
		NeuralNetworkIO<bool>* teachingInput = new NeuralNetworkIO<bool>(8);
		for (int l = 0; l<8; l += 1)
		{
			teachingPattern[0][l] = i == l;
			(*teachingInput).set(0, l, i == l);
		}

		teacher->addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));
	}


	return new TeachingEvolutionWorld(teacher, *layeredNetworkOptions);
}

std::string TeachedEvolutionExample::getDefaultName()
{
	return "Teached evolution example";
}

std::string TeachedEvolutionExample::getDescription()
{
	return "Teaches the famous 8-3-8 en/decoder problem with the help of evoultion.";
}

AbstractTrainingPlan* TeachedEvolutionExample::getCopy()
{
	return new TeachedEvolutionExample();
}

std::string TeachedEvolutionExample::getLearningRuleName()
{
	return EvolutionLearningRule::getName();
}

