#pragma once

#ifndef _RESILIENTLEARNINGRATEPREFERENCEGROUP_H_
#define _RESILIENTLEARNINGRATEPREFERENCEGROUP_H_

// Includes
#include "TrainingPlans/Preferences/PreferenceGroup.hpp"
#include "IO/UseParentSerialization.hpp"
#include "Learning/Supervised/GradientDescentAlgorithms/ResilientLearningRate.hpp"

namespace LightBulb
{
	/**
	* \brief Describes a predefined preference group for the resilient learning rate.
	*/
	class ResilientLearningRatePreferenceGroup : public PreferenceGroup
	{
	protected:
		/**
		* \brief Initializes the preference group.
		* \param options The options which contain the default values.
		*/
		void initialize(const ResilientLearningRateOptions& options);
	public:
		/**
		* \brief Creates a resilient learning rate preference group with standard default values.
		* \param name The name.
		*/
		ResilientLearningRatePreferenceGroup(const std::string& name = "Resilient learning rate");
		/**
		* \brief Creates a resilient learning rate preference group.
		* \param options The options which contain the default values to use.
		* \param name The name.
		*/
		ResilientLearningRatePreferenceGroup(const ResilientLearningRateOptions& options, const std::string& name = "Resilient learning rate");
		/**
		* \brief Creates resilient learning rate options with the current preference values.
		* \return The resilient learning rate options.
		*/
		ResilientLearningRateOptions create() const;
		// Inherited:
		AbstractCloneable* clone() const override;
	};
}

USE_PARENT_SERIALIZATION(LightBulb::ResilientLearningRatePreferenceGroup, LightBulb::PreferenceGroup, LightBulb);

#endif
