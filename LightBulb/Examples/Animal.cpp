// Includes
#include "Examples\Animal.hpp"
#include "NetworkTopology\RecurrentLayeredNetwork.hpp"
#include "NeuralNetwork\NeuralNetwork.hpp"
#include "Examples\Nature.hpp"
#include "ActivationOrder\TopologicalOrder.hpp"

Animal::Animal(Nature* nature_, RecurrentLayeredNetworkOptions& options, int posX_, int posY_, int dirX_, int dirY_)
{
	nature = nature_;
	brain = new NeuralNetwork(new RecurrentLayeredNetwork(options));
	brain->getNetworkTopology()->randomizeWeights(-0.5, 0.5);
	posX = posX_;
	posY = posY_;
	dirX = dirX_;
	dirY = dirY_;
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
		nature->tryToEat(posX + dirX, posY + dirY);
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