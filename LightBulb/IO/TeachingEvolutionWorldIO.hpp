#pragma once

#ifndef _TEACHINGEVOLUTIONWORLDIO_H_
#define _TEACHINGEVOLUTIONWORLDIO_H_

// Includes
#include <Learning/Evolution/TeachingEvolutionWorld.hpp>
#include "IO/ConstructExisting.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

template <class Archive>
void save(Archive& archive, TeachingEvolutionWorld const& world)
{
	archive(cereal::base_class<AbstractSimpleEvolutionWorld>(&world));
}

template <class Archive>
void load(Archive& archive, TeachingEvolutionWorld& world)
{
	archive(cereal::base_class<AbstractSimpleEvolutionWorld>(&world));
}

namespace cereal
{
	CONSTRUCT_EXISTING(TeachingEvolutionWorld, AbstractEvolutionWorld)
	{
		template <class Archive>
		static void construct(Archive& ar, TeachingEvolutionWorld& world)
		{
			ar(cereal::base_class<AbstractSimpleEvolutionWorld>(&world));
		}
	};
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(TeachingEvolutionWorld);

#endif