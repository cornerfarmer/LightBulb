#pragma once

#ifndef _PONGGAMEIO_H_
#define _PONGGAMEIO_H_

// Libary includes
#include "Examples/PongEvolution/PongGame.hpp"
#include "LightBulb/IO/ConstructExisting.hpp"

template <class Archive>
extern void serialize(Archive& archive, PongGameState& state);

template <class Archive>
extern void serialize(Archive& archive, PongGame& game);

namespace cereal
{
	CONSTRUCT_EXISTING(PongGame, PongGame)
	{
		template <class Archive>
		static void construct(Archive& ar, PongGame& game);
	};
}

#endif
