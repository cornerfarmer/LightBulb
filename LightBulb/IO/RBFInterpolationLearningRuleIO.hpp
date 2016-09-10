#pragma once

#ifndef _RBFINTERPOLATIONLEARNINGRULEIO_H_
#define _RBFINTERPOLATIONLEARNINGRULEIO_H_

// Includes
#include "Learning/Supervised/RBFInterpolationLearningRule.hpp"
#include "IOStorage.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	template <class Archive>
	void serialize(Archive& archive, RBFInterpolationLearningRule& learningRule)
	{
		archive(cereal::base_class<AbstractSupervisedLearningRule>(&learningRule));
	}
}

namespace cereal
{
	template <> struct LoadAndConstruct<LightBulb::RBFInterpolationLearningRule>
	{
		template <class Archive>
		static void load_and_construct(Archive& ar, cereal::construct<LightBulb::RBFInterpolationLearningRule>& construct)
		{
			using namespace LightBulb;
			RBFInterpolationLearningRule* learningRule = static_cast<RBFInterpolationLearningRule*>(IOStorage<AbstractLearningRule>::pop());
			ar(cereal::base_class<AbstractSupervisedLearningRule>(learningRule));
			IOStorage<AbstractLearningRule>::push(learningRule);
		}
	};
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::RBFInterpolationLearningRule);

#endif