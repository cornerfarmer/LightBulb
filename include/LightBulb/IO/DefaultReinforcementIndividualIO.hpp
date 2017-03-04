#pragma once

#ifndef _DEFAULTINDIVIDUALENVIRONMENTIO_H_
#define _DEFAULTINDIVIDUALENVIRONMENTIO_H_

// Includes
#include "LightBulb/Learning/Reinforcement/DefaultReinforcementIndividual.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes an DefaultReinforcementIndividual
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param individual The DefaultReinforcementIndividual to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, DefaultReinforcementIndividual& individual);
}

#include "LightBulb/IO/TemplateDeclaration.hpp"
CEREAL_FORCE_DYNAMIC_INIT_FIXED(DefaultReinforcementIndividual)

#endif