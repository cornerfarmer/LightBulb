#pragma once

#ifndef _BACKPROPAGATIONPREFERENCEGROUP_H_
#define _BACKPROPAGATIONPREFERENCEGROUP_H_

// Includes
#include "PreferenceGroup.hpp"
#include "IO/UseParentSerialization.hpp"
#include "Learning/Supervised/GradientCalculation/Backpropagation.hpp"

namespace LightBulb
{

	// Forward declarations

	class BackpropagationPreferenceGroup : public PreferenceGroup
	{
	protected:
	public:
		BackpropagationPreferenceGroup(const std::string& name = "Backpropagation");

		Backpropagation* create() const;
		AbstractPreferenceElement* getCopy() const override;
	};
}

USE_PARENT_SERIALIZATION(LightBulb::BackpropagationPreferenceGroup, PreferenceGroup, LightBulb);

#endif
