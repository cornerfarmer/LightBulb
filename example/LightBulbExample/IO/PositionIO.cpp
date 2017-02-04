#include "IO/PositionIO.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/types/vector.hpp>

template <class Archive>
void save(Archive& archive, Position const& individual)
{
	archive(cereal::base_class<LightBulb::AbstractDefaultIndividual>(&individual));
	archive(cereal::make_nvp("position", individual.position));
}

template <class Archive>
void load(Archive& archive, Position& individual)
{
	archive(cereal::base_class<LightBulb::AbstractDefaultIndividual>(&individual));
	archive(cereal::make_nvp("position", individual.position));
}

DECLARE_SERIALIZATION_TEMPLATE(Position);

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(Position);

CEREAL_REGISTER_DYNAMIC_INIT(Position)