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

#include "LightBulb/IO/TemplateDeclaration.hpp"
CEREAL_FORCE_DYNAMIC_INIT_FIXED(PongReinforcementEnvironment)

#endif
