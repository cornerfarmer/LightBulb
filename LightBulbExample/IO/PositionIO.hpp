#pragma once

#ifndef _POSITIONIO_H_
#define _POSITIONIO_H_

// Includes
#include "Examples/Position.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/vector.hpp>

template <class Archive>
void save(Archive& archive, Position const& object)
{
	archive(cereal::base_class<AbstractSimpleEvolutionObject>(&object));
	archive(cereal::make_nvp("position", object.position));
}

template <class Archive>
void load(Archive& archive, Position& object)
{
	archive(cereal::base_class<AbstractSimpleEvolutionObject>(&object));
	archive(cereal::make_nvp("position", object.position));
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(Position);

#endif