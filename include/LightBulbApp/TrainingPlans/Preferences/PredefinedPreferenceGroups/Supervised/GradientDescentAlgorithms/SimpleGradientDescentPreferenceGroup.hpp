#pragma once

#ifndef _SIMPLEGRADIENTDESCENTPREFERENCEGROUP_H_
#define _SIMPLEGRADIENTDESCENTPREFERENCEGROUP_H_

// Includes
#include "LightBulbApp/TrainingPlans/Preferences/PreferenceGroup.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/SimpleGradientDescent.hpp"

namespace LightBulb
{
	/**
	* \brief Describes a predefined preference group for simple gradient descent.
	*/
	class SimpleGradientDescentPreferenceGroup : public PreferenceGroup
	{
	protected:
		/**
		* \brief Initializes the preference group.
		* \param options The options which contain the default values.
		*/
		void initialize(const SimpleGradientDescentOptions& options);
	public:
		/**
		* \brief Creates a simple gradient descent preference group with standard default values.
		* \param name The name.
		*/
		SimpleGradientDescentPreferenceGroup(const std::string& name = "Simple gradient descent");
		/**
		* \brief Creates a simple gradient descent preference group.
		* \param options The options which contain the default values to use.
		* \param name The name.
		*/
		SimpleGradientDescentPreferenceGroup(const SimpleGradientDescentOptions& options, const std::string& name = "Simple gradient descent");
		/**
		* \brief Creates simple gradient descent options with the current preference values.
		* \return The simple gradient descent options.
		*/
		SimpleGradientDescentOptions create() const;
		// Inherited:
		AbstractCloneable* clone() const override;
	};
}

USE_PARENT_SERIALIZATION(LightBulb::SimpleGradientDescentPreferenceGroup, LightBulb::PreferenceGroup, LightBulb);

#endif
