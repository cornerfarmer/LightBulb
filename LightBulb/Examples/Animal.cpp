// Includes
#include "Examples/Animal.hpp"
#include "Examples/Nature.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "Learning/Evolution/EvolutionLearningRule.hpp"
#include "Examples/AbstractTile.hpp"

Animal::Animal(Nature* nature_, int posX_, int posY_, int dirX_, int dirY_)
	: AbstractSimpleEvolutionObject(nature_, 6, 5)
{
	nature = nature_;

	reset(posX_, posY_, dirX_, dirY_);
}

NeuralNetworkIO<double> Animal::getNNInput()
{
	std::vector<double> sight = nature->getSight(posX, posY, dirX, dirY);
	NeuralNetworkIO<double> input(6);
	for (int i = 0; i < sight.size(); i++)
	{
		input.set(0, i, sight[i]);
	}
	input.set(0, sight.size(), health / 200.0);
	return input;
}

void Animal::interpretNNOutput(NeuralNetworkIO<double>* output)
{
	if (output->get(0, 3) > 0)
	{
		health = std::min(200.0, health + nature->tryToEat(posX + dirX, posY + dirY));
	}

	if (false && health >= 200 && nature->getTile(posX - dirX, posY - dirY)->isWalkable())
	{
		Animal* newAnimal = static_cast<Animal*>(clone());
		health /= 2;
		newAnimal->health = health;
		newAnimal->posX = posX - dirX;
		newAnimal->posY = posY - dirY;
		newAnimal->rotate(1);
		//learningRule.doMutation(*newAnimal);
	}

	if (output->get(0, 0) > 0)
		rotate(1);
	if (output->get(0, 2) > 0)
		rotate(-1);
	if (output->get(0, 1) > 0)
	{
		if (nature->getTile(posX + dirX, posY + dirY)->isWalkable())
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

bool Animal::isDead()
{
	return dead;
}

int Animal::getStepsSurvived()
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

int Animal::getPosX()
{
	return posX;
}

int Animal::getPosY()
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
