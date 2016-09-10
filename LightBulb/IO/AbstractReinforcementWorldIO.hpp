#pragma once

#ifndef _ABSTRACTREINFORCEMENTWORLDIO_H_
#define _ABSTRACTREINFORCEMENTWORLDIO_H_

// Includes
#include "Learning/Reinforcement/AbstractReinforcementWorld.hpp"

// Libraray includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	template <class Archive>
	void serialize(Archive& archive, AbstractReinforcementWorld& world)
	{
		archive(cereal::make_nvp("neuralNetwork", world.neuralNetwork));
		archive(cereal::make_nvp("epsilon", world.epsilon));
	}
}

#endif