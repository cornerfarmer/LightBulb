// Includes
#include "Examples/PongEvolution/PongGame.hpp"
#include "LightBulb/Random/AbstractRandomGenerator.hpp"
//Library includes

PongGame::PongGame()
{
	watchMode = false;
	properties.minBallSpeed.getEigenValueForEditing() = 2;
	properties.width.getEigenValueForEditing() = 210;
	properties.height.getEigenValueForEditing() = 160;
	properties.ballRad.getEigenValueForEditing() = 5;
	properties.paddleSpeed.getEigenValueForEditing() = 5;
	properties.paddleHeight.getEigenValueForEditing() = 30;
	properties.paddleWidth.getEigenValueForEditing() = 10;
	properties.maxTime.getEigenValueForEditing() = 1000; // 1000
	properties.speedIncreaseFac.getEigenValueForEditing() = 1; // 1.2
	properties.maxBallSpeed.getEigenValueForEditing() = 3;// properties.width / ((double)(properties.height - properties.paddleHeight) / properties.paddleSpeed);

	state.ballPosX.getEigenValueForEditing() = 0;
	state.ballPosY.getEigenValueForEditing() = 0;
	state.ballVelX.getEigenValueForEditing() = 0;
	state.ballVelY.getEigenValueForEditing() = 0;
	state.paddle1Pos.getEigenValueForEditing() = 0;
	state.paddle2Pos.getEigenValueForEditing() = 0;
}


void PongGame::movePaddle(int dir)
{
	if (currentPlayer.getEigenValue() == 1)
	{
		if (dir == 1)
			state.paddle1Pos.getEigenValueForEditing() += properties.paddleSpeed.getEigenValue();
		else if(dir == -1)
			state.paddle1Pos.getEigenValueForEditing() -= properties.paddleSpeed.getEigenValue();
		state.paddle1Pos.getEigenValueForEditing() = std::max(0.0f, std::min(static_cast<float>(properties.height.getEigenValue() - properties.paddleHeight.getEigenValue()), state.paddle1Pos.getEigenValue()));
	}
	else
	{
		if (dir == 1)
			state.paddle2Pos.getEigenValueForEditing() += properties.paddleSpeed.getEigenValue();
		else if (dir == -1)
			state.paddle2Pos.getEigenValueForEditing() -= properties.paddleSpeed.getEigenValue();
		state.paddle2Pos.getEigenValueForEditing() = std::max(0.0f, std::min(static_cast<float>(properties.height.getEigenValue() - properties.paddleHeight.getEigenValue()), state.paddle2Pos.getEigenValue()));
	}
}

PongGameState& PongGame::getState()
{
	return state;
}

PongGameProperties& PongGame::getProperties()
{
	return properties;
}


void PongGame::executeCompareAI()
{
	if (state.ballPosY.getEigenValue() > state.paddle2Pos.getEigenValue() + properties.paddleHeight.getEigenValue() / 2)
		movePaddle(1);
	else
		movePaddle(-1);
}

int PongGame::whoHasWon()
{
	if (state.ballPosX.getEigenValue() + properties.ballRad.getEigenValue() >= properties.width.getEigenValue() && state.ballVelX.getEigenValue() > 0)
		return -1;
	else if (state.ballPosX.getEigenValue() <= 0 && state.ballVelX.getEigenValue() < 0)
		return 1;
	else
		return 0;
}

