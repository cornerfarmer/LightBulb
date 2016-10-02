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
	}

	void DQNLearningRule::initializeTry()
	{
		getOptions()->world->setLearningState(learningState.get());
		getOptions()->world->initializeForLearning();
		if (getOptions()->alternativeTargetNetwork)
			getOptions()->alternativeTargetNetwork->getNetworkTopology()->randomizeDependingOnLayerSize(randomGenerator.get());
		steadyNetwork->getNetworkTopology()->copyWeightsFrom(*getTargetNetworkTopology());
		nextTransitionIndex = 0;
		waitUntilLearningStarts = getOptions()->replayStartSize;
		getOptions()->world->setEpsilon(getOptions()->initialExploration);
		currentTotalReward = 0;
		currentTotalError = 0;
		qAvgSum = 0;
		currentSimulationStep = 0;
		currentTotalEpisodes = 0;
		currentTotalEpisodesReward = 0;
	}

	Teacher* DQNLearningRule::getTeacher()
	{
		return &teacher;
	}

	void DQNLearningRule::initialize()
	{
		getOptions()->world->setPolicyBasedLearning(false);
		getOptions()->gradientDescentOptions.gradientDescentAlgorithm = new RMSPropLearningRate(getOptions()->rmsPropOptions);
		getOptions()->gradientDescentOptions.teacher = &teacher;
		getOptions()->gradientDescentOptions.neuralNetwork = getOptions()->alternativeTargetNetwork ? getOptions()->alternativeTargetNetwork : getOptions()->world->getNeuralNetwork();
		getOptions()->gradientDescentOptions.logger = NULL;
		gradientDescent.reset(new GradientDescentLearningRule(getOptions()->gradientDescentOptions));

		if (getOptions()->alternativeTargetNetwork)
			steadyNetwork.reset(getOptions()->alternativeTargetNetwork->clone());
		else
			steadyNetwork.reset(getOptions()->world->getNeuralNetwork()->clone());
	}

	void DQNLearningRule::storeTransition(double reward, AbstractNetworkTopology* networkTopology)
	{
		Transition transition;
		auto patternVector = networkTopology->getActivationsPerLayer(0);
		transition.state = std::vector<double>(patternVector.data() + networkTopology->usesBiasNeuron(), patternVector.data() + patternVector.size());

		if (!getOptions()->world->isTerminalState()) {
			getOptions()->world->getNNInput(transition.nextState);
		}

		transition.reward = reward;

		transition.action = getOptions()->world->getLastActionIndex();

		if (transitions.size() < getOptions()->replayMemorySize)
		{
			transitions.push_back(transition);
		}
		else if (getOptions()->replaceStoredTransitions)
		{
			transitions[nextTransitionIndex++] = transition;
			nextTransitionIndex %= transitions.size();
		}

	}

	void DQNLearningRule::doSupervisedLearning()
	{
		teacher.getTeachingLessons()->clear();

		for (int i = 0; i < std::min((int)transitions.size(), getOptions()->minibatchSize); i++)
		{
			int r = randomGenerator->randInt(1, transitions.size() - 2);

			double y = transitions[r].reward;

			if (!transitions[r].nextState.empty())
			{
				std::vector<double> output(steadyNetwork->getNetworkTopology()->getOutputSize());
				steadyNetwork->calculate(transitions[r].nextState, output, TopologicalOrder());
				double q = *std::max_element(output.begin(), output.end());
				qAvgSum += q;
				y += getOptions()->discountFactor * q;
			}

			NeuralNetworkIO<double>* input = new NeuralNetworkIO<double>(steadyNetwork->getNetworkTopology()->getOutputSize());

			input->set(0, transitions[r].action, y);

			teacher.addTeachingLesson(new TeachingLessonLinearInput(std::vector<std::vector<double>>(1, transitions[r].state), input));
		}

		//auto gradient = checkGradient(&teacher, getOptions()->world->getNeuralNetwork()->getNetworkTopology());

		std::unique_ptr<AbstractLearningResult> result(gradientDescent->start());
		currentTotalError += result->quality;
	}

	std::string DQNLearningRule::getName()
	{
		return "DQNLearningRule";
	}

	std::vector<std::string> DQNLearningRule::getDataSetLabels()
	{
		std::vector<std::string> labels = AbstractReinforcementLearningRule::getDataSetLabels();
		labels.push_back(DATA_SET_TRAINING_ERROR);
		labels.push_back(DATA_SET_EPSILON);
		labels.push_back(DATA_SET_Q_VALUE);
		labels.push_back(DATA_SET_AVG_Q_VALUE);
		return labels;
	}


	std::vector<Eigen::MatrixXd> DQNLearningRule::checkGradient(Teacher* teacher, AbstractNetworkTopology* networkTopology)
	{
		double error = teacher->getTotalError(*getOptions()->world->getNeuralNetwork(), TopologicalOrder());
		double epsilon = 0.0001;
		auto weights = networkTopology->getAllWeights();
		std::vector<Eigen::MatrixXd> gradientApprox(weights->size());
		for (int l = weights->size() - 1; l >= 0; l--)
		{
			gradientApprox[l].resizeLike(weights->at(l));
			for (int n1 = 0; n1 < weights->at(l).rows(); n1++)
			{
				for (int n2 = 0; n2 < weights->at(l).cols(); n2++)
				{
					weights->at(l)(n1, n2) += epsilon;
					double firstError = teacher->getTotalError(*getOptions()->world->getNeuralNetwork(), TopologicalOrder());

					weights->at(l)(n1, n2) -= epsilon * 2;
					double secondError = teacher->getTotalError(*getOptions()->world->getNeuralNetwork(), TopologicalOrder());
					gradientApprox[l](n1, n2) = (firstError - secondError) / (2 * epsilon);

					weights->at(l)(n1, n2) += epsilon;
				}
			}
		}
		return gradientApprox;
	}

	AbstractNetworkTopology* DQNLearningRule::getTargetNetworkTopology()
	{
		if (getOptions()->alternativeTargetNetwork)
			return getOptions()->alternativeTargetNetwork->getNetworkTopology();
		else
			return getOptions()->world->getNeuralNetwork()->getNetworkTopology();
	}

	bool DQNLearningRule::registerSimulationStep(double reward)
	{
		currentTotalReward += reward;

		if (getOptions()->world->isTerminalState()) {
			currentTotalEpisodes++;
			currentTotalEpisodesReward += currentTotalReward;

			currentTotalReward = 0;
		}

		storeTransition(reward, getOptions()->world->getNeuralNetwork()->getNetworkTopology());

		if (waitUntilLearningStarts > 0)
			waitUntilLearningStarts--;
		else
		{
			doSupervisedLearning();

			double e = getOptions()->world->getEpsilon();
			if (e > getOptions()->finalExploration)
				getOptions()->world->setEpsilon(e - (getOptions()->initialExploration - getOptions()->finalExploration) / getOptions()->finalExplorationFrame);
		}

		currentSimulationStep++;
		if (currentSimulationStep >= getOptions()->targetNetworkUpdateFrequency)
		{
			steadyNetwork->getNetworkTopology()->copyWeightsFrom(*getTargetNetworkTopology());

			if (learningState) {
				learningState->addData(DATA_SET_EPSILON, getOptions()->world->getEpsilon());
				learningState->addData(DATA_SET_AVG_Q_VALUE, qAvgSum / (getOptions()->targetNetworkUpdateFrequency * getOptions()->minibatchSize));

				if (currentTotalEpisodes > 0)
					learningState->addData(DATA_SET_REWARD, currentTotalEpisodesReward / currentTotalEpisodes);

				learningState->addData(DATA_SET_TRAINING_ERROR, currentTotalError / getOptions()->targetNetworkUpdateFrequency);
			}

			currentTotalError = 0;
			qAvgSum = 0;
			currentSimulationStep = 0;
			currentTotalEpisodes = 0;
			currentTotalEpisodesReward = 0;

			return true;
		}
		else
			return false;
	}

	bool DQNLearningRule::doIteration()
	{
		bool iterationHasEnded = false;
		do {
			double reward = getOptions()->world->doSimulationStep();
			iterationHasEnded = registerSimulationStep(reward);
		} while (!iterationHasEnded);


		

		double e = getOptions()->world->getEpsilon();
		getOptions()->world->setEpsilon(0);
		getOptions()->world->rateKI();
		getOptions()->world->setEpsilon(e);

		return true;
	}

	
	DQNLearningRuleOptions* DQNLearningRule::getOptions()
	{
		return static_cast<DQNLearningRuleOptions*>(options.get());
	}


	double DQNLearningRule::calculateActionValue(std::vector<double>& state, int action)
	{
		std::vector<double> output(getTargetNetworkTopology()->getOutputSize());
		getOptions()->alternativeTargetNetwork->calculate(state, output, TopologicalOrder());
		return output[action];
	}
}
