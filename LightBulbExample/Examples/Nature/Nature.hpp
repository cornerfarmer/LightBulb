#pragma once

#ifndef _NATURE_H_
#define _NATURE_H_

// Library Includes
#include <vector>

// Include
#include "Learning/Evolution/AbstractSimpleEvolutionWorld.hpp"
#include "Examples/Nature/AbstractTile.hpp"

// Forward declarations
class Animal;
class AbstractTile;

enum NatureEvents
{
	EVT_FIELD_CHANGED
};

class Nature : public LightBulb::AbstractSimpleEvolutionWorld, public LightBulb::Observable<NatureEvents, Nature>
{
protected:
	std::vector<std::vector<std::unique_ptr<AbstractTile>>> tiles;
	int width;
	int height;
	bool watchMode;
	double getViewValueOfPos(int posX, int posY);
	int missingPlants;	
	bool displayMode;
	LightBulb::AbstractEvolutionObject* createNewObject() override;
	void resetWorld() override;
public:
	Nature();
	bool doSimulationStep() override;
	std::vector<double> getSight(int posX, int posY, int dirX, int dirY);
	double tryToEat(int posX, int posY);
	bool isTileFree(int posX, int posY);
	int getWidth();
	int getHeight();
	void addRandomPlant();
	std::vector<std::vector<std::unique_ptr<AbstractTile>>>* getTiles();
	double getScore(LightBulb::AbstractEvolutionObject* object) override;
	AbstractTile* getTile(int posX, int posY);
	void startWatchMode();
	void stopWatchMode();
};

#endif