void PongGame::advanceBall(double fac)
{
	float nextBallPosX = state.ballPosX.getEigenValue() + state.ballVelX.getEigenValue() * fac;
	float nextBallPosY = state.ballPosY.getEigenValue() + state.ballVelY.getEigenValue() * fac;

	double colTimeX = 0, colTimeY = 0;

	if (nextBallPosY <= 0 && state.ballVelY.getEigenValue() < 0)
		colTimeY = state.ballPosY.getEigenValue() / -state.ballVelY.getEigenValue();

	if (nextBallPosY + properties.ballRad.getEigenValue() >= properties.height.getEigenValue() && state.ballVelY.getEigenValue() > 0)
		colTimeY = (properties.height.getEigenValue() - (state.ballPosY.getEigenValue() + properties.ballRad.getEigenValue())) / state.ballVelY.getEigenValue();

	if (nextBallPosX <= 0 && state.ballVelX.getEigenValue() < 0)
		colTimeX = state.ballPosX.getEigenValue() / -state.ballVelX.getEigenValue();

	if (nextBallPosX + properties.ballRad.getEigenValue() >= properties.width.getEigenValue() && state.ballVelX.getEigenValue() > 0)
		colTimeX = (properties.width.getEigenValue() - (state.ballPosX.getEigenValue() + properties.ballRad.getEigenValue())) / state.ballVelX.getEigenValue();


	if (colTimeX > 0 && (colTimeY == 0 || colTimeX <= colTimeY))
	{
		advanceBallWithoutCollision(colTimeX);
		if ((state.ballVelX.getEigenValue() > 0 && state.ballPosY.getEigenValue() + properties.ballRad.getEigenValue() >= state.paddle1Pos.getEigenValue() && state.ballPosY.getEigenValue() <= state.paddle1Pos.getEigenValue() + properties.paddleHeight.getEigenValue()) ||
			(state.ballVelX.getEigenValue() < 0 && state.ballPosY.getEigenValue() + properties.ballRad.getEigenValue() >= state.paddle2Pos.getEigenValue() && state.ballPosY.getEigenValue() <= state.paddle2Pos.getEigenValue() + properties.paddleHeight.getEigenValue()))
		{
			state.ballVelX.getEigenValueForEditing() *= -1;
			//advanceBall(fac - colTimeX);
			if (std::abs(state.ballVelX.getEigenValue() * properties.speedIncreaseFac.getEigenValue()) < properties.maxBallSpeed.getEigenValue() && std::abs(state.ballVelY.getEigenValue() * properties.speedIncreaseFac.getEigenValue()) < properties.maxBallSpeed.getEigenValue()) {
				state.ballVelX.getEigenValueForEditing() *= properties.speedIncreaseFac.getEigenValue();
				state.ballVelY.getEigenValueForEditing() *= properties.speedIncreaseFac.getEigenValue();
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
		state.ballVelY.getEigenValueForEditing() *= -1;
		//advanceBall(fac - colTimeY);
	}
	else
		advanceBallWithoutCollision(fac);
}

void PongGame::advanceBallWithoutCollision(double fac)
{
	state.ballPosX.getEigenValueForEditing() += state.ballVelX.getEigenValue() * fac;
	state.ballPosY.getEigenValueForEditing() += state.ballVelY.getEigenValue() * fac;
}

void PongGame::setPlayer(int i)
{
	currentPlayer.getEigenValueForEditing() = i;
}

LightBulb::Scalar<int>& PongGame::getPlayer()
{
	return currentPlayer;
}

void PongGame::reset()
{
	state.ballPosX.getEigenValueForEditing() = properties.width.getEigenValue() / 2;
	state.ballPosY.getEigenValueForEditing() = properties.height.getEigenValue() / 2;
	
	state.ballVelX.getEigenValueForEditing() = randomGenerator->randFloat() * (properties.maxBallSpeed.getEigenValue() - properties.minBallSpeed.getEigenValue()) / 8.0f + properties.minBallSpeed.getEigenValue();
	if (randomGenerator->randFloat() > 0.5f)
		state.ballVelX.getEigenValueForEditing() *= -1;
	state.ballVelY.getEigenValueForEditing() = randomGenerator->randFloat() * (properties.maxBallSpeed.getEigenValue() - properties.minBallSpeed.getEigenValue()) / 8.0f + properties.minBallSpeed.getEigenValue();
	if (randomGenerator->randFloat() > 0.5f)
		state.ballVelY.getEigenValueForEditing() *= -1;

	//state.ballVelX = 3;
	//state.ballVelY = 3;

	state.paddle1Pos.getEigenValueForEditing() = properties.height.getEigenValue() / 2;
	state.paddle2Pos.getEigenValueForEditing() = properties.height.getEigenValue() / 2;
}
