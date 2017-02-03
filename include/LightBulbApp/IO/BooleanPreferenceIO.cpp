#include "LightBulbApp/LightBulbAppPrec.hpp"
#include "LightBulbApp/IO/BooleanPreferenceIO.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	/**
	* \brief Saves an BooleanPreference.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param booleanPreference The BooleanPreference to save.
	*/
	template <class Archive>
	void save(Archive& archive, BooleanPreference const& booleanPreference)
	{
		archive(cereal::base_class<AbstractPreference>(&booleanPreference));
		archive(cereal::make_nvp("value", booleanPreference.value));
	}

	/**
	* \brief Loads an BooleanPreference.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param booleanPreference The BooleanPreference to load.
	*/
	template <class Archive>
	void load(Archive& archive, BooleanPreference& booleanPreference)
	{
		archive(cereal::base_class<AbstractPreference>(&booleanPreference));
		archive(cereal::make_nvp("value", booleanPreference.value));
	}

	DECLARE_SERIALIZATION_TEMPLATE(BooleanPreference);
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::BooleanPreference);
