#pragma once

#ifndef _RESILIENTLEARNINGRATEPREFERENCEGROUP_H_
#define _RESILIENTLEARNINGRATEPREFERENCEGROUP_H_

// Includes
#include "TrainingPlans/Preferences/PreferenceGroup.hpp"
#include "IO/UseParentSerialization.hpp"
#include "Learning/Supervised/GradientDescentAlgorithms/ResilientLearningRate.hpp"

namespace LightBulb
{

	// Forward declarations

	class ResilientLearningRatePreferenceGroup : public PreferenceGroup
	{
	protected:
		void initialize(const ResilientLearningRateOptions& options);
	public:
		ResilientLearningRatePreferenceGroup(const std::string& name = "Resilient learning rate");
		ResilientLearningRatePreferenceGroup(const ResilientLearningRateOptions& options, const std::string& name = "Resilient learning rate");

		ResilientLearningRateOptions create() const;

		AbstractPreferenceElement* getCopy() const override;
	};
}

USE_PARENT_SERIALIZATION(LightBulb::ResilientLearningRatePreferenceGroup, PreferenceGroup, LightBulb);

#endif
