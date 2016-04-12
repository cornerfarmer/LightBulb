#pragma once

#ifndef _RBFNETWORKIO_H_
#define _RBFNETWORKIO_H_

// Libary includes
#include <NetworkTopology/RBFNetwork.hpp>

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>


template <class Archive>
void save(Archive& archive, RBFNetwork const & rbfNetwork)
{
	archive(cereal::base_class<LayeredNetwork>(&rbfNetwork));
	archive(cereal::make_nvp("neuronWidths", rbfNetwork.neuronWidths));
}

template <class Archive>
void load(Archive& archive, RBFNetwork & rbfNetwork)
{
	archive(cereal::base_class<LayeredNetwork>(&rbfNetwork));
	archive(cereal::make_nvp("neuronWidths", rbfNetwork.neuronWidths));
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(RBFNetwork);

#endif
