#pragma once

#ifndef _ABSTRACTEVOLUTIONLEARNINGRULEIO_H_
#define _ABSTRACTEVOLUTIONLEARNINGRULEIO_H_

// Includes
#include "LightBulb/Learning/Evolution/AbstractEvolutionLearningRule.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes an AbstractEvolutionLearningRule
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param evolutionLearning The AbstractEvolutionLearningRule to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, AbstractEvolutionLearningRule& evolutionLearning);
}

#endif