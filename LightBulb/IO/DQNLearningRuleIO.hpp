#pragma once

#ifndef _DQNLEARNINGRULEIO_H_
#define _DQNLEARNINGRULEIO_H_

// Includes
#include "Learning/Reinforcement/DQNLearningRule.hpp"
#include "IO/MatrixIO.hpp"
#include "ConstructExisting.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>


template <class Archive>
void serialize(Archive& archive, Transition& transition)
{
	archive(cereal::make_nvp("state", transition.state));
	archive(cereal::make_nvp("nextState", transition.nextState));
	archive(cereal::make_nvp("action", transition.action));
	archive(cereal::make_nvp("reward", transition.reward));
}


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
	archive(cereal::make_nvp("gradientDecent", learningRule.gradientDecent));
}


namespace cereal
{
	CONSTRUCT_EXISTING(DQNLearningRule, AbstractLearningRule)
	{
		template <class Archive>
		static void construct(Archive& ar, DQNLearningRule& learningRule)
		{
			ar(cereal::base_class<AbstractReinforcementLearningRule>(&learningRule));
			ar(cereal::make_nvp("nextTransitionIndex", learningRule.nextTransitionIndex));
			ar(cereal::make_nvp("waitUntilLearningStarts", learningRule.waitUntilLearningStarts));
			ar(cereal::make_nvp("transitions", learningRule.transitions));
			ar(cereal::make_nvp("currentTotalError", learningRule.currentTotalError));
			ar(cereal::make_nvp("currentTotalReward", learningRule.currentTotalReward));
			ar(cereal::make_nvp("qAvgSum", learningRule.qAvgSum));

			IOStorage<AbstractLearningRule>::push(learningRule.gradientDecent.release());
			ar(cereal::make_nvp("gradientDecent", learningRule.gradientDecent));
			learningRule.gradientDecent.reset(static_cast<GradientDecentLearningRule*>(IOStorage<AbstractLearningRule>::pop()));
		}
	};
}


#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(DQNLearningRule);

#endif