// Includes
#include "Learning/Reinforcement/DQNLearningRule.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"
// Library includes
#include <Learning/Evolution/EvolutionLearningResult.hpp>
#include "AbstractReinforcementWorld.hpp"
#include <Teaching/TeachingLessonLinearInput.hpp>
#include <ActivationOrder/TopologicalOrder.hpp>

namespace LightBulb
{
	AbstractLearningResult* DQNLearningRule::getLearningResult()
	{
		EvolutionLearningResult* learningResult = new EvolutionLearningResult();

		return learningResult;
	}

	DQNLearningRule::DQNLearningRule(DQNLearningRuleOptions& options_)
		: AbstractReinforcementLearningRule(new DQNLearningRuleOptions(options_))
	{
		initialize(static_cast<DQNLearningRuleOptions*>(options.get()));
	}

	DQNLearningRule::DQNLearningRule(DQNLearningRuleOptions* options_)
		: AbstractReinforcementLearningRule(options_)
	{
		initialize(options_);
	}

	DQNLearningRule::DQNLearningRule()
		: AbstractReinforcementLearningRule(new DQNLearningRuleOptions())
	{
	}
	
	void DQNLearningRule::initialize(DQNLearningRuleOptions* options)
	{
		options->gradientDescentOptions.gradientDescentAlgorithm = new RMSPropLearningRate(options->rmsPropOptions);
		options->gradientDescentOptions.teacher = &teacher;
		options->gradientDescentOptions.neuralNetwork = &getOptions().world->getNeuralNetwork();
		options->gradientDescentOptions.logger = nullptr;
		gradientDescent.reset(new GradientDescentLearningRule(options->gradientDescentOptions));

		steadyNetwork.reset(getOptions().world->getNeuralNetwork().clone());
	}

	void DQNLearningRule::initializeTry()
	{
		getOptions().world->setLearningState(*learningState.get());
		getOptions().world->initializeForLearning();
		steadyNetwork->getNetworkTopology().copyWeightsFrom(getOptions().world->getNeuralNetwork().getNetworkTopology());
		nextTransitionIndex = 0;
		waitUntilLearningStarts = getOptions().replayStartSize;
		getOptions().world->setEpsilon(getOptions().initialExploration);
		currentTotalReward = 0;
	}
	
	void DQNLearningRule::storeTransition(const AbstractNetworkTopology* networkTopology, double reward)
	{
		Transition transition;
		auto patternVector = networkTopology->getActivationsPerLayer(0);
		transition.state = std::vector<double>(patternVector.data() + networkTopology->usesBiasNeuron(), patternVector.data() + patternVector.size());

		if (!getOptions().world->isTerminalState()) {
			getOptions().world->getNNInput(transition.nextState);
		}

		transition.reward = reward;

		for (int i = 0; i < getOptions().world->getLastBooleanOutput().size(); i++)
		{
			if (getOptions().world->getLastBooleanOutput().at(i))
			{
				transition.action = i;
				break;
			}
		}

		if (transitions.size() < getOptions().replayMemorySize)
		{
			transitions.push_back(transition);
		}
		else if (getOptions().replaceStoredTransitions)
		{
			transitions[nextTransitionIndex++] = transition;
			nextTransitionIndex %= transitions.size();
		}

	}

	void DQNLearningRule::doSupervisedLearning()
	{
		teacher.clearLessons();

		for (int i = 0; i < std::min(static_cast<int>(transitions.size()), getOptions().minibatchSize); i++)
		{
			int r = randomGenerator->randInt(0, transitions.size() - 1);

			double y = transitions[r].reward;

			if (!transitions[r].nextState.empty())
			{
				std::vector<double> output(steadyNetwork->getNetworkTopology().getOutputSize());
				steadyNetwork->calculate(transitions[r].nextState, output, TopologicalOrder());
				double q = *max_element(output.begin(), output.end());
				qAvgSum += q;
				y += getOptions().discountFactor * q;
			}

			TeachingInput<double>* input = new TeachingInput<double>(steadyNetwork->getNetworkTopology().getOutputSize());

			input->set(transitions[r].action, y);

			teacher.addTeachingLesson(new TeachingLessonLinearInput(transitions[r].state, input));
		}

		//auto gradient = checkGradient(&teacher, getOptions()->world->getNeuralNetwork()->getNetworkTopology());

		std::unique_ptr<AbstractLearningResult> result(gradientDescent->start());
		currentTotalError += result->quality;
	}

