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
	/**
	* \brief Saves an AbstractSimpleEvolutionObject
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param object The AbstractSimpleEvolutionObject to save.
	*/
	template <class Archive>
	void save(Archive& archive, AbstractSimpleEvolutionObject const& object)
	{
		archive(cereal::base_class<AbstractEvolutionObject>(&object));
		archive(cereal::make_nvp("neuralNetwork", object.neuralNetwork));
	}

	/**
	* \brief Loads an AbstractSimpleEvolutionObject
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param object The AbstractSimpleEvolutionObject to load.
	*/
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