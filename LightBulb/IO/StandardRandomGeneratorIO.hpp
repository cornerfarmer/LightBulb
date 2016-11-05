#pragma once

#ifndef _STANDARDRANDOMGENERATORIO_H_
#define _STANDARDRANDOMGENERATORIO_H_

// Includes
#include "Random/StandardRandomGenerator.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/vector.hpp>

namespace LightBulb
{
	/**
	* \brief Saves a StandardRandomGenerator.
	* \tparam Archive The archive type.
	* \tparam T The random engine.
	* \param archive The archive which should be used.
	* \param standardRandomGenerator The SimpleGradientDescent to save.
	*/
	template <class Archive, class T>
	void save(Archive& archive, StandardRandomGenerator<T> const& standardRandomGenerator)
	{
		archive(cereal::base_class<AbstractRandomGenerator>(&standardRandomGenerator));

		std::ostringstream state;
		state << standardRandomGenerator.generator;
		std::string stateStr = state.str();
		archive(cereal::make_nvp("state", stateStr));
	}

	/**
	* \brief Loads a StandardRandomGenerator.
	* \tparam Archive The archive type.
	* \tparam T The random engine.
	* \param archive The archive which should be used.
	* \param standardRandomGenerator The SimpleGradientDescent to load.
	*/
	template <class Archive, class T>
	void load(Archive& archive, StandardRandomGenerator<T>& standardRandomGenerator)
	{
		archive(cereal::base_class<AbstractRandomGenerator>(&standardRandomGenerator));

		std::string stateStr;
		archive(cereal::make_nvp("state", stateStr));
		std::istringstream state(stateStr);
		state >> standardRandomGenerator.generator;
	}
}

#include "IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::StandardRandomGenerator<std::default_random_engine>)

#endif