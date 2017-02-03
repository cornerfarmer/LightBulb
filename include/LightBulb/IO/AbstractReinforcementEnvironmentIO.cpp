// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/IO/AbstractReinforcementEnvironmentIO.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"

// Libraray includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes an AbstractReinforcementEnvironment
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param environment The AbstractReinforcementEnvironment to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, AbstractReinforcementEnvironment& environment)
	{
		archive(cereal::make_nvp("neuralNetwork", environment.neuralNetwork));
		archive(cereal::make_nvp("epsilon", environment.epsilon));
	}

	DECLARE_SINGLE_SERIALIZATION_TEMPLATE(AbstractReinforcementEnvironment);
}