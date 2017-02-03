#include "LightBulbApp/LightBulbAppPrec.hpp"
#include "LightBulbApp/IO/NeuralNetworkRepositoryIO.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
// Libraray includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a NeuralNetworkRepository.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param neuralNetworkRepository The NeuralNetworkRepository to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, NeuralNetworkRepository& neuralNetworkRepository)
	{
		archive(cereal::make_nvp("neuralNetworks", neuralNetworkRepository.neuralNetworks));
		neuralNetworkRepository.throwEvent(EVT_NN_CHANGED, neuralNetworkRepository);
	}

	DECLARE_SINGLE_SERIALIZATION_TEMPLATE(NeuralNetworkRepository);
}
