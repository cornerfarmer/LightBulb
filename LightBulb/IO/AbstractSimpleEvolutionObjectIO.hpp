#pragma once

#ifndef _ABSTRACTSIMPLEEVOLUTIONOBJECTIO_H_
#define _ABSTRACTSIMPLEEVOLUTIONOBJECTIO_H_

// Includes
#include "Learning/Evolution/AbstractSimpleEvolutionObject.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

template <class Archive>
void serialize(Archive& archive, AbstractSimpleEvolutionObject& object)
{
	archive(cereal::base_class<AbstractEvolutionObject>(&object));
	archive(cereal::make_nvp("neuralNetwork", object.neuralNetwork));
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(AbstractSimpleEvolutionObject);

#endif