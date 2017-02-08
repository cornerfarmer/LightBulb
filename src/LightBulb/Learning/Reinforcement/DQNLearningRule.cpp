// Includes
#include "LightBulb/Learning/Reinforcement/DQNLearningRule.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/NetworkTopology/AbstractNetworkTopology.hpp"
#include "LightBulb/Learning/Evolution/EvolutionLearningResult.hpp"
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementEnvironment.hpp"
#include "LightBulb/Teaching/TeachingLessonLinearInput.hpp"
#include "LightBulb/ActivationOrder/TopologicalOrder.hpp"
#include "LightBulb/Learning/Supervised/SupervisedLearningResult.hpp"
#include "LightBulb/Random/AbstractRandomGenerator.hpp"
#include "LightBulb/Teaching/Teacher.hpp"
#include "LightBulb/Logging/AbstractLogger.hpp"
#include "LightBulb/Learning/LearningState.hpp"
// Library includes

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

	DQNLearningRule::~DQNLearningRule() = default;
	
	void DQNLearningRule::initialize(DQNLearningRuleOptions* options)
	{
		teacher.reset(new Teacher());
		options->gradientDescentOptions.gradientDescentAlgorithm = new RMSPropLearningRate(options->rmsPropOptions);
		options->gradientDescentOptions.teacher = teacher.get();
		options->gradientDescentOptions.neuralNetwork = &getOptions().environment->getNeuralNetwork();
		options->gradientDescentOptions.logger = nullptr;
		gradientDescent.reset(new GradientDescentLearningRule(options->gradientDescentOptions));

		steadyNetwork.reset(getOptions().environment->getNeuralNetwork().clone());
	}

	void DQNLearningRule::initializeTry()
	{
		getOptions().environment->setLearningState(*learningState.get());
		getOptions().environment->initializeForLearning();
		steadyNetwork->getNetworkTopology().copyWeightsFrom(getOptions().environment->getNeuralNetwork().getNetworkTopology());
		nextTransitionIndex = 0;
		waitUntilLearningStarts = getOptions().replayStartSize;
		getOptions().environment->setEpsilon(getOptions().initialExploration);
		currentTotalReward = 0;
	}
	
	void DQNLearningRule::storeTransition(const AbstractNetworkTopology* networkTopology, const Scalar<>& reward)
	{
		Transition transition;
		transition.state = getOptions().environment->getLastInput();

		if (!getOptions().environment->isTerminalState()) {
			if (getOptions().calculatorType == CT_GPU)
				transition.nextState.getViennaclValueForEditing().resize(getOptions().environment->getNeuralNetwork().getNetworkTopology().getInputSize() + getOptions().environment->getNeuralNetwork().getNetworkTopology().usesBiasNeuron());
			else
				transition.nextState.getEigenValueForEditing().resize(getOptions().environment->getNeuralNetwork().getNetworkTopology().getInputSize() + getOptions().environment->getNeuralNetwork().getNetworkTopology().usesBiasNeuron());
			getOptions().environment->getNNInput(transition.nextState);

			transition.nextState.getEigenValueForEditing()(transition.nextState.getEigenValue().size() - 1) = 1;
		}

		transition.reward = reward;

		if (getOptions().calculatorType == CT_GPU)
		{
			
		}
		else
		{
			for (int i = 0; i < getOptions().environment->getLastBooleanOutput().getEigenValue().size(); i++)
			{
				if (getOptions().environment->getLastBooleanOutput().getEigenValue()[i])
				{
					transition.action = i;
					break;
				}
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
		teacher->clearLessons();

		for (int i = 0; i < std::min(static_cast<int>(transitions.size()), getOptions().minibatchSize); i++)
		{
			int r = randomGenerator->randInt(0, transitions.size() - 1);

			if (getOptions().calculatorType == CT_GPU)
			{
			}
			else
			{
				double y = transitions[r].reward.getEigenValue();

				if (transitions[r].nextState.getEigenValue().size() > 0)
				{
					const Vector<>& output = steadyNetwork->calculateWithoutOutputCopy(transitions[r].nextState, TopologicalOrder());

					double q = output.getEigenValue().maxCoeff();
					qAvgSum += q;
					y += getOptions().discountFactor * q;
				}

				TeachingInput<double>* input = new TeachingInput<double>(steadyNetwork->getNetworkTopology().getOutputSize());

				input->set(transitions[r].action.getEigenValue(), y);
				std::vector<double> state(transitions[r].state.getEigenValue().size() - steadyNetwork->getNetworkTopology().usesBiasNeuron());
				for (int l = 0; l < state.size(); l++)
					state[l] = transitions[r].state.getEigenValue()(l);

				teacher->addTeachingLesson(new TeachingLessonLinearInput(state, input));
			}

		}

		//auto gradient = checkGradient(&teacher, getOptions()->environment->getNeuralNetwork()->getNetworkTopology());

		std::unique_ptr<SupervisedLearningResult> result(static_cast<SupervisedLearningResult*>(gradientDescent->start()));
		currentTotalError += result->totalError;
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


	void DQNLearningRule::doIteration()
	{
		log("Iteration " + std::to_string(learningState->iterations), LL_LOW);

		currentTotalError = 0;
		double totalReward = 0;
		int totalEpisodes = 0;
		bool nextIsStartingState = true;
		double totalQ = 0;
		int totalQValues = 0;
		bool skipNextTotalReward = currentTotalReward == -1;
		qAvgSum = 0;

		AbstractNetworkTopology& networkTopology = getOptions().environment->getNeuralNetwork().getNetworkTopology();

		for (int i = 0; i < getOptions().targetNetworkUpdateFrequency; i++) {
			getOptions().environment->doSimulationStep(reward);
			currentTotalReward += reward.getEigenValue();

			if (nextIsStartingState)
			{
				std::vector<double> output(getOptions().environment->getNeuralNetwork().getNetworkTopology().getOutputSize());
				getOptions().environment->getNeuralNetwork().getNetworkTopology().getOutput(output);
				totalQ += *max_element(output.begin(), output.end());
				totalQValues++;
				nextIsStartingState = false;
			}

			if (getOptions().environment->isTerminalState()) {
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

				double e = getOptions().environment->getEpsilon();
				if (e > getOptions().finalExploration)
					getOptions().environment->setEpsilon(e - (getOptions().initialExploration - getOptions().finalExploration) / getOptions().finalExplorationFrame);
			}
		}

		if (totalQValues > 0)
			learningState->addData(DATA_SET_Q_VALUE, totalQ / totalQValues);

		learningState->addData(DATA_SET_EPSILON, getOptions().environment->getEpsilon());
		learningState->addData(DATA_SET_AVG_Q_VALUE, qAvgSum / getOptions().targetNetworkUpdateFrequency);

		if (totalEpisodes > 0) {
			learningState->addData(DATA_SET_REWARD, totalReward / totalEpisodes); 
			log("Reward: " + std::to_string(totalReward / totalEpisodes), LL_LOW);
		}
		else
			currentTotalReward = -1;

		learningState->addData(DATA_SET_TRAINING_ERROR, currentTotalError / getOptions().targetNetworkUpdateFrequency);

		steadyNetwork->getNetworkTopology().copyWeightsFrom(getOptions().environment->getNeuralNetwork().getNetworkTopology());

		double e = getOptions().environment->getEpsilon();
		getOptions().environment->setEpsilon(0);
		getOptions().environment->rate();
		getOptions().environment->setEpsilon(e);

	}


	const DQNLearningRuleOptions& DQNLearningRule::getOptions() const
	{
		return static_cast<DQNLearningRuleOptions&>(*options.get());
	}

}