	std::string DQNLearningRule::getName()
	{
		return "DQNLearningRule";
	}

	std::vector<std::string> DQNLearningRule::getDataSetLabels() const
	{
		std::vector<std::string> labels = AbstractReinforcementLearningRule::getDataSetLabels();
		labels.push_back(DATA_SET_TRAINING_ERROR);
		labels.push_back(DATA_SET_EPSILON);
		labels.push_back(DATA_SET_Q_VALUE);
		labels.push_back(DATA_SET_AVG_Q_VALUE);
		return labels;
	}


	bool DQNLearningRule::doIteration()
	{
		currentTotalError = 0;
		double totalReward = 0;
		int totalEpisodes = 0;
		bool nextIsStartingState = true;
		double totalQ = 0;
		int totalQValues = 0;
		bool skipNextTotalReward = currentTotalReward == -1;
		qAvgSum = 0;

		AbstractNetworkTopology& networkTopology = getOptions().world->getNeuralNetwork().getNetworkTopology();

		for (int i = 0; i < getOptions().targetNetworkUpdateFrequency; i++) {
			double reward = getOptions().world->doSimulationStep();
			currentTotalReward += reward;

			if (nextIsStartingState)
			{
				std::vector<double> output(getOptions().world->getNeuralNetwork().getNetworkTopology().getOutputSize());
				getOptions().world->getNeuralNetwork().getNetworkTopology().getOutput(output);
				totalQ += *max_element(output.begin(), output.end());
				totalQValues++;
				nextIsStartingState = false;
			}

			if (getOptions().world->isTerminalState()) {
				nextIsStartingState = true;
				if (!skipNextTotalReward) {
					totalEpisodes++;
					totalReward += currentTotalReward;
				}
				else
					skipNextTotalReward = false;

				currentTotalReward = 0;
			}

			storeTransition(&networkTopology, reward);

			if (waitUntilLearningStarts > 0)
				waitUntilLearningStarts--;
			else
			{
				doSupervisedLearning();

				double e = getOptions().world->getEpsilon();
				if (e > getOptions().finalExploration)
					getOptions().world->setEpsilon(e - (getOptions().initialExploration - getOptions().finalExploration) / getOptions().finalExplorationFrame);
			}
		}

		if (totalQValues > 0)
			learningState->addData(DATA_SET_Q_VALUE, totalQ / totalQValues);

		learningState->addData(DATA_SET_EPSILON, getOptions().world->getEpsilon());
		learningState->addData(DATA_SET_AVG_Q_VALUE, qAvgSum / getOptions().targetNetworkUpdateFrequency);

		if (totalEpisodes > 0)
			learningState->addData(DATA_SET_REWARD, totalReward / totalEpisodes);
		else
			currentTotalReward = -1;

		learningState->addData(DATA_SET_TRAINING_ERROR, currentTotalError / getOptions().targetNetworkUpdateFrequency);

		steadyNetwork->getNetworkTopology().copyWeightsFrom(getOptions().world->getNeuralNetwork().getNetworkTopology());

		double e = getOptions().world->getEpsilon();
		getOptions().world->setEpsilon(0);
		getOptions().world->rateKI();
		getOptions().world->setEpsilon(e);

		return true;
	}


	const DQNLearningRuleOptions& DQNLearningRule::getOptions() const
	{
		return static_cast<DQNLearningRuleOptions&>(*options.get());
	}

}