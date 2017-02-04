// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/IO/AbstractLoggerIO.hpp"

// Libary includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a logger.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param logger The AbstractLogger to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, AbstractLogger& logger)
	{
		archive(cereal::make_nvp("currentLogLevel", logger.currentLogLevel));
	}

	DECLARE_SINGLE_SERIALIZATION_TEMPLATE(AbstractLogger);
}
