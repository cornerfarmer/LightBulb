#pragma once

#ifndef _ABSTRACTCOEVOLUTIONWORLDIO_H_
#define _ABSTRACTCOEVOLUTIONWORLDIO_H_

// Includes
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

template <class Archive>
void save(Archive& archive, AbstractCoevolutionWorld const& world)
{
	archive(cereal::base_class<AbstractSimpleEvolutionWorld>(&world));
	archive(cereal::make_nvp("fitnessFunction", world.fitnessFunction));
	archive(cereal::make_nvp("hallOfFameToAddAlgorithm", world.hallOfFameToAddAlgorithm));
	archive(cereal::make_nvp("hallOfFameToChallengeAlgorithm", world.hallOfFameToChallengeAlgorithm));
	archive(cereal::make_nvp("combiningStrategy", world.combiningStrategy));

	std::vector<double> fitnessValues(world.objects.size());
	for (int i = 0; i < world.objects.size(); i++)
	{
		if (world.fitnessValues->count(world.objects[i]))
			fitnessValues[i] = world.fitnessValues->at(world.objects[i]);
	}		
	archive(cereal::make_nvp("fitnessValues", fitnessValues));

	archive(cereal::make_nvp("isParasiteWorld", world.parasiteWorld));
}


template <class Archive>
void load(Archive& archive, AbstractCoevolutionWorld& world)
{
	archive(cereal::base_class<AbstractSimpleEvolutionWorld>(&world));
	archive(cereal::make_nvp("fitnessFunction", world.fitnessFunction));
	IOStorage<AbstractEvolutionWorld>::push(&world);
	archive(cereal::make_nvp("hallOfFameToAddAlgorithm", world.hallOfFameToAddAlgorithm));
	archive(cereal::make_nvp("hallOfFameToChallengeAlgorithm", world.hallOfFameToChallengeAlgorithm));
	IOStorage<AbstractEvolutionWorld>::clear();
	archive(cereal::make_nvp("combiningStrategy", world.combiningStrategy));

	std::vector<double> fitnessValues;
	archive(cereal::make_nvp("fitnessValues", fitnessValues));
	for (int i = 0; i < world.objects.size(); i++)
		(*world.fitnessValues)[world.objects[i]] = fitnessValues[i];

	archive(cereal::make_nvp("isParasiteWorld", world.parasiteWorld));
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(AbstractCoevolutionWorld);

#endif