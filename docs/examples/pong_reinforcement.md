# Pong reinforcement

*The example is integrated into LightBulbExample and its code can be found in [PongReinforcement](https://github.com/domin1101/LightBulb/tree/master/example/LightBulbExample/Examples/PongReinforcement).*

A example how to use reinforcement learning in LightBulb. We will try to learn pong to our AI with DQN Learning. 

## Introduction

In contrast to the previous example, we now try to achieve the same result with reinforcement learning. RL is very similar structured like evolution learning. We also have an environment, but only one individual (=actor). Also we do not learn by random guesses, but try to repeat/learn actions which resulted in good rewards. Rewards are the only thing we get as an response from the environment. A good reward means the AI has done something good, a bad reward means the opposite.

## Environment

At first we need again our environment class:

```cpp
class PongReinforcementEnvironment : public LightBulb::AbstractReinforcementEnvironment
{
private:
	int time;
	PongGame game;
protected:
	void getNNInput(std::vector<double>& input) override;
	void interpretNNOutput(std::vector<bool>& output) override;
public:
	PongReinforcementEnvironment(FeedForwardNetworkTopologyOptions& options_, bool epsilonGreedly = false, double epsilon = 0.1);
	double doSimulationStep() override;
	void executeCompareAI();
	void initializeForLearning() override;
	bool isTerminalState() override;
	void setRandomGenerator(AbstractRandomGenerator& randomGenerator_);
};
void PongReinforcementEnvironment::setRandomGenerator(AbstractRandomGenerator& randomGenerator_)
{
	AbstractRandomGeneratorUser::setRandomGenerator(randomGenerator_);
	game.setRandomGenerator(randomGenerator_);
}
```

In the constructor we just forward the given parameters to the parent class.

```cpp
PongReinforcementEnvironment::PongReinforcementEnvironment(FeedForwardNetworkTopologyOptions& options_, bool epsilonGreedly, double epsilon)
	: AbstractReinforcementEnvironment(options_, epsilonGreedly, epsilon)
{
}
```

We have to define how the input of the network should look like and how the output should be interpreted:

```cpp
void PongReinforcementEnvironment::getNNInput(std::vector<double>& input)
{
	input.resize(6);
	input[0] = game.getState().ballPosX / game.getProperties().width;
	input[1] = game.getState().ballPosY / game.getProperties().height;
	input[2] = game.getState().ballVelX / game.getProperties().maxBallSpeed;
	input[3] = game.getState().ballVelY / game.getProperties().maxBallSpeed;
	input[4] = game.getState().paddle1Pos / (game.getProperties().height - game.getProperties().paddleHeight);
	input[5] = game.getState().paddle2Pos / (game.getProperties().height - game.getProperties().paddleHeight);
}

void PongReinforcementEnvironment::interpretNNOutput(std::vector<bool>& output)
{
	if (output[0])
		game.movePaddle(1);
	else if (output[1])
		game.movePaddle(-1);
}
```

Before learning start we reset out time counter.

```cpp
void PongReinforcementEnvironment::initializeForLearning()
{
	AbstractReinforcementEnvironment::initializeForLearning();
	time = -1;
}
```

The simulation step is also very similar to the evolution example.
The difference is that here we return after every tiny step a reward value which rates the taken action. In Pong this is most of the time zero. Only if a point has been made, the reward is 1 or -1 depending on who made the point. 

```cpp
double PongReinforcementEnvironment::doSimulationStep()
{
	if (game.whoHasWon() != 0 || time >= game.getProperties().maxTime || time == -1)
	{
		time = 0;
		game.reset();
	}

	game.setPlayer(1);
	doNNCalculation();
	game.setPlayer(-1);
	executeCompareAI();
	game.advanceBall(1);

	time++;
	if (time >= game.getProperties().maxTime)
		return 0;
	else
		return game.whoHasWon();
}
```

As reinforcement learning is currently only working with one AI, we need another type of opponent. In this example we use a simple scripted AI that always just follows the ball.

```cpp
void PongReinforcementEnvironment::executeCompareAI()
{
	if (game.getState().ballPosY > game.getState().paddle2Pos + game.getProperties().paddleHeight / 2)
		game.movePaddle(1);
	else
		game.movePaddle(-1);
}
```

The method isTerminalState should return if the current state marks the end of an episode. In pong this is always after somebody made a point or the time has run out.

```cpp
bool PongReinforcementEnvironment::isTerminalState()
{
	return game.whoHasWon() != 0 || time >= game.getProperties().maxTime;
}
```

## Learning


First we create the environment:

```cpp
FeedForwardNetworkTopologyOptions feedForwardNetworkTopologyOptions;
feedForwardNetworkTopologyOptions.enableShortcuts = false;
feedForwardNetworkTopologyOptions.useBiasNeuron = true;

feedForwardNetworkTopologyOptions.neuronsPerLayerCount.push_back(6);
feedForwardNetworkTopologyOptions.neuronsPerLayerCount.push_back(256);
feedForwardNetworkTopologyOptions.neuronsPerLayerCount.push_back(3);

feedForwardNetworkTopologyOptions.descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new RectifierFunction()), new NeuronDescription(new WeightedSumFunction(), new IdentityFunction()));

PongReinforcementEnvironment environment(feedForwardNetworkTopologyOptions, true, 1);
```

The environment also gets the description of the neural network.

The learning rule is relatively simple:

```cpp
DQNLearningRuleOptions options;
options.rmsPropOptions.learningRate = 0.0005;
options.finalExplorationFrame = 500000;
options.rmsPropOptions.deltaWeightsMomentum = 0;
options.environment = &environment;
options.logger = new ConsoleLogger(LL_LOW);
options.maxIterationsPerTry = 85;

DQNLearningRule learningRule(options);
```

Thats it. Now we can execute the learning rule.


## Run it!

```cpp
learningRule.start();
AbstractNeuralNetwork* network = environment.getNeuralNetwork();
```

Now its up to you to try and test the pong AI. 

Of course you could also just click the gif below and try it online. :stuck_out_tongue_winking_eye: 

<a href="http://dw-projects.com/index.php?id=58" align="center">
<p align="center">
<img src="media/pong_dqn.gif" width="200">
</p>
</a>

The whole code:

```cpp
#include <LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp>
#include <LightBulb/NeuronDescription/DifferentNeuronDescriptionFactory.hpp>
#include <LightBulb/NeuronDescription/NeuronDescription.hpp>
#include <LightBulb/NeuralNetwork/NeuralNetwork.hpp>
#include <LightBulb/Learning/Supervised/GradientDescentLearningRule.hpp>
#include <LightBulb/Function/ActivationFunction/RectifierFunction.hpp>
#include <LightBulb/Function/InputFunction/WeightedSumFunction.hpp>
#include <LightBulb/Logging/ConsoleLogger.hpp>
#include <LightBulb/Learning/Reinforcement/AbstractReinforcementEnvironment.hpp>
#include <LightBulb/Learning/Reinforcement/DQNLearningRule.hpp>

#include "PongGame.hpp"
#include <LightBulb/Logging/AbstractLogger.hpp>

using namespace LightBulb;


class PongReinforcementEnvironment : public LightBulb::AbstractReinforcementEnvironment
{
private:
	int time;
	PongGame game;
protected:
	void getNNInput(std::vector<double>& input) override;
	void interpretNNOutput(std::vector<bool>& output) override;
public:
	PongReinforcementEnvironment(FeedForwardNetworkTopologyOptions& options_, bool epsilonGreedly = false, double epsilon = 0.1);
	double doSimulationStep() override;
	void executeCompareAI();
	void initializeForLearning() override;
	bool isTerminalState() override;
	void setRandomGenerator(AbstractRandomGenerator& randomGenerator_);
};

PongReinforcementEnvironment::PongReinforcementEnvironment(FeedForwardNetworkTopologyOptions& options_, bool epsilonGreedly, double epsilon)
	: AbstractReinforcementEnvironment(options_, epsilonGreedly, epsilon)
{
}

void PongReinforcementEnvironment::getNNInput(std::vector<double>& input)
{
	input.resize(6);
	input[0] = game.getState().ballPosX / game.getProperties().width;
	input[1] = game.getState().ballPosY / game.getProperties().height;
	input[2] = game.getState().ballVelX / game.getProperties().maxBallSpeed;
	input[3] = game.getState().ballVelY / game.getProperties().maxBallSpeed;
	input[4] = game.getState().paddle1Pos / (game.getProperties().height - game.getProperties().paddleHeight);
	input[5] = game.getState().paddle2Pos / (game.getProperties().height - game.getProperties().paddleHeight);
}

void PongReinforcementEnvironment::interpretNNOutput(std::vector<bool>& output)
{
	if (output[0])
		game.movePaddle(1);
	else if (output[1])
		game.movePaddle(-1);
}

void PongReinforcementEnvironment::initializeForLearning()
{
	AbstractReinforcementEnvironment::initializeForLearning();
	time = -1;
}

double PongReinforcementEnvironment::doSimulationStep()
{
	if (game.whoHasWon() != 0 || time >= game.getProperties().maxTime || time == -1)
	{
		time = 0;
		game.reset();
	}

	game.setPlayer(1);
	doNNCalculation();
	game.setPlayer(-1);
	executeCompareAI();
	game.advanceBall(1);

	time++;
	if (time >= game.getProperties().maxTime)
		return 0;
	else
		return game.whoHasWon();
}

void PongReinforcementEnvironment::executeCompareAI()
{
	if (game.getState().ballPosY > game.getState().paddle2Pos + game.getProperties().paddleHeight / 2)
		game.movePaddle(1);
	else
		game.movePaddle(-1);
}

bool PongReinforcementEnvironment::isTerminalState()
{
	return game.whoHasWon() != 0 || time >= game.getProperties().maxTime;
}

void PongReinforcementEnvironment::setRandomGenerator(AbstractRandomGenerator& randomGenerator_)
{
	AbstractRandomGeneratorUser::setRandomGenerator(randomGenerator_);
	game.setRandomGenerator(randomGenerator_);
}

int main()
{
	FeedForwardNetworkTopologyOptions feedForwardNetworkTopologyOptions;
	feedForwardNetworkTopologyOptions.enableShortcuts = false;
	feedForwardNetworkTopologyOptions.useBiasNeuron = true;

	feedForwardNetworkTopologyOptions.neuronsPerLayerCount.push_back(6);
	feedForwardNetworkTopologyOptions.neuronsPerLayerCount.push_back(256);
	feedForwardNetworkTopologyOptions.neuronsPerLayerCount.push_back(3);

	feedForwardNetworkTopologyOptions.descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new RectifierFunction()), new NeuronDescription(new WeightedSumFunction(), new IdentityFunction()));

	PongReinforcementEnvironment environment(feedForwardNetworkTopologyOptions, true, 1);

	DQNLearningRuleOptions options;
	options.rmsPropOptions.learningRate = 0.0005;
	options.finalExplorationFrame = 500000;
	options.rmsPropOptions.deltaWeightsMomentum = 0;
	options.environment = &environment;
	options.logger = new ConsoleLogger(LL_LOW);
	options.maxIterationsPerTry = 85;

	DQNLearningRule learningRule(options);

	learningRule.start();

	getchar();

	return 0;
}
```