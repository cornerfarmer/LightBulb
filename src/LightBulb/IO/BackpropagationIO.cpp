// Includes
#include "LightBulb/IO/BackpropagationIO.hpp"
#include "LightBulb/IO/EigenMatrixIO.hpp"
#include "LightBulb/IO/TemplateDeclaration.hpp"
// Libary includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes Backpropagation.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param backpropagation The Backpropagation to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, Backpropagation& backpropagation)
	{
		archive(cereal::base_class<AbstractGradientCalculation>(&backpropagation));
		archive(cereal::make_nvp("lastDeltaVectorOutputLayer", backpropagation.lastDeltaVectorOutputLayer));
	}

	DECLARE_SINGLE_SERIALIZATION_TEMPLATE(Backpropagation);
}

namespace cereal
{

	template <class Archive>
	void LoadAndConstruct<LightBulb::Backpropagation>::construct(Archive& ar, LightBulb::Backpropagation& backpropagation)
	{
		ar(base_class<LightBulb::AbstractGradientCalculation>(&backpropagation));
		ar(make_nvp("lastDeltaVectorOutputLayer", backpropagation.lastDeltaVectorOutputLayer));
	}
}


#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::Backpropagation);

CEREAL_REGISTER_DYNAMIC_INIT(Backpropagation)