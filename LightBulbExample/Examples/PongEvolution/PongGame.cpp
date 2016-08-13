// Includes
#include "Examples/PongEvolution/PongGame.hpp"
#include "Examples/PongEvolution/PongAI.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
//Library includes
#include <iomanip>
#include <chrono>
#include <thread>

PongGame::PongGame()
{
	watchMode = false;
	properties.minBallSpeed = 2;
	properties.width = 210;
	properties.height = 160;
	properties.ballRad = 5;
	properties.paddleSpeed = 5;
	properties.paddleHeight = 30;
	properties.paddleWidth = 10;
	properties.maxTime = 1000; // 1000
	properties.speedIncreaseFac = 1; // 1.2
	properties.maxBallSpeed = 3;// properties.width / ((double)(properties.height - properties.paddleHeight) / properties.paddleSpeed);
}


void PongGame::movePaddle(int dir)
{
	if (currentPlayer == 1)
	{
		if (dir == 1)
			state.paddle1Pos += properties.paddleSpeed;
		else if(dir == -1)
			state.paddle1Pos -= properties.paddleSpeed;
		state.paddle1Pos = std::max(0.0, std::min((double)(properties.height - properties.paddleHeight), state.paddle1Pos));
	}
	else
	{
		if (dir == 1)
			state.paddle2Pos += properties.paddleSpeed;
		else if (dir == -1)
			state.paddle2Pos -= properties.paddleSpeed;
		state.paddle2Pos = std::max(0.0, std::min((double)(properties.height - properties.paddleHeight), state.paddle2Pos));
	}
}

PongGameState PongGame::getState()
{
	return state;
}

PongGameProperties PongGame::getProperties()
{
	return properties;
}


void PongGame::executeCompareAI()
{
	if (state.ballPosY > state.paddle2Pos + properties.paddleHeight / 2)
		movePaddle(1);
	else
		movePaddle(-1);
}

int PongGame::whoHasWon()
{
	if (state.ballPosX + properties.ballRad >= properties.width)
		return -1;
	else if (state.ballPosX <= 0)
		return 1;
	else
		return 0;
}

void PongGame::advanceBall(double fac)
{
	double nextBallPosX = state.ballPosX + state.ballVelX * fac;
	double nextBallPosY = state.ballPosY + state.ballVelY * fac;

	double colTimeX = 0, colTimeY = 0;

	if (nextBallPosY <= 0)
		colTimeY = state.ballPosY / -state.ballVelY;

	if (nextBallPosY + properties.ballRad >= properties.height)
		colTimeY = (properties.height - (state.ballPosY + properties.ballRad)) / state.ballVelY;

	if (nextBallPosX <= 0)
		colTimeX = state.ballPosX / -state.ballVelX;

	if (nextBallPosX + properties.ballRad >= properties.width)
		colTimeX = (properties.width - (state.ballPosX + properties.ballRad)) / state.ballVelX;

	if (colTimeX > 0 && (colTimeY == 0 || colTimeX <= colTimeY))
	{
		advanceBallWithoutCollision(colTimeX);
		if ((state.ballVelX > 0 && state.ballPosY + properties.ballRad >= state.paddle1Pos && state.ballPosY <= state.paddle1Pos + properties.paddleHeight) ||
			(state.ballVelX < 0 && state.ballPosY + properties.ballRad >= state.paddle2Pos && state.ballPosY <= state.paddle2Pos + properties.paddleHeight))
		{
			state.ballVelX *= -1;
			advanceBall(fac - colTimeX);
			if (std::abs(state.ballVelX * properties.speedIncreaseFac) < properties.maxBallSpeed && std::abs(state.ballVelY * properties.speedIncreaseFac) < properties.maxBallSpeed) {
				state.ballVelX *= properties.speedIncreaseFac;
				state.ballVelY *= properties.speedIncreaseFac;
			}
		}
		else
		{
			advanceBallWithoutCollision(fac - colTimeX);
		}
	}
	else if (colTimeY > 0)
	{
		advanceBallWithoutCollision(colTimeY);
		state.ballVelY *= -1;
		advanceBall(fac - colTimeY);
	}
	else
		advanceBallWithoutCollision(fac);
}

void PongGame::advanceBallWithoutCollision(double fac)
{
	state.ballPosX += state.ballVelX * fac;
	state.ballPosY += state.ballVelY * fac;
}

void PongGame::setPlayer(int i)
{
	currentPlayer = i;
}

int PongGame::getPlayer()
{
	return currentPlayer;
}

void PongGame::reset()
{
	state.ballPosX = properties.width / 2;
	state.ballPosY = properties.height / 2;

	state.ballVelX = (double)rand() / RAND_MAX * (properties.maxBallSpeed - properties.minBallSpeed) / 8.0 + properties.minBallSpeed;
	if (rand() > RAND_MAX / 2)
		state.ballVelX *= -1;
	state.ballVelY = (double)rand() / RAND_MAX * (properties.maxBallSpeed - properties.minBallSpeed) / 8.0 + properties.minBallSpeed;
	if (rand() > RAND_MAX / 2)
		state.ballVelY *= -1;

	//state.ballVelX = 3;
	//state.ballVelY = 3;

	state.paddle1Pos = properties.height / 2;
	state.paddle2Pos = properties.height / 2;
}
