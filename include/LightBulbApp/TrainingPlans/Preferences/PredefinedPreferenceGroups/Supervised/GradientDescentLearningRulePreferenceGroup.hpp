#pragma once

#ifndef _GRADIENTDESCENTLEARNINGRULEPREFERENCEGROUP_H_
#define _GRADIENTDESCENTLEARNINGRULEPREFERENCEGROUP_H_

// Includes
#include "LightBulb/IO/UseParentSerialization.hpp"
#include "LightBulb/Learning/Supervised/GradientDescentLearningRule.hpp"
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
		* \param skipGradientDescentAlgorithm True, if the preference group should not manage the gradient descent algorithm.
		* \param options The options which contain the default values.
		* \param simpleGradientDescentOptions The options which contain the default values for the simple gradient descent preference group.
		* \param resilientLearningRateOptions The options which contain the default values for the resilient learning rule preference group.
		*/
		void initialize(bool skipGradientDescentAlgorithm, const GradientDescentLearningRuleOptions& options, const SimpleGradientDescentOptions& simpleGradientDescentOptions, const ResilientLearningRateOptions& resilientLearningRateOptions);
	public:
		/**
		* \brief Creates a gradient descent learning rule preference group with standard default values.
		* \param skipGradientDescentAlgorithm True, if the preference group should not manage the gradient descent algorithm.
		* \param name The name.
		*/
		GradientDescentLearningRulePreferenceGroup(bool skipGradientDescentAlgorithm = false, const std::string& name = "Gradient descent");
		/**
		* \brief Creates a gradient descent learning rule preference group.
		* \param options The options which contain the default values to use.
		* \param skipGradientDescentAlgorithm True, if the preference group should not manage the gradient descent algorithm.
		* \param name The name.
		*/
		GradientDescentLearningRulePreferenceGroup(const GradientDescentLearningRuleOptions& options, bool skipGradientDescentAlgorithm = false, const std::string& name = "Gradient descent");
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
