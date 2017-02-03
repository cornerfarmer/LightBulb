#pragma once

#ifndef _ABSTRACTSUPERVISEDLEARNINGRULEIO_H_
#define _ABSTRACTSUPERVISEDLEARNINGRULEIO_H_

// Includes
#include "LightBulb/Learning/Supervised/AbstractSupervisedLearningRule.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes an AbstractSupervisedLearningRule
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param learningRule The AbstractSupervisedLearningRule to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, AbstractSupervisedLearningRule& learningRule);
}

#endif