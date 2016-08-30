#pragma once

#ifndef _PONGGAME_H_
#define _PONGGAME_H_

// Library Includes

// Include
#include "Random/AbstractRandomGeneratorUser.hpp"

// Forward declarations

struct PongGameState
{
	double ballVelX;
	double ballVelY; 
	double ballPosX; 
	double ballPosY;
	double paddle1Pos;
	double paddle2Pos;
	bool ballCollidedWithPaddle;
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

class PongGame : public AbstractRandomGeneratorUser
{
private:
	PongGameState state;
	PongGameProperties properties;
	int currentPlayer;
	bool watchMode;
public:
	PongGame();
	void executeCompareAI();
	void movePaddle(int dir);
	PongGameState getState();
	PongGameProperties getProperties();
	void reset();
	int whoHasWon();
	void advanceBall(double fac);
	void advanceBallWithoutCollision(double fac);
	void setPlayer(int i);
	int getPlayer();
};


#endif
