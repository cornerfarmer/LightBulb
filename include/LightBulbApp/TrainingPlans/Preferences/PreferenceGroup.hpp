#pragma once

#ifndef _PREFERENCEGROUP_H_
#define _PREFERENCEGROUP_H_

// Includes
#include "AbstractPreferenceElement.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/AbstractPreference.hpp"

// Library includes
#include <memory>
#include <string>

namespace LightBulb
{
	/**
	 * \brief Describes a preference group which contains multiple preference elements.
	 */
	class PreferenceGroup : public AbstractPreferenceElement
	{
		template <class Archive>
		friend void save(Archive& archive, PreferenceGroup const& preferenceGroup);
		template <class Archive>
		friend void load(Archive& archive, PreferenceGroup& preferenceGroup);
	protected:
		/**
		 * \brief The name of the group.
		 */
		std::string name;
		/**
		 * \brief The preference storage.
		 */
		std::vector<std::unique_ptr<AbstractPreferenceElement>> preferences;
	public:
		virtual ~PreferenceGroup() {}
		/**
		 * \brief Creates a preference group.
		 * \param name_ The name of the group.
		 */
		PreferenceGroup(const std::string& name_);
		/**
		 * \brief Copy contructor.
		 * \param other The group to copy.
		 */
		PreferenceGroup(const PreferenceGroup& other);
		/**
		 * \brief Creates a empty preference group.
		 */
		PreferenceGroup() = default;
		PreferenceGroup(PreferenceGroup&& other) noexcept;
		PreferenceGroup& operator=(PreferenceGroup other);
		friend void swap(PreferenceGroup& lhs, PreferenceGroup& rhs) noexcept;
		/**
		 * \brief Adds a preference to the group.
		 * \param preferenceElement The new preference element to store.
		 */
		void addPreference(AbstractPreferenceElement* preferenceElement);
		/**
		 * \brief Returns the preference with the given name.
		 * \param preferenceName The name to search for.
		 * \return The preference.
		 * \throws std::invalid_argument If there is no preference with the given name.
		 */
		const AbstractPreference& getPreference(const std::string& preferenceName) const;
		/**
		 * \brief Returns the preference group with the given name.
		 * \param preferenceGroupName The name to search for.
		 * \return The prefernce group.
		 * \throws std::invalid_argument If there is no preference group with the given name.
		 */
		PreferenceGroup& getPreferenceGroup(const std::string& preferenceGroupName) const;
		/**
		* \brief Returns the value of the double preference with the given name.
		* \param preferenceName The name of the preference to search for.
		* \return The value.
		* \throws std::invalid_argument If there is no double preference with the given name.
		*/
		double getDoublePreference(const std::string& preferenceName) const;
		/**
		* \brief Returns the value of the integer preference with the given name.
		* \param preferenceName The name of the preference to search for.
		* \return The value.
		* \throws std::invalid_argument If there is no integer preference with the given name.
		*/
		int getIntegerPreference(const std::string& preferenceName) const;
		/**
		* \brief Returns the value of the boolean preference with the given name.
		* \param preferenceName The name of the preference to search for.
		* \return The value.
		* \throws std::invalid_argument If there is no boolean preference with the given name.
		*/
		bool getBooleanPreference(const std::string& preferenceName) const;
		/**
		* \brief Returns the value of the choice preference with the given name.
		* \param preferenceName The name of the preference to search for.
		* \return The value.
		* \throws std::invalid_argument If there is no choice preference with the given name.
		*/
		std::string getChoicePreference(const std::string& preferenceName) const;
		/**
		 * \brief Returns all preference elements.
		 * \return A vector of all stored preference elements.
		 */
		const std::vector<std::unique_ptr<AbstractPreferenceElement>>& getPreferenceElements() const;
		/**
		 * \brief Calls the create() method on the first preference group with the given type and returns the retrieved object.
		 * \tparam Class The class of the object which should be returned.
		 * \tparam PreferenceGroupClass The class of the preference group to serach for.
		 * \return The created object.
		 * \throws std::invalid_argument If there is no group with the given type.
		 */
		template<class Class, class PreferenceGroupClass>
		Class createFromGroup() const
		{
			for (auto preference = preferences.begin(); preference != preferences.end(); preference++)
			{
				if (PreferenceGroupClass* preferenceGroup = dynamic_cast<PreferenceGroupClass*>(preference->get()))
					return preferenceGroup->create();
			}
			throw std::invalid_argument("The preference group could not be found.");
		}
		/**
		* \brief Calls the create() method on the preference group with the given type and the given name and returns the retrieved object.
		* \tparam Class The class of the object which should be returned.
		* \tparam PreferenceGroupClass The class of the preference group to serach for.
		* \param groupName The name of the preference group to serach for.
		* \return The created object.
		* \throws std::invalid_argument If there is no preference group with the given name.
		*/
		template<class Class, class PreferenceGroupClass>
		Class createFromGroup(std::string groupName) const
		{
			const PreferenceGroup& preferenceGroup = getPreferenceGroup(groupName);
			const PreferenceGroupClass& castedPreferenceGroup = dynamic_cast<const PreferenceGroupClass&>(preferenceGroup);
			return castedPreferenceGroup.create();

			throw std::invalid_argument("The preference group could not be found.");
		}
		// Inherited:
		const std::string& getName() const override;
		std::string toString(std::string offset = "") const override;
		void setName(std::string newName) override;
		AbstractCloneable* clone() const override;
	};
}

#include "LightBulbApp/IO/PreferenceGroupIO.hpp"

#endif
