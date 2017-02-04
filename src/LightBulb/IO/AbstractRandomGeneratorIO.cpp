// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/IO/AbstractRandomGeneratorIO.hpp"

// Libraray includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	/**
	* \brief Saves an AbstractRandomGenerator.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param randomGenerator The AbstractRandomGenerator to save.
	*/
	template <class Archive>
	void save(Archive& archive, AbstractRandomGenerator const& randomGenerator)
	{
		archive(cereal::make_nvp("seed", randomGenerator.seed));
	}

	/**
	* \brief Loads an AbstractRandomGenerator.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param randomGenerator The AbstractRandomGenerator to load.
	*/
	template <class Archive>
	void load(Archive& archive, AbstractRandomGenerator& randomGenerator)
	{
		archive(cereal::make_nvp("seed", randomGenerator.seed));
	}

	DECLARE_SERIALIZATION_TEMPLATE(AbstractRandomGenerator);
}