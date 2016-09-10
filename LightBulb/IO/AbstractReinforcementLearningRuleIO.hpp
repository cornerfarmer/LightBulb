#pragma once

#ifndef _ABSTRACTREINFORCEMENTLEARNINGRULEIO_H_
#define _ABSTRACTREINFORCEMENTLEARNINGRULEIO_H_

// Includes
#include "Learning/Reinforcement/AbstractReinforcementLearningRule.hpp"
// Libraray includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	template <class Archive>
	void serialize(Archive& archive, AbstractReinforcementLearningRule& learningRule)
	{
		archive(cereal::base_class<AbstractLearningRule>(&learningRule));
		learningRule.randomGeneretorHasChanged();
	}
}

#endif