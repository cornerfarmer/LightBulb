// Includes
#include "Learning/Reinforcement/MonteCarloLearningRule.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
// Library includes
#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <Learning/EvolutionLearningResult.hpp>
#include <Learning/Evolution/EvolutionLearningRule.hpp>
#include "AbstractReinforcementWorld.hpp"
#include <Teaching/TeachingLessonLinearInput.hpp>

AbstractLearningResult* MonteCarloLearningRule::getLearningResult()
{
	EvolutionLearningResult* learningResult = new EvolutionLearningResult();
	
	return learningResult;
}

MonteCarloLearningRule::MonteCarloLearningRule(MonteCarloLearningRuleOptions& options_)
	: AbstractReinforcementLearningRule(new MonteCarloLearningRuleOptions(options_))
{
	initialize();
}

MonteCarloLearningRule::MonteCarloLearningRule(MonteCarloLearningRuleOptions* options_)
	: AbstractReinforcementLearningRule(options_)
{
	initialize();
}

MonteCarloLearningRule::MonteCarloLearningRule()
	: AbstractReinforcementLearningRule(new MonteCarloLearningRuleOptions())
{
	initialize();
}

void MonteCarloLearningRule::initializeTry()
{
	getOptions()->world->setLearningState(learningState.get());
	getOptions()->world->initializeForLearning();
}

void MonteCarloLearningRule::initialize()
{
	GradientDecentLearningRuleOptions options;
	options.maxIterationsPerTry = 1000;
	options.maxTries = 1;
	options.changeWeightsBeforeLearning = false;
	options.teacher = &teacher;
	options.neuralNetwork = getOptions()->world->getNeuralNetwork();
	options.logger = getOptions()->logger;
	gradientDecentLearningRule.reset(new GradientDecentLearningRule(options));
}

void MonteCarloLearningRule::addTrainingPattern(AbstractNetworkTopology* networkTopology, double reward)
{
	auto patternVector = networkTopology->getActivationVector(0);
	teachingPatterns.push_back(std::vector<double>(patternVector.data(), patternVector.data() + patternVector.size()));

	teachingInputs.resize(teachingInputs.size() + 1, std::vector<double>(networkTopology->getOutputSize()));
	networkTopology->getOutput(teachingInputs.back());
	
	for (int i = 0; i < getOptions()->world->getLastBooleanOutput().size(); i++)
	{
		if (getOptions()->world->getLastBooleanOutput()[i])
		{
			chosenActions.push_back(i);
			break;
		}
	}

	teachingInputs.back()[chosenActions.back()] = 0;

	for (int i = teachingInputs.size() - 1; i >= 0; i--)
	{
		teachingInputs[i][chosenActions[i]] += reward;
		reward *= getOptions()->discountingFactor;
	}
}

void MonteCarloLearningRule::doSupervisedLearning()
{
	if (teacher.getTeachingLessons()->size() == 0) {
		teacher.getTeachingLessons()->clear();

		for (int i = 0; i < teachingInputs.size(); i++)
		{
			NeuralNetworkIO<double>* input = new NeuralNetworkIO<double>(teachingInputs[i].size());
			for (int j = 0; j < teachingInputs[i].size(); j++)
				input->set(0, j, teachingInputs[i][j]);
			teacher.addTeachingLesson(new TeachingLessonLinearInput(std::vector<std::vector<double>>(1, teachingPatterns[i]), input));
		}
	}
	
	initialize();
	auto result = gradientDecentLearningRule->start();
	learningState->addData(DATA_SET_TRAINING_ERROR, result->quality);

	teachingPatterns.clear();
	teachingInputs.clear();
	chosenActions.clear();
}

std::string MonteCarloLearningRule::getName()
{
	return "MonteCarloLearningRule";
}

std::vector<std::string> MonteCarloLearningRule::getDataSetLabels()
{
	std::vector<std::string> labels = AbstractReinforcementLearningRule::getDataSetLabels();
	labels.push_back(DATA_SET_TRAINING_ERROR);
	return labels;
}

bool MonteCarloLearningRule::doIteration()
{
	int rewardCounter = 0;
	double totalReward = 0;
	AbstractNetworkTopology* networkTopology = getOptions()->world->getNeuralNetwork()->getNetworkTopology();

	while (true)
	{
		double reward = getOptions()->world->doSimulationStep();
		
		addTrainingPattern(networkTopology, reward);

		if (reward != 0)
			break;
	}

	learningState->addData(DATA_SET_REWARD, totalReward);

	doSupervisedLearning();
		
	// Continue with the next generation
	learningState->iterations++;

	getOptions()->world->rateKI();	

	return true;
}


MonteCarloLearningRuleOptions* MonteCarloLearningRule::getOptions()
{
	return static_cast<MonteCarloLearningRuleOptions*>(options.get());
}

