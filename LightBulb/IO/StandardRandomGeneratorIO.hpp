#pragma once

#ifndef _STANDARDRANDOMGENERATORIO_H_
#define _STANDARDRANDOMGENERATORIO_H_

// Includes
#include "Random/StandardRandomGenerator.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/vector.hpp>

template <class Archive, class T>
void save(Archive& archive, StandardRandomGenerator<T> const& standardRandomGenerator)
{
	archive(cereal::base_class<AbstractRandomGenerator>(&standardRandomGenerator));

	std::ostringstream state;
	state << standardRandomGenerator.generator;
	std::string stateStr = state.str();
	archive(cereal::make_nvp("state", stateStr));

	archive(cereal::make_nvp("seed", standardRandomGenerator.seed));
}

template <class Archive, class T>
void load(Archive& archive, StandardRandomGenerator<T>& standardRandomGenerator)
{
	archive(cereal::base_class<AbstractRandomGenerator>(&standardRandomGenerator));

	std::string stateStr;
	archive(cereal::make_nvp("state", stateStr));
	std::istringstream state(stateStr);
	state >> standardRandomGenerator.generator;

	archive(cereal::make_nvp("seed", standardRandomGenerator.seed));
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(StandardRandomGenerator<std::default_random_engine>)

#endif