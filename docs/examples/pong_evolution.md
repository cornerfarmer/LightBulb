# Pong evolution

*The example is integrated into LightBulbExample and its code can be found in [PongEvolution](https://github.com/domin1101/LightBulb/tree/master/example/LightBulbExample/Examples/PongEvolution).*

A simple example how to use coevolution in LightBulb. Our goal is to learn a network to play pong.

## Introduction

As pong is a game for two players and we do not want to add any human or predefined AI player to this example - the AI should learn totally on its own - it is necessary that AIs play against each other and learn by its own mistakes/good moves. This can be a bit complicated, so we use coevolution which makes it easier to get this working.

Coevolution is very similar to normal evolution, but instead of having just one population we use two. To rate individuals from a population we let them play pong against individuals from the other populations and select the ones which did the best job. One population is called the parasite population. The goal for the individuals of this population is to make the individuals from the other population fail. The goal of the ones from the other population is to win or at least play tie.

## Individuals

At first we need again our individual class:

```cpp
class PongAI : public LightBulb::AbstractDefaultIndividual
{
protected:
	Pong* currentGame;
	void getNNInput(std::vector<double>& input) override;
	void interpretNNOutput(std::vector<double>& output) override;
public:
	PongAI(Pong& pong_);
};
```

The constructor:

```cpp
PongAI::PongAI(Pong& pong_)
	: AbstractDefaultIndividual(pong_)
{
	currentGame = &pong_;
	FeedForwardNetworkTopologyOptions options;
	options.neuronsPerLayerCount.push_back(1);
	options.neuronsPerLayerCount.push_back(2);
	options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new IdentityFunction()));
	buildNeuralNetwork(options);
}
```

We get the network input from the environment:

```cpp
void Position::getNNInput(std::vector<double>& input)
{
	currentGame->getNNInput(input);
}
```

The interpretation of the output is really simple. Either move the paddle up, down or do nothing:

```cpp
void PongAI::interpretNNOutput(std::vector<double>& output)
{
	if (output[0] > 0.5)
		currentGame->getGame().movePaddle(1);
	else if (output[1] > 0.5)
		currentGame->getGame().movePaddle(-1);
}
```

## Environment

In this example we have to use the AbstractCoevolutionEnvironment as we want to use coevolution.

```cpp
class Pong : public LightBulb::AbstractCoevolutionEnvironment
{
private:
	PongGame game;
protected:
	LightBulb::AbstractIndividual* createNewIndividual() override;
	void resetEnvironment() override;
	int simulateGame(PongAI& ai1, PongAI& ai2);
	int doCompare(LightBulb::AbstractIndividual& obj1, LightBulb::AbstractIndividual& obj2, int round) override;
public:
	Pong(bool isParasiteEnvironment, LightBulb::AbstractCombiningStrategy* combiningStrategy_, LightBulb::AbstractCoevolutionFitnessFunction* fitnessFunction_, LightBulb::AbstractHallOfFameAlgorithm* hallOfFameToAddAlgorithm_ = nullptr, LightBulb::AbstractHallOfFameAlgorithm* hallOfFameToChallengeAlgorithm_ = nullptr);
	void getNNInput(std::vector<double>& sight);
	int getRoundCount() const override;
};
```

In the constructor we just forward the given parameters to our base class. We will come to their meaning later.

```cpp
Pong::Pong(bool isParasiteEnvironment_, AbstractCombiningStrategy* combiningStrategy_, AbstractCoevolutionFitnessFunction* fitnessFunction_, AbstractHallOfFameAlgorithm* hallOfFameToAddAlgorithm_, AbstractHallOfFameAlgorithm* hallOfFameToChallengeAlgorithm_)
	: AbstractCoevolutionEnvironment(isParasiteEnvironment_, combiningStrategy_, fitnessFunction_, hallOfFameToAddAlgorithm_, hallOfFameToChallengeAlgorithm_)
{

}
```

As in a normal environment we have to define how new individuals should be created:

```cpp
AbstractIndividual* Pong::createNewIndividual()
{
	return new PongAI(*options, *this);
}
```

When the environment resets we just reset our game. PongGame is by the way just a class which manages the pong game itself. To make the example still clear and simple, i have excluded the game code into an extra class.

```cpp
void Pong::resetEnvironment()
{
	game.reset();
}
```

As said in the individual class, here is the getNNInput() method. The neural network gets ball position, velocity and paddle positions:

```cpp
void Pong::getNNInput(std::vector<double>& input)
{
	input.resize(6);
	input[0] = game.getPlayer() * game.getState().ballPosX / game.getProperties().width;
	input[1] = game.getState().ballPosY / game.getProperties().height;
	input[2] = game.getPlayer() * game.getState().ballVelX / game.getProperties().maxBallSpeed;
	input[3] = game.getState().ballVelY / game.getProperties().maxBallSpeed;
	if (game.getPlayer() == 1)
	{
		input[4] = game.getState().paddle1Pos / (game.getProperties().height - game.getProperties().paddleHeight);
		input[5] = game.getState().paddle2Pos / (game.getProperties().height - game.getProperties().paddleHeight);
	}
	else
	{
		input[5] = game.getState().paddle1Pos / (game.getProperties().height - game.getProperties().paddleHeight);
		input[4] = game.getState().paddle2Pos / (game.getProperties().height - game.getProperties().paddleHeight);
	}
}
```

We also have to define how often each pair of individuals should be compared. In our case this is just 1, but it can also be 2 or more times. (For example, if the starting player has an advantage)

 ```cpp
int Pong::getRoundCount() const
{
	return 1;
}
```


Now let's get to the interesting part: We have to define how individuals should be compared.

```cpp
int Pong::doCompare(AbstractIndividual& individual1, AbstractIndividual& individual2, int round)
{
	return simulateGame(static_cast<PongAI&>(individual1), static_cast<PongAI&>(individual2));
}
```

The method doCompare should just return 1, if individual1 has been better than individual2 or -1, if it's the other way round.
To make this decision we just simulate one game between those AIs.


```cpp
int Pong::simulateGame(PongAI& ai1, PongAI& ai2)
{
	ai2.resetNN();
	ai1.resetNN();

	ai1.setPong(*this);
	ai2.setPong(*this);

	resetEnvironment();

	double time = 0;
	while (game.whoHasWon() == 0 && time < game.getProperties().maxTime)
	{
		game.setPlayer(1);
		ai1.doNNCalculation();
		game.setPlayer(-1);
		ai2.doNNCalculation();
		game.advanceBall(1);

		time++;
	}

	if (game.whoHasWon() == 0) {
		if (parasiteEnvironment)
			return -1;
		else
			return 1;
	}
	else
		return game.whoHasWon();
}
```

The game method "whoHasWon" returns -1, 0, 1 depending on who has won or if it's a tie. But as we are not allowed to return 0 (tie) in doCompare(), we always have to determine a winner. Remember: The parasite individual has to make the other individual fail. If it's a tie, this has not happened. So we declare the other individual as a winner. 

## Learning

First we have to create our two environments:

```cpp
cs1 = new SharedSamplingCombiningStrategy(25);
cs2 = new SharedSamplingCombiningStrategy(25);

hof1 = new RandomHallOfFameAlgorithm(5);
hof2 = new RandomHallOfFameAlgorithm(5);

Pong environment(false, cs1, new SharedCoevolutionFitnessFunction(), hof1, hof2);
Pong parasiteEnvironment(true, cs2, new SharedCoevolutionFitnessFunction(), hof2, hof1);

cs1->setSecondEnvironment(parasiteEnvironment);
cs2->setSecondEnvironment(environment);
```

Both environments have its combining strategies and hall of fame algorithms.

The combining strategy determine which individuals should be compared. As it would be too expensive to compare every individual with every other one, it is very important to get the best comparison pairs.

The hall of fame algorithms might be not necessary for simple problems like this one. Every few iterations they store the best individual and compare future individuals with those hall of fame members. This makes the learning process more stable.


```cpp
EvolutionLearningRuleOptions options;
options.creationCommands.push_back(new ConstantCreationCommand(250));
options.exitConditions.push_back(new PerfectIndividualFoundCondition(20));
options.reuseCommands.push_back(new ConstantReuseCommand(new BestReuseSelector(), 16));
options.selectionCommands.push_back(new BestSelectionCommand(150));
options.mutationsCommands.push_back(new ConstantMutationCommand(new MutationAlgorithm(1.6), new RandomSelector(new RankBasedRandomFunction()), 1.8));
options.recombinationCommands.push_back(new ConstantRecombinationCommand(new RecombinationAlgorithm(), new RandomSelector(new RankBasedRandomFunction()), 0.3));
options.world = &environment;

EvolutionLearningRule learningRule1(options);

options.world = &parasiteEnvironment;
EvolutionLearningRule learningRule2(options);
```

For creating the two evolution learning rules which manages the two environments, we again have to declare a bunch of evolution commands.


Those learning rules are now combined into one big CoevolutionLearningRule:

```cpp
CoevolutionLearningRuleOptions coevolutionLearningRuleOptions;
coevolutionLearningRuleOptions.learningRule1 = &learningRule1;
coevolutionLearningRuleOptions.learningRule2 = &learningRule2;

CoevolutionLearningRule learningRule(coevolutionLearningRuleOptions);
```

## Run it!

Now we are ready to start!
```cpp
std::unique_ptr<EvolutionLearningResult> result(static_cast<EvolutionLearningResult*>(learningRule.start()));
PongAI* bestAI = static_cast<PongAI*>(result.bestIndividuals[0].get());
```

Now its up to you to try and test the pong AI. 

Of course you could also just click the gif below and try it online. :stuck_out_tongue_winking_eye: 

<a href="http://dw-projects.com/index.php?id=58" align="center">
<p align="center">
<img src="media/pong_evolution.gif" width="200">
</p>
</a>

In the [next tutorial]() we also try to learn pong, but this time we use reinforcement learning.
