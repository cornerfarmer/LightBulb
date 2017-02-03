#include "LightBulbApp/LightBulbAppPrec.hpp"
#include "LightBulbApp/IO/PreferenceGroupIO.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	/**
	* \brief Saves a PreferenceGroup.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param preferenceGroup The PreferenceGroup to save.
	*/
	template <class Archive>
	void save(Archive& archive, PreferenceGroup const& preferenceGroup)
	{
		archive(cereal::base_class<AbstractPreferenceElement>(&preferenceGroup));
		archive(cereal::make_nvp("name", preferenceGroup.name));
		archive(cereal::make_nvp("preferences", preferenceGroup.preferences));
	}

	/**
	* \brief Loads a PreferenceGroup.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param preferenceGroup The PreferenceGroup to load.
	*/
	template <class Archive>
	void load(Archive& archive, PreferenceGroup& preferenceGroup)
	{
		archive(cereal::base_class<AbstractPreferenceElement>(&preferenceGroup));
		archive(cereal::make_nvp("name", preferenceGroup.name));
		archive(cereal::make_nvp("preferences", preferenceGroup.preferences));
	}

	DECLARE_SERIALIZATION_TEMPLATE(PreferenceGroup);
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::PreferenceGroup);
