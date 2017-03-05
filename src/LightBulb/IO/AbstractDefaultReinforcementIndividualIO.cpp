// Includes
#include "LightBulb/IO/AbstractDefaultReinforcementIndividualIO.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/IO/TemplateDeclaration.hpp"
// Libraray includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes an AbstractDefaultReinforcementIndividual
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param individual The AbstractDefaultReinforcementIndividual to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, AbstractDefaultReinforcementIndividual& individual)
	{
		archive(cereal::make_nvp("neuralNetwork", individual.neuralNetwork));
		archive(cereal::make_nvp("epsilon", individual.epsilon));
	}

	DECLARE_SINGLE_SERIALIZATION_TEMPLATE(AbstractDefaultReinforcementIndividual);
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::AbstractDefaultReinforcementIndividual);

CEREAL_REGISTER_DYNAMIC_INIT(AbstractDefaultReinforcementIndividual)