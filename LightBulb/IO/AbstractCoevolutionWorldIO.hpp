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
void serialize(Archive& archive, AbstractCoevolutionWorld& world)
{
	archive(cereal::base_class<AbstractSimpleEvolutionWorld>(&world));
	archive(cereal::make_nvp("fitnessFunction", world.fitnessFunction));
	archive(cereal::make_nvp("hallOfFameToAddAlgorithm", world.hallOfFameToAddAlgorithm));
	archive(cereal::make_nvp("hallOfFameToChallengeAlgorithm", world.hallOfFameToChallengeAlgorithm));
	archive(cereal::make_nvp("combiningStrategy", world.combiningStrategy));
	archive(cereal::make_nvp("fitnessValues", world.fitnessValues));
	archive(cereal::make_nvp("isParasiteWorld", world.isParasiteWorld));
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(AbstractCoevolutionWorld);

#endif