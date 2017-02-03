// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/IO/ZigguratGeneratorIO.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/vector.hpp>

namespace LightBulb
{
	/**
	* \brief Saves a ZigguratGenerator.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param zigguratGenerator The ZigguratGenerator to save.
	*/
	template <class Archive>
	void save(Archive& archive, ZigguratGenerator const& zigguratGenerator)
	{
		archive(cereal::base_class<AbstractRandomGenerator>(&zigguratGenerator));

		archive(cereal::make_nvp("kn", zigguratGenerator.kn));
		archive(cereal::make_nvp("fn", zigguratGenerator.fn));
		archive(cereal::make_nvp("wn", zigguratGenerator.wn));
		archive(cereal::make_nvp("state", zigguratGenerator.state));
	}

	/**
	* \brief Loads a ZigguratGenerator.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param zigguratGenerator The ZigguratGenerator to load.
	*/
	template <class Archive>
	void load(Archive& archive, ZigguratGenerator& zigguratGenerator)
	{
		archive(cereal::base_class<AbstractRandomGenerator>(&zigguratGenerator));

		archive(cereal::make_nvp("kn", zigguratGenerator.kn));
		archive(cereal::make_nvp("fn", zigguratGenerator.fn));
		archive(cereal::make_nvp("wn", zigguratGenerator.wn));
		archive(cereal::make_nvp("state", zigguratGenerator.state));
	}

	DECLARE_SERIALIZATION_TEMPLATE(ZigguratGenerator);
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::ZigguratGenerator)

CEREAL_REGISTER_DYNAMIC_INIT(ZigguratGenerator)