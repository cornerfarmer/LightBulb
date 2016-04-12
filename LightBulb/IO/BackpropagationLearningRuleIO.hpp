#pragma once

#ifndef _BACKPROPAGATIONLEARNINGRULEIO_H_
#define _BACKPROPAGATIONLEARNINGRULEIO_H_

// Includes
#include "Learning/BackpropagationLearningRule.hpp"
#include "IO/MatrixIO.hpp"
#include "IOStorage.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

template <class Archive>
void serialize(Archive& archive, BackpropagationLearningRule& learningRule)
{
	archive(cereal::base_class<AbstractLearningRule>(&learningRule));
	archive(cereal::make_nvp("deltaVectorOutputLayer", learningRule.deltaVectorOutputLayer));
	archive(cereal::make_nvp("previousDeltaWeights", learningRule.previousDeltaWeights));
}

namespace cereal
{
	template <> struct LoadAndConstruct<BackpropagationLearningRule>
	{
		template <class Archive>
		static void load_and_construct(Archive& ar, cereal::construct<BackpropagationLearningRule>& construct)
		{
			BackpropagationLearningRule* learningRule = static_cast<BackpropagationLearningRule*>(IOStorage<AbstractLearningRule>::pop());
			ar(cereal::base_class<AbstractLearningRule>(learningRule));
			ar(cereal::make_nvp("deltaVectorOutputLayer", learningRule->deltaVectorOutputLayer));
			ar(cereal::make_nvp("previousDeltaWeights", learningRule->previousDeltaWeights));
			IOStorage<AbstractLearningRule>::push(learningRule);
		}
	};
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(BackpropagationLearningRule);

#endif