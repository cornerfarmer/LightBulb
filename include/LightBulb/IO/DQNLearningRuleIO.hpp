#pragma once

#ifndef _DQNLEARNINGRULEIO_H_
#define _DQNLEARNINGRULEIO_H_

// Includes
#include "LightBulb/Learning/Reinforcement/DQNLearningRule.hpp"
#include "LightBulb/IO/EigenMatrixIO.hpp"
#include "LightBulb/IO/ConstructExisting.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a Transition.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param transition The Transition to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, Transition& transition)
	{
		archive(cereal::make_nvp("state", transition.state));
		archive(cereal::make_nvp("nextState", transition.nextState));
		archive(cereal::make_nvp("action", transition.action));
		archive(cereal::make_nvp("reward", transition.reward));
	}

	/**
	* \brief Serializes a DQNLearningRule.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param learningRule The DQNLearningRule to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, DQNLearningRule& learningRule)
	{
		archive(cereal::base_class<AbstractReinforcementLearningRule>(&learningRule));
		archive(cereal::make_nvp("nextTransitionIndex", learningRule.nextTransitionIndex));
		archive(cereal::make_nvp("waitUntilLearningStarts", learningRule.waitUntilLearningStarts));
		archive(cereal::make_nvp("transitions", learningRule.transitions));
		archive(cereal::make_nvp("currentTotalError", learningRule.currentTotalError));
		archive(cereal::make_nvp("currentTotalReward", learningRule.currentTotalReward));
		archive(cereal::make_nvp("qAvgSum", learningRule.qAvgSum));
		archive(cereal::make_nvp("gradientDescent", learningRule.gradientDescent));
	}
}


namespace cereal
{
	CONSTRUCT_EXISTING(LightBulb::DQNLearningRule, LightBulb::AbstractLearningRule)
	{
		/**
		* \brief Constructs a existing DQNLearningRule.
		* \tparam Archive The archive type.
		* \param ar The archive which should be used.
		* \param learningRule The existing DQNLearningRule to construct.
		*/
		template <class Archive>
		static void construct(Archive& ar, LightBulb::DQNLearningRule& learningRule)
		{
			using namespace LightBulb;
			ar(base_class<AbstractReinforcementLearningRule>(&learningRule));
			ar(make_nvp("nextTransitionIndex", learningRule.nextTransitionIndex));
			ar(make_nvp("waitUntilLearningStarts", learningRule.waitUntilLearningStarts));
			ar(make_nvp("transitions", learningRule.transitions));
			ar(make_nvp("currentTotalError", learningRule.currentTotalError));
			ar(make_nvp("currentTotalReward", learningRule.currentTotalReward));
			ar(make_nvp("qAvgSum", learningRule.qAvgSum));

			IOStorage<AbstractLearningRule>::push(learningRule.gradientDescent.release());
			ar(make_nvp("gradientDescent", learningRule.gradientDescent));
			learningRule.gradientDescent.reset(static_cast<GradientDescentLearningRule*>(IOStorage<AbstractLearningRule>::pop()));
		}
	};
}


#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::DQNLearningRule);

#endif