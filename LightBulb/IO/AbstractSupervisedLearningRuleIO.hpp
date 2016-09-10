#pragma once

#ifndef _ABSTRACTSUPERVISEDLEARNINGRULEIO_H_
#define _ABSTRACTSUPERVISEDLEARNINGRULEIO_H_

// Includes
#include "Learning/Supervised/AbstractSupervisedLearningRule.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	template <class Archive>
	void serialize(Archive& archive, AbstractSupervisedLearningRule& learningRule)
	{
		archive(cereal::base_class<AbstractLearningRule>(&learningRule));
		archive(cereal::make_nvp("totalError", learningRule.totalError));
	}
}

#include "UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::AbstractSupervisedLearningRule);

#endif