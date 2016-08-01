// Includes
#include "Learning/Reinforcement/DQNLearningRule.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
// Library includes
#include <Learning/EvolutionLearningResult.hpp>
#include "AbstractReinforcementWorld.hpp"
#include <Teaching/TeachingLessonLinearInput.hpp>
#include <ActivationOrder/TopologicalOrder.hpp>

AbstractLearningResult* DQNLearningRule::getLearningResult()
{
	EvolutionLearningResult* learningResult = new EvolutionLearningResult();
	
	return learningResult;
}

DQNLearningRule::DQNLearningRule(DQNLearningRuleOptions& options_)
	: AbstractReinforcementLearningRule(new DQNLearningRuleOptions(options_))
{
	initialize();
}

DQNLearningRule::DQNLearningRule(DQNLearningRuleOptions* options_)
	: AbstractReinforcementLearningRule(options_)
{
	initialize();
}

DQNLearningRule::DQNLearningRule()
	: AbstractReinforcementLearningRule(new DQNLearningRuleOptions())
{
	initialize();
}

void DQNLearningRule::initializeTry()
{
	getOptions()->world->setLearningState(learningState.get());
	getOptions()->world->initializeForLearning();
	nextTransitionIndex = 0;
	waitUntilLearningStarts = 50000;
}

void DQNLearningRule::initialize()
{
	BackpropagationLearningRuleOptions options;
	options.resilientLearningRate = false;
	options.maxIterationsPerTry = 10;
	options.maxTries = 1;
	options.changeWeightsBeforeLearning = false;
	options.teacher = &teacher;
	options.neuralNetwork = getOptions()->world->getNeuralNetwork();
	options.logger = getOptions()->logger;
	options.resilientLearningRate = true;
	backpropagationLearningRule.reset(new BackpropagationLearningRule(options));

	steadyNetwork.reset(getOptions()->world->getNeuralNetwork()->clone());
}

void DQNLearningRule::storeTransition(AbstractNetworkTopology* networkTopology, double reward)
{
	Transition transition;
	auto patternVector = networkTopology->getActivationVector(0);
	transition.state = std::vector<double>(patternVector.data() + networkTopology->usesBiasNeuron(), patternVector.data() + patternVector.size());

	if (reward == 0) {
		 getOptions()->world->getNNInput(transition.nextState);
	}

	transition.reward = reward;	
	
	for (int i = 0; i < getOptions()->world->getLastBooleanOutput().size(); i++)
	{
		if (getOptions()->world->getLastBooleanOutput()[i])
		{
			transition.action = i;
			break;
		}
	}

	if (transitions.size() < 1000000)
	{
		transitions.push_back(transition);
	} 
	else
	{
		transitions[nextTransitionIndex++] = transition;
		nextTransitionIndex %= transitions.size();
	}

}

void DQNLearningRule::doSupervisedLearning()
{
	teacher.getTeachingLessons()->clear();

	for (int i = 0; i < 32; i++)
	{
		int r = rand() % transitions.size();

		double y = transitions[r].reward;

		if (!transitions[r].nextState.empty())
		{
			std::vector<double> output(steadyNetwork->getNetworkTopology()->getOutputSize());
			steadyNetwork->calculate(transitions[r].nextState, output, TopologicalOrder());
			double q = *std::max_element(output.begin(), output.end());
			y += 0.99 * q;
		}

		NeuralNetworkIO<double>* input = new NeuralNetworkIO<double>(steadyNetwork->getNetworkTopology()->getOutputSize());

		input->set(0, transitions[r].action, y);

		teacher.addTeachingLesson(new TeachingLessonLinearInput(std::vector<std::vector<double>>(1, transitions[r].state), input));
	}


	auto result = backpropagationLearningRule->start();
	learningState->addData(DATA_SET_TRAINING_ERROR, result->quality);
}

std::string DQNLearningRule::getName()
{
	return "DQNLearningRule";
}

std::vector<std::string> DQNLearningRule::getDataSetLabels()
{
	std::vector<std::string> labels = AbstractReinforcementLearningRule::getDataSetLabels();
	labels.push_back(DATA_SET_TRAINING_ERROR);
	return labels;
}

bool DQNLearningRule::doIteration()
{
	int rewardCounter = 0;
	double totalReward = 0;
	AbstractNetworkTopology* networkTopology = getOptions()->world->getNeuralNetwork()->getNetworkTopology();

	for (int i = 0; i < 10000; i++) {
		double reward = getOptions()->world->doSimulationStep();

		storeTransition(networkTopology, reward);

		learningState->addData(DATA_SET_REWARD, totalReward);

		if (waitUntilLearningStarts > 0)
			waitUntilLearningStarts--;
		else
			doSupervisedLearning();

		double e = getOptions()->world->getEpsilon();
		if (e > 0.1)
			getOptions()->world->setEpsilon(e - 0.9 / 1000000);
	}
		
	steadyNetwork->getNetworkTopology()->copyWeightsFrom(*getOptions()->world->getNeuralNetwork()->getNetworkTopology());


	// Continue with the next generation
	learningState->iterations++;

	getOptions()->world->rateKI();	

	return true;
}


DQNLearningRuleOptions* DQNLearningRule::getOptions()
{
	return static_cast<DQNLearningRuleOptions*>(options.get());
}

