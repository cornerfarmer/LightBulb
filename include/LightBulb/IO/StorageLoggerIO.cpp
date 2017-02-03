// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/IO/StorageLoggerIO.hpp"

#include <cereal/types/vector.hpp>
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a StorageLogger.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param storageLogger The StorageLogger to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, StorageLogger& storageLogger)
	{
		archive(cereal::base_class<AbstractLogger>(&storageLogger));
		archive(cereal::make_nvp("messages", storageLogger.messages));
	}

	DECLARE_SINGLE_SERIALIZATION_TEMPLATE(StorageLogger);
}


#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::StorageLogger);

