#pragma once

#ifndef _BESTSELECTIONCOMMANDPREFERENCEGROUP_H_
#define _BESTSELECTIONCOMMANDPREFERENCEGROUP_H_

// Includes
#include "TrainingPlans/Preferences/PreferenceGroup.hpp"
#include "IO/UseParentSerialization.hpp"
#include "Learning/Evolution/BestSelectionCommand.hpp"

namespace LightBulb
{
	/**
	* \brief Describes a predefined preference group for a best selection command.
	*/
	class BestSelectionCommandPreferenceGroup : public PreferenceGroup
	{
	protected:
	public:
		/**
		* \brief Creates a best selection command preference group with standard default values.
		* \param name The name.
		*/
		BestSelectionCommandPreferenceGroup(const std::string& name = "Select best");
		/**
		 * \brief Creates a new best selection command object with the current preference values.
		 * \return The new best selection command.
		 */
		BestSelectionCommand* create() const;
		// Inherited:
		AbstractCloneable* clone() const override;
	};
}

USE_PARENT_SERIALIZATION(LightBulb::BestSelectionCommandPreferenceGroup, LightBulb::PreferenceGroup, LightBulb);

#endif
