#pragma once

#ifndef _FUNCTIONSIMULATORIO_H_
#define _FUNCTIONSIMULATORIO_H_

// Includes
#include "Examples/FunctionSimulator.hpp"
#include "IO/ConstructExisting.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

template <class Archive>
void save(Archive& archive, FunctionSimulator const& world)
{
	archive(cereal::base_class<AbstractSimpleEvolutionWorld>(&world));
}

template <class Archive>
void load(Archive& archive, FunctionSimulator& world)
{
	archive(cereal::base_class<AbstractSimpleEvolutionWorld>(&world));
}

namespace cereal
{
	CONSTRUCT_EXISTING(FunctionSimulator, AbstractEvolutionWorld)
	{
		template <class Archive>
		static void construct(Archive& ar, FunctionSimulator& world)
		{
			ar(cereal::base_class<AbstractSimpleEvolutionWorld>(&world));
		}
	};
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(FunctionSimulator);

#endif