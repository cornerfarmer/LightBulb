#pragma once

#ifndef _ABSTRACTREINFORCEMENTLEARNINGRULEIO_H_
#define _ABSTRACTREINFORCEMENTLEARNINGRULEIO_H_

// Includes
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementLearningRule.hpp"
// Libraray includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes an AbstractReinforcementLearningRule
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param learningRule The AbstractReinforcementLearningRule to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, AbstractReinforcementLearningRule& learningRule)
	{
		archive(cereal::base_class<AbstractLearningRule>(&learningRule));
		learningRule.randomGeneratorHasChanged();
	}
}

#endif