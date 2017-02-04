// Includes
#include "LightBulb/IO/SimpleGradientDescentIO.hpp"
#include "LightBulb/IO/EigenMatrixIO.hpp"
#include "LightBulb/LinearAlgebra/Matrix.hpp"
#include "LightBulb/IO/TemplateDeclaration.hpp"

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes SimpleGradientDescent.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param simpleGradientDescent The SimpleGradientDescent to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, SimpleGradientDescent& simpleGradientDescent)
	{
		archive(cereal::base_class<AbstractGradientDescentAlgorithm>(&simpleGradientDescent));
		archive(cereal::make_nvp("previousDeltaWeights", simpleGradientDescent.previousDeltaWeights));
	}

	DECLARE_SINGLE_SERIALIZATION_TEMPLATE(SimpleGradientDescent);
}

namespace cereal
{
	template <class Archive>
	void LoadAndConstruct<LightBulb::SimpleGradientDescent>::construct(Archive& ar, LightBulb::SimpleGradientDescent& simpleGradientDescent)
	{
		using namespace LightBulb;
		ar(base_class<AbstractGradientDescentAlgorithm>(&simpleGradientDescent));
		ar(make_nvp("previousDeltaWeights", simpleGradientDescent.previousDeltaWeights));
	}
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::SimpleGradientDescent);

CEREAL_REGISTER_DYNAMIC_INIT(SimpleGradientDescent)