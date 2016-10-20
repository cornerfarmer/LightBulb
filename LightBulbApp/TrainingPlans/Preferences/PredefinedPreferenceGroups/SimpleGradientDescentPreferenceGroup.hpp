#pragma once

#ifndef _SIMPLEGRADIENTDESCENTPREFERENCEGROUP_H_
#define _SIMPLEGRADIENTDESCENTPREFERENCEGROUP_H_

// Includes
#include "TrainingPlans/Preferences/PreferenceGroup.hpp"
#include "IO/UseParentSerialization.hpp"
#include "Learning/Supervised/GradientDescentAlgorithms/SimpleGradientDescent.hpp"

namespace LightBulb
{

	// Forward declarations

	class SimpleGradientDescentPreferenceGroup : public PreferenceGroup
	{
	protected:
		void initialize(const SimpleGradientDescentOptions& options);
	public:
		SimpleGradientDescentPreferenceGroup(const std::string& name = "Simple gradient descent");
		SimpleGradientDescentPreferenceGroup(const SimpleGradientDescentOptions& options, const std::string& name = "Simple gradient descent");

		SimpleGradientDescentOptions create() const;

		AbstractPreferenceElement* getCopy() const override;
	};
}

USE_PARENT_SERIALIZATION(LightBulb::SimpleGradientDescentPreferenceGroup, PreferenceGroup, LightBulb);

#endif
