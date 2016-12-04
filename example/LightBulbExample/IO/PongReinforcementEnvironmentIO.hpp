#pragma once

#ifndef _PONGREINFORCEMENTENVIRONMENTIO_H_
#define _PONGREINFORCEMENTENVIRONMENTIO_H_

// Libary includes
#include "Examples/PongReinforcement/PongReinforcementEnvironment.hpp"
#include "LightBulb/IO/ConstructExisting.hpp"

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

template <class Archive>
void serialize(Archive& archive, PongReinforcementEnvironment& environment)
{
	archive(cereal::base_class<LightBulb::AbstractReinforcementEnvironment>(&environment));
	archive(cereal::make_nvp("time", environment.time));
	archive(cereal::make_nvp("game", environment.game));
}


namespace cereal
{
	CONSTRUCT_EXISTING(PongReinforcementEnvironment, LightBulb::AbstractReinforcementEnvironment)
	{
		template <class Archive>
		static void construct(Archive& ar, PongReinforcementEnvironment& environment)
		{
			using namespace LightBulb;
			ar(base_class<AbstractReinforcementEnvironment>(&environment));
			ar(make_nvp("time", environment.time));

			IOStorage<PongGame>::push(&environment.game);
			ar(make_nvp("game", environment.game));
			IOStorage<PongGame>::clear();
		}
	};
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(PongReinforcementEnvironment);

#endif
