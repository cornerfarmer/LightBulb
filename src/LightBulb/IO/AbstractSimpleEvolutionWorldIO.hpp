#pragma once

#ifndef _ABSTRACTSIMPLEEVOLUTIONWORLDIO_H_
#define _ABSTRACTSIMPLEEVOLUTIONWORLDIO_H_

// Includes
#include "Learning/Evolution/AbstractSimpleEvolutionWorld.hpp"
#include "Learning/Evolution/AbstractIndividual.hpp"
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
		std::vector<std::unique_ptr<AbstractIndividual>> individuals;
		for (auto individual = world.individuals.begin(); individual != world.individuals.end(); individual++)
			individuals.push_back(std::unique_ptr<AbstractIndividual>(*individual));

		archive(cereal::make_nvp("individuals", individuals));

		for (auto individual = individuals.begin(); individual != individuals.end(); individual++)
			individual->release();
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
		std::vector<std::unique_ptr<AbstractIndividual>> individuals;
		IOStorage<AbstractEvolutionWorld>::push(&world);
		archive(cereal::make_nvp("individuals", individuals));
		IOStorage<AbstractEvolutionWorld>::clear();

		for (auto individual = individuals.begin(); individual != individuals.end(); individual++)
		{
			world.individuals.push_back(individual->release());
		}
	}
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::AbstractSimpleEvolutionWorld);

#endif