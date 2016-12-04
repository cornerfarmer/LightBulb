#pragma once

#ifndef _RMSPROPLEARNINGRATEPREFERENCEGROUP_H_
#define _RMSPROPLEARNINGRATEPREFERENCEGROUP_H_

// Includes
#include "LightBulbApp/TrainingPlans/Preferences/PreferenceGroup.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/RMSPropLearningRate.hpp"

namespace LightBulb
{
	/**
	* \brief Describes a predefined preference group for the RMSProp learning rate.
	*/
	class RMSPropLearningRatePreferenceGroup : public PreferenceGroup
	{
	protected:
		/**
		* \brief Initializes the preference group.
		* \param options The options which contain the default values.
		*/
		void initialize(const RMSPropLearningRateOptions& options);
	public:
		/**
		* \brief Creates a RMSProp learning rate preference group with standard default values.
		* \param name The name.
		*/
		RMSPropLearningRatePreferenceGroup(const std::string& name = "RMSProp");
		/**
		* \brief Creates a RMSProp learning rate preference group.
		* \param options The options which contain the default values to use.
		* \param name The name.
		*/
		RMSPropLearningRatePreferenceGroup(const RMSPropLearningRateOptions& options, const std::string& name = "RMSProp");
		/**
		* \brief Creates RMSProp learning rate options with the current preference values.
		* \return The RMSProp learning rate options.
		*/
		RMSPropLearningRateOptions create() const;
		// Inherited:
		AbstractCloneable* clone() const override;
	};
}

USE_PARENT_SERIALIZATION(LightBulb::RMSPropLearningRatePreferenceGroup, LightBulb::PreferenceGroup, LightBulb);

#endif
