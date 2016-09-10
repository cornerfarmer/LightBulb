// Includes
#include "Learning/Reinforcement/AbstractReinforcementWorld.hpp"
#include <ActivationOrder/TopologicalOrder.hpp>
#include <NetworkTopology/FeedForwardNetworkTopology.hpp>

//Library include

namespace LightBulb
{
	void AbstractReinforcementWorld::doNNCalculation(bool resetInput)
	{
		if (resetInput) {
			neuralNetwork->getNetworkTopology()->resetActivation();
			// Get the input
			getNNInput(lastInput);
		}

		TopologicalOrder topologicalOrder;
		// Calculate the output from the the input
		neuralNetwork->calculate(lastInput, lastOutput, topologicalOrder, false);

		if (!epsilonGreedly) {
			for (int i = 0; i < lastOutput.size(); i++)
			{
				lastBooleanOutput[i] = (0.5 <= lastOutput[i]);
			}
		}
		else
		{
			lastBooleanOutput = std::vector<bool>(lastBooleanOutput.size(), 0);
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

	AbstractReinforcementWorld::AbstractReinforcementWorld(FeedForwardNetworkTopologyOptions& options, bool epsilonGreedly_, double epsilon_)
	{
		buildNeuralNetwork(options);
		epsilonGreedly = epsilonGreedly_;
		epsilon = epsilon_;
	}

	void AbstractReinforcementWorld::initializeForLearning()
	{
		// Randomize all weights
		neuralNetwork->getNetworkTopology()->randomizeDependingOnLayerSize(randomGenerator);
	}

	NeuralNetwork* AbstractReinforcementWorld::getNeuralNetwork()
	{
		return neuralNetwork.get();
	}

	double AbstractReinforcementWorld::getEpsilon()
	{
		return epsilon;
	}


	void AbstractReinforcementWorld::setEpsilon(double newEpsilon)
	{
		epsilon = newEpsilon;
	}

	void AbstractReinforcementWorld::setLearningState(LearningState* learningState_)
	{
		learningState = learningState_;
	}

	void AbstractReinforcementWorld::buildNeuralNetwork(FeedForwardNetworkTopologyOptions& options)
	{
		// Create a new network topology from the adjusted options.
		FeedForwardNetworkTopology* networkTopology = new FeedForwardNetworkTopology(options);

		// Create a neural network from the network topolgy
		neuralNetwork.reset(new NeuralNetwork(networkTopology));

		// Initialize the mutation strength vector
		buildOutputBuffer();
	}


	void AbstractReinforcementWorld::buildOutputBuffer()
	{
		lastOutput.resize(neuralNetwork->getNetworkTopology()->getOutputSize());
		lastBooleanOutput.resize(lastOutput.size());
	}

	std::vector<std::string> AbstractReinforcementWorld::getDataSetLabels()
	{
		std::vector<std::string> labels;
		return labels;
	}

	std::vector<bool> AbstractReinforcementWorld::getLastBooleanOutput()
	{
		return lastBooleanOutput;
	}
}