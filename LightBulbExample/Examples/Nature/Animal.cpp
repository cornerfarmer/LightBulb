// Includes
#include "Examples/Nature/Animal.hpp"
#include "Examples/Nature/Nature.hpp"
#include "Examples/Nature/AbstractTile.hpp"
#include <NeuronDescription/SameNeuronDescriptionFactory.hpp>
#include <Function/InputFunction/WeightedSumFunction.hpp>
#include <NetworkTopology/FeedForwardNetworkTopology.hpp>
#include <NeuronDescription/NeuronDescription.hpp>
#include <Function/ActivationFunction/BinaryFunction.hpp>

using namespace LightBulb;

Animal::Animal(Nature& nature_, int posX_, int posY_, int dirX_, int dirY_)
	: AbstractSimpleEvolutionObject(nature_)
{
	nature = &nature_;

	reset(posX_, posY_, dirX_, dirY_);

	FeedForwardNetworkTopologyOptions options;
	options.useBiasNeuron = false;
	options.neuronsPerLayerCount.push_back(6);
	options.neuronsPerLayerCount.push_back(10);
	options.neuronsPerLayerCount.push_back(5);
	options.descriptionFactory = new SameNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new BinaryFunction()));
	buildNeuralNetwork(options);
}

void Animal::getNNInput(std::vector<double>& input)
{
	input = nature->getSight(posX, posY, dirX, dirY);
	input.push_back(health / 200.0);
}

void Animal::interpretNNOutput(std::vector<double>& output)
{
	if (output[3] > 0)
	{
		health = std::min(200.0, health + nature->tryToEat(posX + dirX, posY + dirY));
	}

	if (false && health >= 200 && nature->getTile(posX - dirX, posY - dirY).isWalkable())
	{
		Animal* newAnimal = static_cast<Animal*>(clone());
		health /= 2;
		newAnimal->health = health;
		newAnimal->posX = posX - dirX;
		newAnimal->posY = posY - dirY;
		newAnimal->rotate(1);
		//learningRule.doMutation(*newAnimal);
	}

	if (output[0] > 0)
		rotate(1);
	if (output[2] > 0)
		rotate(-1);
	if (output[1] > 0)
	{
		if (nature->getTile(posX + dirX, posY + dirY).isWalkable())
		{
			posX += dirX;
			posY += dirY;
		}
	}

	health -= 1;
	if (health <= 0)
		dead = true;

	stepsSurvived++;
}

bool Animal::isDead() const
{
	return dead;
}

int Animal::getStepsSurvived() const
{
	return stepsSurvived;
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
}

int Animal::getPosX() const
{
	return posX;
}

int Animal::getPosY() const
{
	return posY;
}

void Animal::reset(int posX_, int posY_, int dirX_, int dirY_)
{
	health = 100;
	dead = false;
	stepsSurvived = 0;

	posX = posX_;
	posY = posY_;
	dirX = dirX_;
	dirY = dirY_;
}
