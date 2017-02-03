#pragma once

#ifndef _FEEDFORWARDNETWORKTOPOLOGYPREFERENCEGROUP_H_
#define _FEEDFORWARDNETWORKTOPOLOGYPREFERENCEGROUP_H_

// Includes
#include "LightBulbApp/TrainingPlans/Preferences/PreferenceGroup.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"

namespace LightBulb
{
	class AbstractActivationFunction;
	class AbstractInputFunction;
	class ChoicePreference;
	struct FeedForwardNetworkTopologyOptions;
	/**
	* \brief Describes a predefined preference group for a feed forward network topology.
	*/
	class FeedForwardNetworkTopologyPreferenceGroup : public PreferenceGroup
	{
	protected:
		/**
		* \brief Initializes the preference group.
		* \param options The options which contain the default values.
		*/
		void initialize(const FeedForwardNetworkTopologyOptions& options);
		AbstractActivationFunction* getActivationFunctionFromChoice(std::string preferenceName) const;
		AbstractInputFunction* getInputFunctionFromChoice(std::string preferenceName) const;
		void fillInputFunctionChoices(ChoicePreference& preference) const;
		void fillActivationFunctionChoices(ChoicePreference& preference) const;
		std::string getActivationFunctionName(const AbstractActivationFunction* activationFunction) const;
		std::string getInputFunctionName(const AbstractInputFunction* inputFunction) const;
	public:
		/**
		* \brief Creates a feed forward network topology preference group with standard default values.
		* \param name The name.
		*/
		FeedForwardNetworkTopologyPreferenceGroup(const std::string& name = "RMSProp");
		/**
		* \brief Creates a feed forward network topology preference group.
		* \param options The options which contain the default values to use.
		* \param name The name.
		*/
		FeedForwardNetworkTopologyPreferenceGroup(const FeedForwardNetworkTopologyOptions& options, const std::string& name = "Feed forward network");
		/**
		* \brief Creates feed forward network topology options with the current preference values.
		* \return The feed forward network topology options.
		*/
		FeedForwardNetworkTopologyOptions create() const;
		// Inherited:
		AbstractCloneable* clone() const override;
	};
}

USE_PARENT_SERIALIZATION(LightBulb::FeedForwardNetworkTopologyPreferenceGroup, LightBulb::PreferenceGroup, LightBulb);

#endif
