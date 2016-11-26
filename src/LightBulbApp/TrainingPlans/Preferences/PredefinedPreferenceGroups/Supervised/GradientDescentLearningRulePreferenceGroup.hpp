#pragma once

#ifndef _GRADIENTDESCENTLEARNINGRULEPREFERENCEGROUP_H_
#define _GRADIENTDESCENTLEARNINGRULEPREFERENCEGROUP_H_

// Includes
#include "IO/UseParentSerialization.hpp"
#include "Learning/Supervised/GradientDescentLearningRule.hpp"
#include "AbstractSupervisedLearningRulePreferenceGroup.hpp"

namespace LightBulb
{
	// Forward declarations
	class SimpleGradientDescentOptions;
	class ResilientLearningRateOptions;

	/**
	* \brief Describes a predefined preference group for a gradient descent learning rule.
	*/
	class GradientDescentLearningRulePreferenceGroup : public AbstractSupervisedLearningRulePreferenceGroup
	{
	protected:
		/**
		* \brief Initializes the preference group.
		* \param options The options which contain the default values.
		* \param simpleGradientDescentOptions The options which contain the default values for the simple gradient descent preference group.
		* \param resilientLearningRateOptions The options which contain the default values for the resilient learning rule preference group.
		*/
		void initialize(const GradientDescentLearningRuleOptions& options, const SimpleGradientDescentOptions& simpleGradientDescentOptions, const ResilientLearningRateOptions& resilientLearningRateOptions);
	public:
		/**
		* \brief Creates a gradient descent learning rule preference group with standard default values.
		* \param name The name.
		*/
		GradientDescentLearningRulePreferenceGroup(const std::string& name = "Gradient descent");
		/**
		* \brief Creates a gradient descent learning rule preference group.
		* \param options The options which contain the default values to use.
		* \param name The name.
		*/
		GradientDescentLearningRulePreferenceGroup(const GradientDescentLearningRuleOptions& options, const std::string& name = "Gradient descent");
		/**
		* \brief Creates a gradient descent learning rule preference group.
		* \param options The options which contain the default values to use.
		* \param simpleGradientDescentOptions The options which contain the default values to use for the simple gradient descent group.
		* \param resilientLearningRateOptions The options which contain the default values to use for the resilient learning rate group.
		* \param name The name.
		*/
		GradientDescentLearningRulePreferenceGroup(const GradientDescentLearningRuleOptions& options, const SimpleGradientDescentOptions& simpleGradientDescentOptions, const ResilientLearningRateOptions& resilientLearningRateOptions, const std::string& name = "Gradient descent");
		/**
		* \brief Creates gradient descent learning rule options with the current preference values.
		* \return The gradient descent learning rule options.
		*/
		GradientDescentLearningRuleOptions create() const;
		// Inherited:
		AbstractCloneable* clone() const override;
	};
}

USE_PARENT_SERIALIZATION(LightBulb::GradientDescentLearningRulePreferenceGroup, LightBulb::PreferenceGroup, LightBulb);

#endif
