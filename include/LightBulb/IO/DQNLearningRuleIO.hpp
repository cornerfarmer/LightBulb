#pragma once

#ifndef _DQNLEARNINGRULEIO_H_
#define _DQNLEARNINGRULEIO_H_

// Includes
#include "LightBulb/Learning/Reinforcement/DQNLearningRule.hpp"
#include "LightBulb/IO/ConstructExisting.hpp"

namespace LightBulb
{
	/**
	* \brief Serializes a Transition.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param transition The Transition to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, Transition& transition);

	/**
	* \brief Serializes a DQNLearningRule.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param learningRule The DQNLearningRule to serialize.
	*/
	template <class Archive>
	extern void serialize(Archive& archive, DQNLearningRule& learningRule);
}


namespace cereal
{
	CONSTRUCT_EXISTING(LightBulb::DQNLearningRule, LightBulb::AbstractLearningRule)
	{
		/**
		* \brief Constructs a existing DQNLearningRule.
		* \tparam Archive The archive type.
		* \param ar The archive which should be used.
		* \param learningRule The existing DQNLearningRule to construct.
		*/
		template <class Archive>
		static void construct(Archive& ar, LightBulb::DQNLearningRule& learningRule);
	};

}


#endif