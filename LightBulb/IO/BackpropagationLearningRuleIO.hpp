#pragma once

#ifndef _BACKPROPAGATIONLEARNINGRULEIO_H_
#define _BACKPROPAGATIONLEARNINGRULEIO_H_

// Includes
#include "Learning/BackpropagationLearningRule.hpp"
#include "IO/AbstractLearningRuleIO.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

template <class Archive>
void serialize(Archive& archive, BackpropagationLearningRule& learningRule)
{
	archive(cereal::base_class<AbstractLearningRule>(&learningRule));
}

namespace cereal
{
	template <> struct LoadAndConstruct<BackpropagationLearningRule>
	{
		template <class Archive>
		static void load_and_construct(Archive& ar, cereal::construct<BackpropagationLearningRule>& construct)
		{

		}
	};
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(BackpropagationLearningRule);

#endif