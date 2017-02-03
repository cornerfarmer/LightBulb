// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/IO/ResilientLearningRateIO.hpp"

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a ResilientLearningRate.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param resilientLearningRate The ResilientLearningRate to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, ResilientLearningRate & resilientLearningRate)
	{
		archive(cereal::base_class<AbstractGradientDescentAlgorithm>(&resilientLearningRate));
		archive(cereal::make_nvp("previousLearningRates", resilientLearningRate.previousLearningRates));
	}

	DECLARE_SINGLE_SERIALIZATION_TEMPLATE(ResilientLearningRate);
}

namespace cereal
{
	template <class Archive>
	void LoadAndConstruct<LightBulb::ResilientLearningRate>::construct(Archive& ar, LightBulb::ResilientLearningRate& resilientLearningRate)
	{
		ar(base_class<LightBulb::AbstractGradientDescentAlgorithm>(&resilientLearningRate));
		ar(make_nvp("previousLearningRates", resilientLearningRate.previousLearningRates));
	}
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::ResilientLearningRate);
