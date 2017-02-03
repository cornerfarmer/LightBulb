#include "LightBulbExamplePrec.hpp"
#include "IO/NetworkIO.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/vector.hpp>

template <class Archive>
void save(Archive& archive, Network const& individual)
{
	archive(cereal::base_class<LightBulb::AbstractDefaultIndividual>(&individual));
	archive(cereal::make_nvp("positions", individual.positions));
}

template <class Archive>
void load(Archive& archive, Network& individual)
{
	archive(cereal::base_class<LightBulb::AbstractDefaultIndividual>(&individual));
	archive(cereal::make_nvp("positions", individual.positions));
}

DECLARE_SERIALIZATION_TEMPLATE(Network);

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(Network);