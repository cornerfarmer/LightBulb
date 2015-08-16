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
	
	drawer.reset(new NatureDrawer(options));
}

void Nature::doSimulationStep(EvolutionLearningRule& learningRule)
{
	while (window.isOpen())
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
			animals[i]->doNNCalculation(learningRule);
			if (animals[i]->isDead())
			{
				animals.erase(animals.begin() + i);
				if (i != 0)
					i--;
				if (animals.size() == 0)
					break;
			}
		}

		if (animals.size() < 5)
			addNewObject();
		sf::sleep(sf::milliseconds(100));
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

bool Nature::tryToEat(int posX, int posY)
{
	if (posX >= 0 && posY >= 0 && posX < width && posY < height)
	{
		if (plants[posX][posY])
		{
			plants[posX][posY] = false;
			return true;
		}
	}
	return false;
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
