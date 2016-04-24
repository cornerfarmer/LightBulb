#pragma once

#ifndef _ABSTRACTSIMPLEEVOLUTIONWORLDIO_H_
#define _ABSTRACTSIMPLEEVOLUTIONWORLDIO_H_

// Includes
#include "Learning/Evolution/AbstractSimpleEvolutionWorld.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

template <class Archive>
void save(Archive& archive, AbstractSimpleEvolutionWorld const& world)
{
	std::vector<std::unique_ptr<AbstractEvolutionObject>> objects;
	for (auto worldObject = world.objects.begin(); worldObject != world.objects.end(); worldObject++)	
		objects.push_back(std::unique_ptr<AbstractEvolutionObject>(*worldObject));
	
	archive(cereal::make_nvp("isParasiteWorld", objects));

	for (auto object = objects.begin(); object != objects.end(); object++)
		object->release();
}

template <class Archive>
void load(Archive& archive, AbstractSimpleEvolutionWorld& world)
{
	std::vector<std::unique_ptr<AbstractEvolutionObject>> objects;
	for (auto worldObject = world.objects.begin(); worldObject != world.objects.end(); worldObject++)
		objects.push_back(std::unique_ptr<AbstractEvolutionObject>(*worldObject));

	archive(cereal::make_nvp("isParasiteWorld", objects));

	for (auto object = objects.begin(); object != objects.end(); object++)
		object->release();
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(AbstractSimpleEvolutionWorld);

#endif