#pragma once

#ifndef _PONGREINFORCEMENTWORLDIO_H_
#define _PONGREINFORCEMENTWORLDIO_H_

// Libary includes
#include "Examples/PongReinforcement/PongReinforcementWorld.hpp"
#include "IO/ConstructExisting.hpp"

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

template <class Archive>
void serialize(Archive& archive, PongReinforcementWorld& world)
{
	archive(cereal::base_class<LightBulb::AbstractReinforcementWorld>(&world));
	archive(cereal::make_nvp("time", world.time));
	archive(cereal::make_nvp("game", world.game));
}


namespace cereal
{
	CONSTRUCT_EXISTING(PongReinforcementWorld, LightBulb::AbstractReinforcementWorld)
	{
		template <class Archive>
		static void construct(Archive& ar, PongReinforcementWorld& world)
		{
			using namespace LightBulb;
			ar(base_class<AbstractReinforcementWorld>(&world));
			ar(make_nvp("time", world.time));

			IOStorage<PongGame>::push(&world.game);
			ar(make_nvp("game", world.game));
			IOStorage<PongGame>::clear();
		}
	};
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(PongReinforcementWorld);

#endif
