// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/IO/NeuronDescriptionIO.hpp"
#include "LightBulb/Function/ActivationFunction/AbstractActivationFunction.hpp"
#include "LightBulb/Function/InputFunction/AbstractInputFunction.hpp"

// Libary includes
#include <cereal/cereal.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	template <class Archive>
	void serialize(Archive& archive, NeuronDescription& neuronDescription)
	{
		archive(cereal::make_nvp("inputFunction", neuronDescription.inputFunction));
		archive(cereal::make_nvp("activationFunction", neuronDescription.activationFunction));
	}

	DECLARE_SINGLE_SERIALIZATION_TEMPLATE(NeuronDescription);
}

namespace cereal
{
	template <class Archive>
	void LoadAndConstruct<LightBulb::NeuronDescription>::load_and_construct(Archive& ar, construct<LightBulb::NeuronDescription>& construct)
	{
		using namespace LightBulb;
		std::unique_ptr<AbstractInputFunction> inputFunction;
		ar(make_nvp("inputFunction", inputFunction));
		std::unique_ptr<AbstractActivationFunction> activationFunction;
		ar(make_nvp("activationFunction", activationFunction));
		construct(inputFunction.release(), activationFunction.release());
	}

	DECLARE_LOAD_AND_CONSTRUCT_TEMPLATE(LightBulb::NeuronDescription);
}