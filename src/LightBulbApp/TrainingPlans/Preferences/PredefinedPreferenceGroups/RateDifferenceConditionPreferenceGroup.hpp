#pragma once

#ifndef _RATEDIFFERENCECONDITIONPREFERENCEGROUP_H_
#define _RATEDIFFERENCECONDITIONPREFERENCEGROUP_H_

// Includes
#include "TrainingPlans/Preferences/PreferenceGroup.hpp"
#include "IO/UseParentSerialization.hpp"
#include "Learning/Evolution/RateDifferenceCondition.hpp"

namespace LightBulb
{
	/**
	* \brief Describes a predefined preference group for a rate difference condition.
	*/
	class RateDifferenceConditionPreferenceGroup : public PreferenceGroup
	{
	protected:
	public:
		/**
		* \brief Creates a rate difference condition group with standard default values.
		* \param name The name.
		*/
		RateDifferenceConditionPreferenceGroup(const std::string& name = "Rate difference condition");
		/**
		 * \brief Creates a new rate difference condition object with the current preference values.
		 * \return The new rate difference condition.
		 */
		RateDifferenceCondition* create() const;
		// Inherited:
		AbstractCloneable* clone() const override;
	};
}

USE_PARENT_SERIALIZATION(LightBulb::RateDifferenceConditionPreferenceGroup, LightBulb::PreferenceGroup, LightBulb);

#endif
