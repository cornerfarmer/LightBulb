#pragma once

#ifndef _ABSTRACTREINFORCEMENTWORLDIO_H_
#define _ABSTRACTREINFORCEMENTWORLDIO_H_

// Includes
#include "Learning/Reinforcement/AbstractReinforcementWorld.hpp"

// Libraray includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes an AbstractReinforcementWorld
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param world The AbstractReinforcementWorld to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, AbstractReinforcementWorld& world)
	{
		archive(cereal::make_nvp("neuralNetwork", world.neuralNetwork));
		archive(cereal::make_nvp("epsilon", world.epsilon));
	}
}

#endif