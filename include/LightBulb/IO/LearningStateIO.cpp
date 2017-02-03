// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/IO/LearningStateIO.hpp"
#include "LightBulb/IO/IOStorage.hpp"

// Libary includes
#include <cereal/types/map.hpp>
#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a LearningState.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param learningState The LearningState to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, LearningState& learningState)
	{
		archive(cereal::make_nvp("dataSaveInterval", learningState.dataSaveInterval));
		archive(cereal::make_nvp("dataSets", learningState.dataSets));
		archive(cereal::make_nvp("iterationsNeeded", learningState.iterations));
		archive(cereal::make_nvp("tries", learningState.tries));
	}

	DECLARE_SINGLE_SERIALIZATION_TEMPLATE(LearningState);
}

namespace cereal
{
	template <class Archive>
	void LoadAndConstruct<LightBulb::LearningState>::load_and_construct(Archive& ar, construct<LightBulb::LearningState>& construct)
	{
		using namespace LightBulb;
		int dataSaveInterval;
		ar(make_nvp("dataSaveInterval", dataSaveInterval));
		construct(*IOStorage<std::map<std::string, bool>>::pop(), dataSaveInterval);

		ar(make_nvp("dataSets", construct->dataSets));
		ar(make_nvp("iterationsNeeded", construct->iterations));
		ar(make_nvp("tries", construct->tries));
	}
}