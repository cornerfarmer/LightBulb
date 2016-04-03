#pragma once

#ifndef _BACKPROPAGATIONLEARNINGRULEIO_H_
#define _BACKPROPAGATIONLEARNINGRULEIO_H_

// Includes
#include "Learning/BackpropagationLearningRule.hpp"
#include "IO/LayeredNetworkIO.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

template <class Archive>
void serialize(Archive& archive, BackpropagationLearningRule& learningRule)
{
	archive(CEREAL_NVP(learningRule.));
}

namespace cereal
{
	template <> struct LoadAndConstruct<BackpropagationLearningRule>
	{
		template <class Archive>
		static void load_and_construct(Archive& ar, cereal::construct<BackpropagationLearningRule>& construct)
		{
			std::unique_ptr<AbstractNetworkTopology> networkTopology;
			ar(networkTopology);
			construct(networkTopology.release());
		}
	};
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(BackpropagationLearningRule);

#endif