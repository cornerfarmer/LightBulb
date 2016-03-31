// Includes
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "IO/LayeredNetworkIO.cpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

template <class Archive>
void serialize(Archive& archive, NeuralNetwork& neuralNetwork)
{
	archive(CEREAL_NVP(neuralNetwork.networkTopology));
}

namespace cereal
{
	template <> struct LoadAndConstruct<NeuralNetwork>
	{
		template <class Archive>
		static void load_and_construct(Archive& ar, cereal::construct<NeuralNetwork>& construct)
		{
			std::unique_ptr<AbstractNetworkTopology> networkTopology;
			ar(networkTopology);
			construct(networkTopology.release());
		}
	};
}

#include <cereal/archives/xml.hpp>

CEREAL_REGISTER_TYPE(NeuralNetwork);
