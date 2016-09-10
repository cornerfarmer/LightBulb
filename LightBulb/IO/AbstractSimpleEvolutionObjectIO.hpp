#pragma once

#ifndef _ABSTRACTSIMPLEEVOLUTIONOBJECTIO_H_
#define _ABSTRACTSIMPLEEVOLUTIONOBJECTIO_H_

// Includes
#include "Learning/Evolution/AbstractSimpleEvolutionObject.hpp"
#include "IOStorage.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	template <class Archive>
	void save(Archive& archive, AbstractSimpleEvolutionObject const& object)
	{
		archive(cereal::base_class<AbstractEvolutionObject>(&object));
		archive(cereal::make_nvp("neuralNetwork", object.neuralNetwork));
	}

	template <class Archive>
	void load(Archive& archive, AbstractSimpleEvolutionObject& object)
	{
		archive(cereal::base_class<AbstractEvolutionObject>(&object));
		archive(cereal::make_nvp("neuralNetwork", object.neuralNetwork));
		object.buildOutputBuffer();
		object.world = IOStorage<AbstractEvolutionWorld>::get();
	}
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::AbstractSimpleEvolutionObject);

#endif