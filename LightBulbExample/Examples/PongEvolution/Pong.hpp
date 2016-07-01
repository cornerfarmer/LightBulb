#pragma once

#ifndef _PONG_H_
#define _PONG_H_

// Library Includes
#include <vector>
#include <map>
#include <array>
#include <mutex>

// Include
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"
#include "IO/UseParentSerialization.hpp"
#include <NetworkTopology/LayeredNetwork.hpp>

// Forward declarations
class EvolutionLearningRule;
class AbstractEvolutionObject;
class PongAI;
class AbstractTile;

enum PongEvents
{
	EVT_FIELD_CHANGED
};

struct PongGameState
{
	double ballVelX;
	double ballVelY; 
	double ballPosX; 
	double ballPosY;
	double paddle1Pos;
	double paddle2Pos;
};

struct PongGameProperties
{
	int width;
	int height; 
	int ballRad;
	int paddleHeight;
	int paddleWidth; 
	int paddleSpeed; 
	int maxBallSpeed;
	int minBallSpeed;
	int maxTime;
	double speedIncreaseFac;
};


#define DATASET_PONG_RATING "Pong rating"

class Pong : public AbstractCoevolutionWorld, public LightBulb::Observable<PongEvents, Pong>
{
private:
	PongGameState state;
	PongGameProperties properties;
	int currentPlayer;
	bool watchMode;
	void initialize();
	int whoHasWon();
	void advanceBall(double fac);
	void advanceBallWithoutCollision(double fac);
protected:
	AbstractEvolutionObject* createNewObject();
	void resetWorld();
	int simulateGame(PongAI* ai1, PongAI* ai2);
	std::unique_ptr<LayeredNetworkOptions> options;
	int doCompare(AbstractEvolutionObject* obj1, AbstractEvolutionObject* obj2, int round);
public:
	Pong(LayeredNetworkOptions& options_, bool isParasiteWorld, AbstractCombiningStrategy* combiningStrategy_, AbstractCoevolutionFitnessFunction* fitnessFunction_, AbstractHallOfFameAlgorithm* hallOfFameToAddAlgorithm_ = NULL, AbstractHallOfFameAlgorithm* hallOfFameToChallengeAlgorithm_ = NULL);
	Pong() = default;
	void getNNInput(std::vector<double>& sight);
	void executeCompareAI();
	int rateKI(AbstractEvolutionObject* rateKI);
	void startNewGame();
	void initializeForLearning();
	void movePaddle(int dir);
	std::vector<std::string> getDataSetLabels();
	int getRoundCount();
	void startWatchMode();
	void stopWatchMode();
	PongGameState getState();
	PongGameProperties getProperties();
};

USE_EXISTING_PARENT_SERIALIZATION(Pong, AbstractCoevolutionWorld, AbstractEvolutionWorld);

#endif
