#pragma once

#ifndef _NATURE_H_
#define _NATURE_H_

// Library Includes
#include <vector>
#include <SFML\Graphics.hpp>

// Include
#include "Learning\AbstractSimpleEvolutionWorld.hpp"
#include "Examples\NatureDrawer.hpp"
#include "Examples\AbstractTile.hpp"

// Forward declarations
class EvolutionLearningRule;
class EvolutionObjectInterface;
class Animal;
class AbstractTile;

class Nature : public AbstractSimpleEvolutionWorld
{
protected:
	std::vector<std::vector<std::unique_ptr<AbstractTile>>> tiles;
	int width;
	int height;
	double getViewValueOfPos(int posX, int posY);
	sf::RenderWindow window;
	std::unique_ptr<NatureDrawer> drawer;
	int missingPlants;	
	bool displayMode;
	EvolutionObjectInterface* createNewObject();
	void resetWorld();
public:
	Nature();
	void doSimulationStep(EvolutionLearningRule& learningRule);
	std::vector<double> getSight(int posX, int posY, int dirX, int dirY);
	double tryToEat(int posX, int posY);
	bool isTileFree(int posX, int posY);
	int getWidth();
	int getHeight();
	void addRandomPlant();
	std::vector<std::vector<std::unique_ptr<AbstractTile>>>* Nature::getTiles();
	double getScore(EvolutionObjectInterface* object);
	AbstractTile* getTile(int posX, int posY);
};

#endif