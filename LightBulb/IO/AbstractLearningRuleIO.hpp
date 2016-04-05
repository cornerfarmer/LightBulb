#pragma once

#ifndef _ABSTRACTLEARNINGRULEIO_H_
#define _ABSTRACTLEARNINGRULEIO_H_

// Includes
#include "Learning/AbstractLearningRule.hpp"
// Libraray includes
#include <cereal/cereal.hpp>

template <class Archive>
void serialize(Archive& archive, AbstractLearningRule& learningRule)
{
	archive(cereal::make_nvp("iteration", learningRule.iteration));
	archive(cereal::make_nvp("totalError", learningRule.totalError));
	archive(cereal::make_nvp("tryCounter", learningRule.tryCounter));
}

#endif