// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/IO/RMSPropLearningRateIO.hpp"
#include "LightBulb/IO/ConstructExisting.hpp"
#include "LightBulb/IO/EigenMatrixIO.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a RMSPropLearningRate.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param rmsPropLearningRate The RMSPropLearningRate to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, RMSPropLearningRate& rmsPropLearningRate)
	{
		archive(cereal::base_class<AbstractGradientDescentAlgorithm>(&rmsPropLearningRate));
		archive(cereal::make_nvp("prevDeltaWeights", rmsPropLearningRate.prevDeltaWeights));
		archive(cereal::make_nvp("prevGradient", rmsPropLearningRate.prevGradient));
		archive(cereal::make_nvp("prevSquaredGradient", rmsPropLearningRate.prevSquaredGradient));
	}

	DECLARE_SINGLE_SERIALIZATION_TEMPLATE(RMSPropLearningRate);
}

namespace cereal
{
	template <class Archive>
	void LoadAndConstruct<LightBulb::RMSPropLearningRate>::construct(Archive& ar, LightBulb::RMSPropLearningRate& rmsPropLearningRate)
	{
		using namespace LightBulb;
		ar(base_class<AbstractGradientDescentAlgorithm>(&rmsPropLearningRate));
		ar(make_nvp("prevDeltaWeights", rmsPropLearningRate.prevDeltaWeights));
		ar(make_nvp("prevGradient", rmsPropLearningRate.prevGradient));
		ar(make_nvp("prevSquaredGradient", rmsPropLearningRate.prevSquaredGradient));
	}
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::RMSPropLearningRate);

CEREAL_REGISTER_DYNAMIC_INIT(RMSPropLearningRate)