#pragma once

#ifndef _ABSTRACTCOEVOLUTIONWORLDIO_H_
#define _ABSTRACTCOEVOLUTIONWORLDIO_H_

// Includes
#include "Learning/Evolution/AbstractCoevolutionWorld.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	template <class Archive>
	void save(Archive& archive, AbstractCoevolutionWorld const& world)
	{
		archive(cereal::base_class<AbstractSimpleEvolutionWorld>(&world));
		archive(cereal::make_nvp("hallOfFameToAddAlgorithm", world.hallOfFameToAddAlgorithm));
		archive(cereal::make_nvp("hallOfFameToChallengeAlgorithm", world.hallOfFameToChallengeAlgorithm));

		std::vector<double> fitnessValues(world.objects.size());
		for (int i = 0; i < world.objects.size(); i++)
		{
			if (world.fitnessValues->count(world.objects[i]))
				fitnessValues[i] = world.fitnessValues->at(world.objects[i]);
		}
		archive(cereal::make_nvp("fitnessValues", fitnessValues));

		archive(cereal::make_nvp("comparisons", world.comparisons));
	}


	template <class Archive>
	void load(Archive& archive, AbstractCoevolutionWorld& world)
	{
		archive(cereal::base_class<AbstractSimpleEvolutionWorld>(&world));

		std::shared_ptr<AbstractHallOfFameAlgorithm> tmp(world.hallOfFameToAddAlgorithm);

		IOStorage<AbstractHallOfFameAlgorithm>::push(world.hallOfFameToAddAlgorithm.get());
		archive(cereal::make_nvp("hallOfFameToAddAlgorithm", world.hallOfFameToAddAlgorithm));
		world.hallOfFameToAddAlgorithm = tmp;

		tmp = world.hallOfFameToChallengeAlgorithm;

		IOStorage<AbstractHallOfFameAlgorithm>::push(world.hallOfFameToChallengeAlgorithm.get());
		archive(cereal::make_nvp("hallOfFameToChallengeAlgorithm", world.hallOfFameToChallengeAlgorithm));
		world.hallOfFameToChallengeAlgorithm = tmp;
		IOStorage<AbstractHallOfFameAlgorithm>::clear();

		tmp = NULL;

		std::vector<double> fitnessValues;
		archive(cereal::make_nvp("fitnessValues", fitnessValues));
		world.fitnessValues.reset(new std::map<AbstractEvolutionObject*, double>());
		for (int i = 0; i < world.objects.size(); i++)
			(*world.fitnessValues)[world.objects[i]] = fitnessValues[i];

		archive(cereal::make_nvp("comparisons", world.comparisons));
	}

}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::AbstractCoevolutionWorld);

#endif