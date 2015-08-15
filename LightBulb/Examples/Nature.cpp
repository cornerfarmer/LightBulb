// Includes
#include "Examples\Nature.hpp"
#include "Examples\Animal.hpp"
#include "NetworkTopology\RecurrentLayeredNetwork.hpp"
#include "NeuronFactory\SameFunctionsNeuronFactory.hpp"
#include "Neuron\StandardThreshold.hpp"
#include "Function\WeightedSumFunction.hpp"
#include "Function\FermiFunction.hpp"
#include "Function\IdentityFunction.hpp"

EvolutionObjectInterface* Nature::addNewObject()
{
	RecurrentLayeredNetworkOptions options;

	options.neuronsPerLayerCount.push_back(3);
	options.neuronsPerLayerCount.push_back(10);
	options.neuronsPerLayerCount.push_back(4);
	options.neuronFactory = new SameFunctionsNeuronFactory(new StandardThreshold(0), new WeightedSumFunction(), new FermiFunction(1), new IdentityFunction());

	animals.push_back(new Animal(this, options, (int)((float)rand() / RAND_MAX * width), (int)((float)rand() / RAND_MAX * height), 0, 1));
	
	return animals.back();
}

Nature::Nature()
{
	width = 40;
	height = 40;

	plants.resize(width);
	for (int x = 0; x < width; x++)
	{
		plants[x].resize(height);
		for (int y = 0; y < height; y++)
		{
			plants[x][y] = true;
		}
	}
}


void Nature::doSimulationStep(EvolutionLearningRule& learningRule)
{
	for (auto animal = animals.begin(); animal != animals.end(); animal++)
	{
		(*animal)->doNNCalculation(learningRule);
	}
}

std::vector<bool> Nature::getSight(int posX, int posY, int dirX, int dirY)
{
	std::vector<bool> sight;
	if (dirX == 1 && dirY == 0)
	{
		sight.push_back(getViewValueOfPos(posX + dirX, posY - 1));
		sight.push_back(getViewValueOfPos(posX + dirX, posY));
		sight.push_back(getViewValueOfPos(posX + dirX, posY + 1));
	}
	else if (dirX == -1 && dirY == 0)
	{
		sight.push_back(getViewValueOfPos(posX + dirX, posY + 1));
		sight.push_back(getViewValueOfPos(posX + dirX, posY));
		sight.push_back(getViewValueOfPos(posX + dirX, posY - 1));
	}
	else if (dirX == 0 && dirY == 1)
	{
		sight.push_back(getViewValueOfPos(posX + 1, posY + dirY));
		sight.push_back(getViewValueOfPos(posX, posY + dirY));
		sight.push_back(getViewValueOfPos(posX - 1, posY + dirY));
	}
	else if (dirX == 0 && dirY == -1)
	{
		sight.push_back(getViewValueOfPos(posX - 1, posY + dirY));
		sight.push_back(getViewValueOfPos(posX, posY + dirY));
		sight.push_back(getViewValueOfPos(posX + 1,posY + dirY));
	}
	return sight;
}

void Nature::tryToEat(int posX, int posY)
{
	plants[posX][posY] = false;
}

bool Nature::isTileFree(int posX, int posY)
{
	bool free = true;
	for (auto animal = animals.begin(); animal != animals.end(); animal++)
	{
		if ((*animal)->getPosX() == posX && (*animal)->getPosY() == posY)
		{
			free = false;
			break;
		}
	}
	return free;
}

bool Nature::getViewValueOfPos(int posX, int posY)
{
	return (posX >= 0 && posY >= 0 && posX < width && posY < height && plants[posX][posY]);
}