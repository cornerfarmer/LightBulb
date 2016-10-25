#pragma once

#ifndef _BACKPROPAGATIONPREFERENCEGROUP_H_
#define _BACKPROPAGATIONPREFERENCEGROUP_H_

// Includes
#include "TrainingPlans/Preferences/PreferenceGroup.hpp"
#include "IO/UseParentSerialization.hpp"
#include "Learning/Supervised/GradientCalculation/Backpropagation.hpp"

namespace LightBulb
{
	/**
	* \brief Describes a predefined preference group for backpropagation.
	*/
	class BackpropagationPreferenceGroup : public PreferenceGroup
	{
	protected:
	public:
		/**
		* \brief Creates a backpropagation preference group with standard default values.
		* \param name The name.
		*/
		BackpropagationPreferenceGroup(const std::string& name = "Backpropagation");
		/**
		 * \brief Creates a new backpropagation object with the current preference values.
		 * \return The new backpropagation object.
		 */
		Backpropagation* create() const;
		// Inherited:
		AbstractPreferenceElement* getCopy() const override;
	};
}

USE_PARENT_SERIALIZATION(LightBulb::BackpropagationPreferenceGroup, PreferenceGroup, LightBulb);

#endif
