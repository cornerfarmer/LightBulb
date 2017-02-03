#include "LightBulbApp/LightBulbAppPrec.hpp"
#include "LightBulbApp/IO/ChoicePreferenceIO.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	/**
	* \brief Saves an ChoicePreference.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param choicePreference The ChoicePreference to save.
	*/
	template <class Archive>
	void save(Archive& archive, ChoicePreference const& choicePreference)
	{
		archive(cereal::base_class<AbstractPreference>(&choicePreference));
		archive(cereal::make_nvp("value", choicePreference.value));
	}

	/**
	* \brief Loads an ChoicePreference.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param choicePreference The ChoicePreference to load.
	*/
	template <class Archive>
	void load(Archive& archive, ChoicePreference& choicePreference)
	{
		archive(cereal::base_class<AbstractPreference>(&choicePreference));
		archive(cereal::make_nvp("value", choicePreference.value));
	}

	DECLARE_SERIALIZATION_TEMPLATE(ChoicePreference);
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::ChoicePreference);
