#pragma once

#ifndef _SIMPLEGRADIENTDESCENTPREFERENCEGROUP_H_
#define _SIMPLEGRADIENTDESCENTPREFERENCEGROUP_H_

// Includes
#include "PreferenceGroup.hpp"
#include "IO/UseParentSerialization.hpp"
#include "Learning/Supervised/GradientDescentAlgorithms/SimpleGradientDescent.hpp"

namespace LightBulb
{

	// Forward declarations

	class SimpleGradientDescentPreferenceGroup : public PreferenceGroup
	{
	protected:
	public:
		SimpleGradientDescentPreferenceGroup(std::string name = "Simple gradient descent");

		SimpleGradientDescentOptions create();

		AbstractPreferenceElement* getCopy();
	};
}

USE_PARENT_SERIALIZATION(LightBulb::SimpleGradientDescentPreferenceGroup, PreferenceGroup, LightBulb);

#endif
