#pragma once

#ifndef _RESILIENTLEARNINGRATEPREFERENCEGROUP_H_
#define _RESILIENTLEARNINGRATEPREFERENCEGROUP_H_

// Includes
#include "PreferenceGroup.hpp"
#include "IO/UseParentSerialization.hpp"
#include "Learning/Supervised/GradientDescentAlgorithms/ResilientLearningRate.hpp"

namespace LightBulb
{

	// Forward declarations

	class ResilientLearningRatePreferenceGroup : public PreferenceGroup
	{
	protected:
		void initialize(ResilientLearningRateOptions& options);
	public:
		ResilientLearningRatePreferenceGroup(std::string name = "Resilient learning rate");
		ResilientLearningRatePreferenceGroup(ResilientLearningRateOptions& options, std::string name = "Resilient learning rate");

		ResilientLearningRateOptions create();

		AbstractPreferenceElement* getCopy();
	};
}

USE_PARENT_SERIALIZATION(LightBulb::ResilientLearningRatePreferenceGroup, PreferenceGroup, LightBulb);

#endif
