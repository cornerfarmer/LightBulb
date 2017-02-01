// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementEnvironment.hpp"
#include "LightBulb/ActivationOrder/TopologicalOrder.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"

//Library include

namespace LightBulb
{
	void AbstractReinforcementEnvironment::doNNCalculation()
	{
		neuralNetwork->getNetworkTopology().resetActivation();
		// Get the input
		getNNInput(lastInput);		

		TopologicalOrder topologicalOrder;
		// Calculate the output from the the input
		neuralNetwork->calculate(lastInput, lastOutput, topologicalOrder, false);

		if (!epsilonGreedly) {
			for (int i = 0; i < lastOutput.size(); i++)
			{
				if (useStochasticActionDecision)
					lastBooleanOutput[i] = (randomGenerator->randDouble() < lastOutput[i]);
				else
					lastBooleanOutput[i] = (0.5 < lastOutput[i]);
			}
		}
		else
		{
			lastBooleanOutput = std::vector<bool>(lastBooleanOutput.size(), false);
			if (randomGenerator->randDouble() < epsilon)
			{
				lastBooleanOutput[randomGenerator->randInt(0, lastBooleanOutput.size() - 1)] = true;
			}
			else
			{
				int bestOutput = 0;
				for (int i = 1; i < lastOutput.size(); i++)
				{
					if (lastOutput[bestOutput] <= lastOutput[i])
						bestOutput = i;
				}
				lastBooleanOutput[bestOutput] = true;
			}
		}

		// Interpret the output
		interpretNNOutput(lastBooleanOutput);
	}

	AbstractReinforcementEnvironment::AbstractReinforcementEnvironment(FeedForwardNetworkTopologyOptions& options, bool epsilonGreedly_, double epsilon_)
	{
		buildNeuralNetwork(options);
		epsilonGreedly = epsilonGreedly_;
		epsilon = epsilon_;
		useStochasticActionDecision = true;
	}

	void AbstractReinforcementEnvironment::initializeForLearning()
	{
		// Randomize all weights
		neuralNetwork->getNetworkTopology().randomizeDependingOnLayerSize(*randomGenerator);		
	}

	NeuralNetwork& AbstractReinforcementEnvironment::getNeuralNetwork()
	{
		return *neuralNetwork.get();
	}

	double AbstractReinforcementEnvironment::getEpsilon()
	{
		return epsilon;
	}


	void AbstractReinforcementEnvironment::setEpsilon(double newEpsilon)
	{
		epsilon = newEpsilon;
	}

	void AbstractReinforcementEnvironment::setLearningState(LearningState& learningState_)
	{
		learningState = &learningState_;
	}

	void AbstractReinforcementEnvironment::buildNeuralNetwork(FeedForwardNetworkTopologyOptions& options)
	{
		// Create a new network topology from the adjusted options.
		FeedForwardNetworkTopology* networkTopology = new FeedForwardNetworkTopology(options);

		// Create a neural network from the network topolgy
		neuralNetwork.reset(new NeuralNetwork(networkTopology));

		// Initialize the mutation strength vector
		buildOutputBuffer();
	}


	void AbstractReinforcementEnvironment::buildOutputBuffer()
	{
		lastOutput.resize(neuralNetwork->getNetworkTopology().getOutputSize());
		lastBooleanOutput.resize(lastOutput.size());
	}

	std::vector<std::string> AbstractReinforcementEnvironment::getDataSetLabels() const
	{
		std::vector<std::string> labels;
		return labels;
	}

	std::vector<bool>& AbstractReinforcementEnvironment::getLastBooleanOutput()
	{
		return lastBooleanOutput;
	}

	void AbstractReinforcementEnvironment::setStochasticActionDecision(bool useStochasticActionDecision_)
	{
		useStochasticActionDecision = useStochasticActionDecision_;
	}
}
