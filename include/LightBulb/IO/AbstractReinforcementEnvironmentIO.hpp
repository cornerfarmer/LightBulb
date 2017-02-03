#pragma once

#ifndef _ABSTRACTREINFORCEMENTENVIRONMENTIO_H_
#define _ABSTRACTREINFORCEMENTENVIRONMENTIO_H_

// Includes
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementEnvironment.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes an AbstractReinforcementEnvironment
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param environment The AbstractReinforcementEnvironment to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, AbstractReinforcementEnvironment& environment);
}

#endif