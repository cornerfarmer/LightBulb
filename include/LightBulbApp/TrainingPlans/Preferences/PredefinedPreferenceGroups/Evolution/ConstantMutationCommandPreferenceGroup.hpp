#pragma once

#ifndef _CONSTANTMUTATIONCOMMANDPREFERENCEGROUP_H_
#define _CONSTANTMUTATIONCOMMANDPREFERENCEGROUP_H_

// Includes
#include "LightBulbApp/TrainingPlans/Preferences/PreferenceGroup.hpp"
#include "LightBulb/IO/UseParentSerialization.hpp"
#include "LightBulb/Learning/Evolution/ConstantMutationCommand.hpp"

namespace LightBulb
{
	/**
	* \brief Describes a predefined preference group for a constant mutation command.
	*/
	class ConstantMutationCommandPreferenceGroup : public PreferenceGroup
	{
	protected:
	public:
		/**
		* \brief Creates a constant mutation command preference group with standard default values.
		* \param name The name.
		*/
		ConstantMutationCommandPreferenceGroup(const std::string& name = "Constant mutation");
		/**
		 * \brief Creates a new constant mutation command object with the current preference values.
		 * \return The new constant mutation command.
		 */
		ConstantMutationCommand* create() const;
		// Inherited:
		AbstractCloneable* clone() const override;
	};
}

USE_PARENT_SERIALIZATION(LightBulb::ConstantMutationCommandPreferenceGroup, LightBulb::PreferenceGroup, LightBulb);

#endif
