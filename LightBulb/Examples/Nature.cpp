// Includes
#include "Examples\Nature.hpp"
#include "Examples\Animal.hpp"
#include "Examples\EarthTile.hpp"
#include "Examples\RockTile.hpp"
//Library includes
#include <iostream>


EvolutionObjectInterface* Nature::createNewObject()
{
	int posX = 0;
	int posY = 0;
	do {
		posX = (int)((float)rand() / RAND_MAX * (width - 1));
		posY = (int)((float)rand() / RAND_MAX * (height - 1));
	} while (!tiles[posX][posY]->isWalkable());

	return new Animal(this, posX, posY, 0, 1);
}

Nature::Nature()
{
	missingPlants = 0;
	width = 120;
	height = 120;

	tiles.resize(width);
	for (int x = 0; x < width; x++)
	{
		tiles[x].resize(height);
	}
	resetWorld();


	window.create(sf::VideoMode(800, 700), "LightBulb!");
	NatureDrawerOptions options;
	options.nature = this;
	displayMode = true;
	options.scalingX =  60.0 / width * 10;
	options.scalingY =  60.0 / height * 10;
	drawer.reset(new NatureDrawer(options));
}

void Nature::doSimulationStep(EvolutionLearningRule& learningRule)
{	
	int deadAnimals = 0;

	while (objects.size() - deadAnimals > 0)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed)
				displayMode = !displayMode;
		}

		if (displayMode) {
			window.clear();
			drawer->recalculateAllValues();
			drawer->draw(window);
			window.display();
		}

		for (auto animal = objects.begin(); animal != objects.end(); animal++)
		{
			if (!static_cast<Animal*>(*animal)->isDead())
			{
				static_cast<Animal*>(*animal)->doNNCalculation(learningRule);
				if (static_cast<Animal*>(*animal)->isDead())
				{
					deadAnimals++;
				}
			}
		}

		/*for (int i = 0; i < 3 && rand() < RAND_MAX / 20; i++)
			addRandomPlant();*/

		//sf::sleep(sf::milliseconds(5));
	}
	std::cout << "Animals ate " << missingPlants << " plants" << std::endl;
}

int Nature::getScore(EvolutionObjectInterface* object)
{
	return static_cast<Animal*>(object)->getStepsSurvived();
}

void Nature::resetWorld()
{
	for (auto animal = objects.begin(); animal != objects.end(); animal++)
	{
		int posX = 0;
		int posY = 0;
		do {
			posX = (int)((float)rand() / RAND_MAX * (width - 1));
			posY = (int)((float)rand() / RAND_MAX * (height - 1));
		} while (!tiles[posX][posY]->isWalkable());
		static_cast<Animal*>(*animal)->reset(posX, posY, 0, 1);
	}
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
				tiles[x][y].reset(new RockTile());
			else
			{
				if (abs(sin((double)x / width * 10) * height / 3 + height / 2 - y) < height / 10)
					tiles[x][y].reset(new RockTile());
				else
					tiles[x][y].reset(new EarthTile());
			}
		}
	}
	missingPlants = 0;
}

void Nature::addRandomPlant()
{
	/*if (missingPlants > 0)
	{
		int posX, posY;
		do {
			posX = (float)rand() / RAND_MAX * (width - 1);
			posY = (float)rand() / RAND_MAX * (height - 1);
		} while (tiles[posX][posY]);
		plants[posX][posY] = true;
		missingPlants--;
	}*/
}

std::vector<double> Nature::getSight(int posX, int posY, int dirX, int dirY)
{
	std::vector<double> sight;
	if (dirX == 1 && dirY == 0)
	{
		sight.push_back(getViewValueOfPos(posX + dirX, posY - 2));
		sight.push_back(getViewValueOfPos(posX + dirX, posY - 1));
		sight.push_back(getViewValueOfPos(posX + dirX, posY));
		sight.push_back(getViewValueOfPos(posX + dirX, posY + 1));
		sight.push_back(getViewValueOfPos(posX + dirX, posY + 2));
	}
	else if (dirX == -1 && dirY == 0)
	{
		sight.push_back(getViewValueOfPos(posX + dirX, posY + 2));
		sight.push_back(getViewValueOfPos(posX + dirX, posY + 1));
		sight.push_back(getViewValueOfPos(posX + dirX, posY));
		sight.push_back(getViewValueOfPos(posX + dirX, posY - 1));
		sight.push_back(getViewValueOfPos(posX + dirX, posY - 2));
	}
	else if (dirX == 0 && dirY == 1)
	{
		sight.push_back(getViewValueOfPos(posX + 2, posY + dirY));
		sight.push_back(getViewValueOfPos(posX + 1, posY + dirY));
		sight.push_back(getViewValueOfPos(posX, posY + dirY));
		sight.push_back(getViewValueOfPos(posX - 1, posY + dirY));
		sight.push_back(getViewValueOfPos(posX - 2, posY + dirY));
	}
	else if (dirX == 0 && dirY == -1)
	{
		sight.push_back(getViewValueOfPos(posX - 2, posY + dirY));
		sight.push_back(getViewValueOfPos(posX - 1, posY + dirY));
		sight.push_back(getViewValueOfPos(posX, posY + dirY));
		sight.push_back(getViewValueOfPos(posX + 1,posY + dirY));
		sight.push_back(getViewValueOfPos(posX + 2, posY + dirY));
	}
	return sight;
}

double Nature::tryToEat(int posX, int posY)
{
	if (posX >= 0 && posY >= 0 && posX < width && posY < height)
	{
		float food = tiles[posX][posY]->tryToEat();
		if (food > 0)
			missingPlants++;
		return food;
	}
	return 0;
}

bool Nature::isTileFree(int posX, int posY)
{
	if (posX >= 0 && posY >= 0 && posX < width && posY < height)
	{
		bool free = true;
		for (auto animal = objects.begin(); animal != objects.end(); animal++)
		{
			if (!static_cast<Animal*>(*animal)->isDead() && static_cast<Animal*>(*animal)->getPosX() == posX && static_cast<Animal*>(*animal)->getPosY() == posY)
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
		return tiles[posX][posY]->getViewValue();
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

std::vector<std::vector<std::unique_ptr<AbstractTile>>>* Nature::getTiles()
{
	return &tiles;
}

AbstractTile* Nature::getTile(int posX, int posY)
{
	if (posX < width && posY < height)
		return tiles[posX][posY].get();
	else
		throw std::exception();
}