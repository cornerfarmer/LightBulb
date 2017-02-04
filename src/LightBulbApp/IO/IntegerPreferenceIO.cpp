#include "LightBulbApp/LightBulbAppPrec.hpp"
#include "LightBulbApp/IO/IntegerPreferenceIO.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	/**
	* \brief Saves an IntegerPreference.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param integerPreference The IntegerPreference to save.
	*/
	template <class Archive>
	void save(Archive& archive, IntegerPreference const& integerPreference)
	{
		archive(cereal::base_class<AbstractPreference>(&integerPreference));
		archive(cereal::make_nvp("value", integerPreference.value));
	}

	/**
	* \brief Loads an IntegerPreference.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param integerPreference The IntegerPreference to load.
	*/
	template <class Archive>
	void load(Archive& archive, IntegerPreference& integerPreference)
	{
		archive(cereal::base_class<AbstractPreference>(&integerPreference));
		archive(cereal::make_nvp("value", integerPreference.value));
	}

	DECLARE_SERIALIZATION_TEMPLATE(IntegerPreference);
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::IntegerPreference);

CEREAL_REGISTER_DYNAMIC_INIT(IntegerPreference)
