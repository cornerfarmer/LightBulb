#pragma once

#ifndef _NETWORKIO_H_
#define _NETWORKIO_H_

// Includes
#include "Examples/NetworkEvolution/Network.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>

template <class Archive>
void save(Archive& archive, Network const& individual)
{
	archive(cereal::base_class<LightBulb::AbstractDefaultIndividual>(&individual));
	archive(cereal::make_nvp("positions", individual.positions));
}

template <class Archive>
void load(Archive& archive, Network& individual)
{
	archive(cereal::base_class<LightBulb::AbstractDefaultIndividual>(&individual));
	archive(cereal::make_nvp("positions", individual.positions));
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(Network);

#endif