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
	IOStorage<std::map<std::string, bool>>::push(&learningRule.options->disabledDataSets);
	archive(cereal::make_nvp("learningState", learningRule.learningState));
	archive(cereal::make_nvp("randomGenerator", learningRule.randomGenerator));
}

#endif