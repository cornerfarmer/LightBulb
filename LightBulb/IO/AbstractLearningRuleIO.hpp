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
	archive(learningRule.iteration);
	archive(learningRule.totalError);
	archive(learningRule.tryCounter);
}

#endif