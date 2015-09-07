#pragma once

#ifndef _NATURE_H_
#define _NATURE_H_

// Library Includes
#include <vector>
#include <SFML\Graphics.hpp>

// Include
#include "Learning\EvolutionWorldInterface.hpp"
#include "Examples\NatureDrawer.hpp"
#include "Examples\AbstractTile.hpp"

// Forward declarations
class EvolutionLearningRule;
class EvolutionObjectInterface;
class Animal;
class AbstractTile;

class Nature : public EvolutionWorldInterface
{
	std::vector<EvolutionObjectInterface*> animals;
	std::vector<std::vector<std::unique_ptr<AbstractTile>>> tiles;
	int width;
	int height;
	double getViewValueOfPos(int posX, int posY);
	sf::RenderWindow window;
	std::unique_ptr<NatureDrawer> drawer;
	int missingPlants;	
public:
	Nature();
	EvolutionObjectInterface* addNewObject();
	void doSimulationStep(EvolutionLearningRule& learningRule);
	std::vector<double> getSight(int posX, int posY, int dirX, int dirY);
	double tryToEat(int posX, int posY);
	bool isTileFree(int posX, int posY);
	int getWidth();
	int getHeight();
	void addRandomPlant();
	std::vector<std::vector<std::unique_ptr<AbstractTile>>>* Nature::getTiles();
	int getScore(EvolutionObjectInterface* object);
	std::vector<EvolutionObjectInterface*>* getEvolutionObjects();
	void setEvolutionObjects(std::vector<EvolutionObjectInterface*>& newObjects);
	void reset();
	AbstractTile* getTile(int posX, int posY);
};

#endif