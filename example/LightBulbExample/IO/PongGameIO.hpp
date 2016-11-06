#pragma once

#ifndef _PONGGAMEIO_H_
#define _PONGGAMEIO_H_

// Libary includes
#include "Examples/PongEvolution/PongGame.hpp"
#include "IO/ConstructExisting.hpp"

#include <cereal/cereal.hpp>

template <class Archive>
void serialize(Archive& archive, PongGameState& state)
{
	archive(cereal::make_nvp("ballPosX", state.ballPosX));
	archive(cereal::make_nvp("ballPosY", state.ballPosY));
	archive(cereal::make_nvp("ballVelX", state.ballVelX));
	archive(cereal::make_nvp("ballVelY", state.ballVelY));
	archive(cereal::make_nvp("paddle1Pos", state.paddle1Pos));
	archive(cereal::make_nvp("paddle2Pos", state.paddle2Pos));
}


template <class Archive>
void serialize(Archive& archive, PongGame& game)
{
	archive(cereal::make_nvp("state", game.state));
}


namespace cereal
{
	CONSTRUCT_EXISTING(PongGame, PongGame)
	{
		template <class Archive>
		static void construct(Archive& ar, PongGame& game)
		{
			ar(make_nvp("state", game.state));
		}
	};
}

#endif
