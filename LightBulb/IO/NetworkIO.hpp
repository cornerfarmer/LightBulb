#pragma once

#ifndef _NETWORKIO_H_
#define _NETWORKIO_H_

// Includes
#include "Examples/Network.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>

template <class Archive>
void save(Archive& archive, Network const& object)
{
	archive(cereal::base_class<AbstractSimpleEvolutionObject>(&object));
	archive(cereal::make_nvp("positions", object.positions));
}

template <class Archive>
void load(Archive& archive, Network& object)
{
	archive(cereal::base_class<AbstractSimpleEvolutionObject>(&object));
	archive(cereal::make_nvp("positions", object.positions));
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(Network);

#endif