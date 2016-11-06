#pragma once

#ifndef _ABSTRACTSIMPLEEVOLUTIONWORLDIO_H_
#define _ABSTRACTSIMPLEEVOLUTIONWORLDIO_H_

// Includes
#include "Learning/Evolution/AbstractSimpleEvolutionWorld.hpp"
#include "Learning/Evolution/AbstractEvolutionObject.hpp"
#include "IO/IOStorage.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	/**
	* \brief Saves an AbstractSimpleEvolutionWorld
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param world The AbstractSimpleEvolutionWorld to save.
	*/
	template <class Archive>
	void save(Archive& archive, AbstractSimpleEvolutionWorld const& world)
	{
		std::vector<std::unique_ptr<AbstractEvolutionObject>> objects;
		for (auto worldObject = world.objects.begin(); worldObject != world.objects.end(); worldObject++)
			objects.push_back(std::unique_ptr<AbstractEvolutionObject>(*worldObject));

		archive(cereal::make_nvp("objects", objects));

		for (auto object = objects.begin(); object != objects.end(); object++)
			object->release();
	}

	/**
	* \brief Loads an AbstractSimpleEvolutionWorld
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param world The AbstractSimpleEvolutionWorld to load.
	*/
	template <class Archive>
	void load(Archive& archive, AbstractSimpleEvolutionWorld& world)
	{
		std::vector<std::unique_ptr<AbstractEvolutionObject>> objects;
		IOStorage<AbstractEvolutionWorld>::push(&world);
		archive(cereal::make_nvp("objects", objects));
		IOStorage<AbstractEvolutionWorld>::clear();

		for (auto object = objects.begin(); object != objects.end(); object++)
		{
			world.objects.push_back(object->release());
		}
	}
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::AbstractSimpleEvolutionWorld);

#endif