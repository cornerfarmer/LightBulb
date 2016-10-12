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
	/**
	* \brief Serializes a RBFInterpolationLearningRule.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param learningRule The RBFInterpolationLearningRule to serialize.
	*/
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
		/**
		* \brief Constructs a RBFInterpolationLearningRule.
		* \tparam Archive The archive type.
		* \param ar The archive which should be used.
		* \param construct The RBFInterpolationLearningRule construct object.
		*/
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