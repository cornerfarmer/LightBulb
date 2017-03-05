#pragma once

#ifndef _ABSTRACTDEFAULTINDIVIDUALENVIRONMENTIO_H_
#define _ABSTRACTDEFAULTINDIVIDUALENVIRONMENTIO_H_

// Includes
#include "LightBulb/Learning/Reinforcement/AbstractDefaultReinforcementIndividual.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes an AbstractDefaultReinforcementIndividual
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param individual The AbstractDefaultReinforcementIndividual to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, AbstractDefaultReinforcementIndividual& individual);
}

#include "LightBulb/IO/TemplateDeclaration.hpp"
CEREAL_FORCE_DYNAMIC_INIT_FIXED(AbstractDefaultReinforcementIndividual)

#endif