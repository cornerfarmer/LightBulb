#pragma once

#ifndef _ABSTRACTREINFORCEMENTWORLDIO_H_
#define _ABSTRACTREINFORCEMENTWORLDIO_H_

// Includes
#include "Learning/Reinforcement/AbstractReinforcementWorld.hpp"

// Libraray includes
#include <cereal/cereal.hpp>

template <class Archive>
void save(Archive& archive, AbstractReinforcementWorld const& world)
{
	archive(cereal::make_nvp("neuralNetwork", world.neuralNetwork));
	archive(cereal::make_nvp("epsilon", world.epsilon));
}

template <class Archive>
void load(Archive& archive, AbstractReinforcementWorld& world)
{
	archive(cereal::make_nvp("neuralNetwork", world.neuralNetwork));
	archive(cereal::make_nvp("epsilon", world.epsilon));
}

#endif