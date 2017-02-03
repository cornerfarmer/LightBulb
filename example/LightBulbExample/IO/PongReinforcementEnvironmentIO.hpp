#pragma once

#ifndef _PONGREINFORCEMENTENVIRONMENTIO_H_
#define _PONGREINFORCEMENTENVIRONMENTIO_H_

// Libary includes
#include "Examples/PongReinforcement/PongReinforcementEnvironment.hpp"
#include "LightBulb/IO/ConstructExisting.hpp"

template <class Archive>
void serialize(Archive& archive, PongReinforcementEnvironment& environment);

namespace cereal
{
	CONSTRUCT_EXISTING(PongReinforcementEnvironment, LightBulb::AbstractReinforcementEnvironment)
	{
		template <class Archive>
		static void construct(Archive& ar, PongReinforcementEnvironment& environment);
	};
}

#endif
