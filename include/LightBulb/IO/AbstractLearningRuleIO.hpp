#pragma once

#ifndef _ABSTRACTLEARNINGRULEIO_H_
#define _ABSTRACTLEARNINGRULEIO_H_

// Includes
#include "LightBulb/Learning/AbstractLearningRule.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes an AbstractLearningRule
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param learningRule The AbstractLearningRule to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, AbstractLearningRule& learningRule);
}

#endif