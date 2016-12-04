#pragma once

#ifndef _ABSTRACTREINFORCEMENTENVIRONMENTIO_H_
#define _ABSTRACTREINFORCEMENTENVIRONMENTIO_H_

// Includes
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementEnvironment.hpp"

// Libraray includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes an AbstractReinforcementEnvironment
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param environment The AbstractReinforcementEnvironment to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, AbstractReinforcementEnvironment& environment)
	{
		archive(cereal::make_nvp("neuralNetwork", environment.neuralNetwork));
		archive(cereal::make_nvp("epsilon", environment.epsilon));
	}
}

#endif