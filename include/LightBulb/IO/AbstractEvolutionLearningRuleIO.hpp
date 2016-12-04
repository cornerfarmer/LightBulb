#pragma once

#ifndef _ABSTRACTEVOLUTIONLEARNINGRULEIO_H_
#define _ABSTRACTEVOLUTIONLEARNINGRULEIO_H_

// Includes
#include "LightBulb/Learning/Evolution/AbstractEvolutionLearningRule.hpp"
// Libraray includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes an AbstractEvolutionLearningRule
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param evolutionLearning The AbstractEvolutionLearningRule to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, AbstractEvolutionLearningRule& evolutionLearning)
	{
		archive(cereal::base_class<AbstractLearningRule>(&evolutionLearning));
		archive(cereal::make_nvp("zigguratGenerator", evolutionLearning.zigguratGenerator));
	}
}

#endif