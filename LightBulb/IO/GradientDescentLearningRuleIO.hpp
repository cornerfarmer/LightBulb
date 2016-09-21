#pragma once

#ifndef _GRADIENTDESCENTLEARNINGRULEIO_H_
#define _GRADIENTDESCENTLEARNINGRULEIO_H_

// Includes
#include "Learning/Supervised/GradientDescentLearningRule.hpp"
#include "IO/MatrixIO.hpp"
#include "ConstructExisting.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	template <class Archive>
	void serialize(Archive& archive, GradientDescentLearningRule& learningRule)
	{
		archive(cereal::base_class<AbstractSupervisedLearningRule>(&learningRule));
		archive(cereal::make_nvp("gradientDescentAlgorithm", learningRule.gradientDescentAlgorithm));
		archive(cereal::make_nvp("gradientCalculation", learningRule.gradientCalculation));
	}
}


namespace cereal
{
	CONSTRUCT_EXISTING(LightBulb::GradientDescentLearningRule, LightBulb::AbstractLearningRule)
	{
		template <class Archive>
		static void construct(Archive& ar, LightBulb::GradientDescentLearningRule& learningRule)
		{
			using namespace LightBulb;
			ar(cereal::base_class<AbstractSupervisedLearningRule>(&learningRule));

			IOStorage<AbstractGradientDescentAlgorithm>::push(learningRule.gradientDescentAlgorithm.release());
			ar(cereal::make_nvp("gradientDescentAlgorithm", learningRule.gradientDescentAlgorithm));
			learningRule.gradientDescentAlgorithm.reset(IOStorage<AbstractGradientDescentAlgorithm>::pop());

			IOStorage<AbstractGradientCalculation>::push(learningRule.gradientCalculation.release());
			ar(cereal::make_nvp("gradientCalculation", learningRule.gradientCalculation));
			learningRule.gradientCalculation.reset(IOStorage<AbstractGradientCalculation>::pop());
		}
	};
}


#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::GradientDescentLearningRule);

#endif