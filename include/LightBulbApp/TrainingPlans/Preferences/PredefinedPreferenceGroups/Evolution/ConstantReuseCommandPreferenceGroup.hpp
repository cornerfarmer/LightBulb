#pragma once

#ifndef _CONSTANTREUSECOMMANDPREFERENCEGROUP_H_
#define _CONSTANTREUSECOMMANDPREFERENCEGROUP_H_

// Includes
#include "LightBulbApp/TrainingPlans/Preferences/PreferenceGroup.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"
#include "LightBulb/Learning/Evolution/ConstantReuseCommand.hpp"

namespace LightBulb
{
	/**
	* \brief Describes a predefined preference group for a constant reuse command.
	*/
	class ConstantReuseCommandPreferenceGroup : public PreferenceGroup
	{
	protected:
	public:
		/**
		* \brief Creates a constant reuse command preference group with standard default values.
		* \param name The name.
		*/
		ConstantReuseCommandPreferenceGroup(const std::string& name = "Constant reuse");
		/**
		 * \brief Creates a new constant reuse command object with the current preference values.
		 * \return The new constant reuse command.
		 */
		ConstantReuseCommand* create() const;
		// Inherited:
		AbstractCloneable* clone() const override;
	};
}

USE_PARENT_SERIALIZATION(LightBulb::ConstantReuseCommandPreferenceGroup, LightBulb::PreferenceGroup, LightBulb);

#endif
