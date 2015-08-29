// Includes
#include "Examples\Nature.hpp"
#include "Examples\Animal.hpp"


EvolutionObjectInterface* Nature::addNewObject()
{
	animals.push_back(new Animal(this, (int)((float)rand() / RAND_MAX * width), (int)((float)rand() / RAND_MAX * height), 0, 1));
	
	return animals.back();
}

Nature::Nature()
{
	missingPlants = 0;
	width = 60;
	height = 60;

	plants.resize(width);
	for (int x = 0; x < width; x++)
	{
		plants[x].resize(height);
		for (int y = 0; y < height; y++)
		{
			plants[x][y] = true;
		}
	}

	window.create(sf::VideoMode(800, 700), "LightBulb!");
	NatureDrawerOptions options;
	options.nature = this;
	options.scalingX = 10;
	options.scalingY = 10;
	drawer.reset(new NatureDrawer(options));
}

void Nature::doSimulationStep(EvolutionLearningRule& learningRule)
{
	int deadAnimals = 0;
	while (animals.size() - deadAnimals > 0)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		drawer->recalculateAllValues();
		drawer->draw(window);
		window.display();

		for (int i = 0; i < animals.size(); i++)
		{
			if (!animals[i]->isDead())
			{
				animals[i]->doNNCalculation(learningRule);
				if (animals[i]->isDead())
				{
					deadAnimals++;
				}
			}
		}

		/*for (int i = 0; i < 3 && rand() < RAND_MAX / 20; i++)
			addRandomPlant();*/

		sf::sleep(sf::milliseconds(25));
	}
}

EvolutionObjectInterface* Nature::getEvolutionObject(int index)
{
	return animals[index];
}

void Nature::removeEvolutionObject(EvolutionObjectInterface* evolutionObject)
{
	animals.erase(std::remove(animals.begin(), animals.end(), evolutionObject), animals.end());
}

bool Nature::isBetterThan(EvolutionObjectInterface* first, EvolutionObjectInterface* second)
{
	return static_cast<Animal*>(first)->getStepsSurvived() > static_cast<Animal*>(second)->getStepsSurvived();
}

int Nature::getEvolutionObjectCount()
{
	return animals.size();
}

void Nature::reset()
{
	for (auto animal = animals.begin(); animal != animals.end(); animal++)
	{
		(*animal)->reset((int)((float)rand() / RAND_MAX * width), (int)((float)rand() / RAND_MAX * height), 0, 1);
	}
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			plants[x][y] = true;
		}
	}
}

void Nature::addRandomPlant()
{
	if (missingPlants > 0)
	{
		int posX, posY;
		do {
			posX = (float)rand() / RAND_MAX * (width - 1);
			posY = (float)rand() / RAND_MAX * (height - 1);
		} while (plants[posX][posY]);
		plants[posX][posY] = true;
		missingPlants--;
	}
}

std::vector<double> Nature::getSight(int posX, int posY, int dirX, int dirY)
{
	std::vector<double> sight;
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

bool Nature::tryToEat(int posX, int posY)
{
	if (posX >= 0 && posY >= 0 && posX < width && posY < height)
	{
		if (plants[posX][posY])
		{
			plants[posX][posY] = false;
			missingPlants++;
			return true;
		}
	}
	return false;
}

bool Nature::isTileFree(int posX, int posY)
{
	if (posX >= 0 && posY >= 0 && posX < width && posY < height)
	{
		bool free = true;
		for (auto animal = animals.begin(); animal != animals.end(); animal++)
		{
			if (!(*animal)->isDead() && (*animal)->getPosX() == posX && (*animal)->getPosY() == posY)
			{
				free = false;
				break;
			}
		}

		return free;
	}
	else
	{
		return false;
	}
}

double Nature::getViewValueOfPos(int posX, int posY)
{
	if (posX >= 0 && posY >= 0 && posX < width && posY < height)
	{
		if (plants[posX][posY])
			return 1;
		else if (!isTileFree(posX, posY))
			return 0;
		else
			return -1;
	}
	else
		return -1;
}

int Nature::getWidth()
{
	return width;
}

int Nature::getHeight()
{
	return height;
}

std::vector<std::vector<bool>>* Nature::getPlants()
{
	return &plants;
}
