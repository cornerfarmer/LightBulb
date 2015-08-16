// Includes
#include "Examples\Animal.hpp"
#include "NetworkTopology\RecurrentLayeredNetwork.hpp"
#include "NeuralNetwork\NeuralNetwork.hpp"
#include "Examples\Nature.hpp"
#include "ActivationOrder\TopologicalOrder.hpp"
#include "NeuronFactory\SameFunctionsNeuronFactory.hpp"
#include "Neuron\StandardThreshold.hpp"
#include "Function\WeightedSumFunction.hpp"
#include "Function\FermiFunction.hpp"
#include "Function\IdentityFunction.hpp"
#include "Learning\EvolutionLearningRule.hpp"

Animal::Animal(Nature* nature_, int posX_, int posY_, int dirX_, int dirY_)
{
	RecurrentLayeredNetworkOptions options;

	options.selfConnectHiddenLayers = true;
	options.neuronsPerLayerCount.push_back(3);
	options.neuronsPerLayerCount.push_back(10);
	options.neuronsPerLayerCount.push_back(5);
	options.neuronFactory = new SameFunctionsNeuronFactory(new StandardThreshold(0), new WeightedSumFunction(), new FermiFunction(1), new IdentityFunction());

	brain = new NeuralNetwork(new RecurrentLayeredNetwork(options));
	brain->getNetworkTopology()->randomizeWeights(-0.5, 0.5);

	nature = nature_;
	posX = posX_;
	posY = posY_;
	dirX = dirX_;
	dirY = dirY_;
	health = 50;
	dead = false;
}

NeuralNetwork* Animal::getNeuralNetwork()
{
	return brain;
}

void Animal::doNNCalculation(EvolutionLearningRule& learningRule)
{
	std::vector<bool> sight = nature->getSight(posX, posY, dirX, dirY);
	NeuralNetworkIO<double> input(3);
	for (int i = 0; i < sight.size(); i++)
	{
		input.set(0, i, sight[i]);
	}
	std::unique_ptr<NeuralNetworkIO<double>> output = brain->calculate(input, TopologicalOrder());
	if (output->get(0, 0) > 0.5)
		rotate(1);
	if (output->get(0, 2) > 0.5)
		rotate(-1);
	if (output->get(0, 1) > 0.5)
	{
		if (nature->isTileFree(posX + dirX, posY + dirY))
		{
			posX += dirX;
			posY += dirY;
		}
	}
	
	if (output->get(0, 3) > 0.5)
	{
		if (nature->tryToEat(posX + dirX, posY + dirY))
			health = std::min(100, health + 10);
	}

	
	if (health >= 80 && nature->isTileFree(posX - dirX, posY - dirY))
	{
		Animal* newAnimal = static_cast<Animal*>(nature->addNewObject());
		health /= 2;
		newAnimal->health = health;
		newAnimal->posX = posX - dirX;
		newAnimal->posY = posY - dirY;
		newAnimal->rotate(1);
		newAnimal->brain->getNetworkTopology()->copyWeightsFrom(*brain->getNetworkTopology());
		learningRule.doMutation(*newAnimal);
	}
	

	health -= 5;
	if (health <= 0)
		dead = true;
}

bool Animal::isDead()
{
	return dead;
}

void Animal::rotate(int dir)
{
	if (dir == 1)
	{
		if (dirX == 1 && dirY == 0)
		{
			dirX = 0;
			dirY = 1;
		}
		else if (dirX == -1 && dirY == 0)
		{
			dirX = 0;
			dirY = -1;
		}
		else if (dirX == 0 && dirY == 1)
		{
			dirX = -1;
			dirY = 0;
		}
		else if (dirX == 0 && dirY == -1)
		{
			dirX = 1;
			dirY = 0;
		}
	} 
	else
	{
		if (dirX == 1 && dirY == 0)
		{
			dirX = 0;
			dirY = -1;
		}
		else if (dirX == -1 && dirY == 0)
		{
			dirX = 0;
			dirY = 1;
		}
		else if (dirX == 0 && dirY == 1)
		{
			dirX = 1;
			dirY = 0;
		}
		else if (dirX == 0 && dirY == -1)
		{
			dirX = -1;
			dirY = 0;
		}
	}
}

Animal::~Animal()
{
	delete(brain);
}

int Animal::getPosX()
{
	return posX;
}

int Animal::getPosY()
{
	return posY;
}