#pragma once

#ifndef _PONGGAME_H_
#define _PONGGAME_H_

// Library Includes
#include "cereal/access.hpp"

// Include
#include "LightBulb/Random/AbstractRandomGeneratorUser.hpp"
#include "LightBulb/LinearAlgebra/Scalar.hpp"

// Forward declarations

struct PongGameState
{
	LightBulb::Scalar<> ballVelX;
	LightBulb::Scalar<> ballVelY;
	LightBulb::Scalar<> ballPosX;
	LightBulb::Scalar<> ballPosY;
	LightBulb::Scalar<> paddle1Pos;
	LightBulb::Scalar<> paddle2Pos;
};

struct PongGameProperties
{
	LightBulb::Scalar<int> width;
	LightBulb::Scalar<int> height;
	LightBulb::Scalar<int> ballRad;
	LightBulb::Scalar<int> paddleHeight;
	LightBulb::Scalar<int> paddleWidth;
	LightBulb::Scalar<int> paddleSpeed;
	LightBulb::Scalar<int> maxBallSpeed;
	LightBulb::Scalar<int> minBallSpeed;
	LightBulb::Scalar<int> maxTime;
	LightBulb::Scalar<> speedIncreaseFac;
};

class PongGame : public LightBulb::AbstractRandomGeneratorUser
{
	template <class Archive>
	friend void serialize(Archive& archive, PongGame& game);
	friend struct cereal::LoadAndConstruct<PongGame>;
private:
	PongGameState state;
	PongGameProperties properties;
	LightBulb::Scalar<int> currentPlayer;
	bool watchMode;
public:
	PongGame();
	void executeCompareAI();
	void movePaddle(int dir);
	PongGameState& getState();
	PongGameProperties& getProperties();
	const PongGameState& getState() const;
	const PongGameProperties& getProperties() const;
	void reset();
	int whoHasWon() const;
	void advanceBall(double fac);
	void advanceBallWithoutCollision(double fac);
	void setPlayer(int i);
	LightBulb::Scalar<int>& getPlayer();
};

#include "IO/PongGameIO.hpp"

#endif
