// Includes
#include "LightBulb/IO/DefaultReinforcementIndividualIO.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/IO/TemplateDeclaration.hpp"
// Libraray includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes an DefaultReinforcementIndividual
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param individual The DefaultReinforcementIndividual to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, DefaultReinforcementIndividual& individual)
	{
		archive(cereal::make_nvp("neuralNetwork", individual.neuralNetwork));
		archive(cereal::make_nvp("epsilon", individual.epsilon));
	}

	DECLARE_SINGLE_SERIALIZATION_TEMPLATE(DefaultReinforcementIndividual);
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::DefaultReinforcementIndividual);

CEREAL_REGISTER_DYNAMIC_INIT(DefaultReinforcementIndividual)