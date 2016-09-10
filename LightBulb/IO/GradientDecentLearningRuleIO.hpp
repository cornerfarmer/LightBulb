#pragma once

#ifndef _GRADIENTDECENTLEARNINGRULEIO_H_
#define _GRADIENTDECENTLEARNINGRULEIO_H_

// Includes
#include "Learning/Supervised/GradientDecentLearningRule.hpp"
#include "IO/MatrixIO.hpp"
#include "ConstructExisting.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	template <class Archive>
	void serialize(Archive& archive, GradientDecentLearningRule& learningRule)
	{
		archive(cereal::base_class<AbstractSupervisedLearningRule>(&learningRule));
		archive(cereal::make_nvp("gradientDecentAlgorithm", learningRule.gradientDecentAlgorithm));
		archive(cereal::make_nvp("gradientCalculation", learningRule.gradientCalculation));
	}
}


namespace cereal
{
	CONSTRUCT_EXISTING(LightBulb::GradientDecentLearningRule, LightBulb::AbstractLearningRule)
	{
		template <class Archive>
		static void construct(Archive& ar, LightBulb::GradientDecentLearningRule& learningRule)
		{
			using namespace LightBulb;
			ar(cereal::base_class<AbstractSupervisedLearningRule>(&learningRule));

			IOStorage<AbstractGradientDecentAlgorithm>::push(learningRule.gradientDecentAlgorithm.release());
			ar(cereal::make_nvp("gradientDecentAlgorithm", learningRule.gradientDecentAlgorithm));
			learningRule.gradientDecentAlgorithm.reset(IOStorage<AbstractGradientDecentAlgorithm>::pop());

			IOStorage<AbstractGradientCalculation>::push(learningRule.gradientCalculation.release());
			ar(cereal::make_nvp("gradientCalculation", learningRule.gradientCalculation));
			learningRule.gradientCalculation.reset(IOStorage<AbstractGradientCalculation>::pop());
		}
	};
}


#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::GradientDecentLearningRule);

#endif