// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/IO/AbstractHallOfFameAlgorithmIO.hpp"
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"

// Libraray includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes an AbstractHallOfFameAlgorithm
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param hallOfFameAlgorithm The AbstractHallOfFameAlgorithm to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, AbstractHallOfFameAlgorithm& hallOfFameAlgorithm)
	{
		archive(cereal::make_nvp("members", hallOfFameAlgorithm.members));
	}

	DECLARE_SINGLE_SERIALIZATION_TEMPLATE(AbstractHallOfFameAlgorithm);
}
