// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/IO/SameNeuronDescriptionFactoryIO.hpp"
#include "LightBulb/NeuronDescription/NeuronDescription.hpp"

// Library includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a SameNeuronDescriptionFactory.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param descriptionFactory The SameNeuronDescriptionFactory to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, SameNeuronDescriptionFactory& descriptionFactory)
	{
		archive(cereal::make_nvp("neuronDescription", descriptionFactory.neuronDescription));
		archive(cereal::base_class<AbstractNeuronDescriptionFactory>(&descriptionFactory));
	}

	DECLARE_SINGLE_SERIALIZATION_TEMPLATE(SameNeuronDescriptionFactory);
}

namespace cereal
{
	template <class Archive>
	void LoadAndConstruct<LightBulb::SameNeuronDescriptionFactory>::load_and_construct(Archive& ar, construct<LightBulb::SameNeuronDescriptionFactory>& construct)
	{
		using namespace LightBulb;
		std::unique_ptr<NeuronDescription> neuronDescription;
		ar(make_nvp("neuronDescription", neuronDescription));
		construct(neuronDescription.release());
		ar(cereal::base_class<AbstractNeuronDescriptionFactory>(construct.ptr()));
	}
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::SameNeuronDescriptionFactory);
