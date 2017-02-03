#include "LightBulbExamplePrec.hpp"
#include "IO/NetworkSimulatorIO.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>

template <class Archive>
void save(Archive& archive, NetworkSimulator const& environment)
{
	archive(cereal::base_class<LightBulb::AbstractSimpleEvolutionEnvironment>(&environment));
	archive(cereal::make_nvp("consumers", environment.consumers));
}

template <class Archive>
void load(Archive& archive, NetworkSimulator& environment)
{
	archive(cereal::base_class<LightBulb::AbstractSimpleEvolutionEnvironment>(&environment));
	archive(cereal::make_nvp("consumers", environment.consumers));
}

DECLARE_SERIALIZATION_TEMPLATE(NetworkSimulator);

namespace cereal
{
	template <class Archive>
	void LoadAndConstruct<NetworkSimulator>::construct(Archive& ar, NetworkSimulator& environment)
	{
		ar(base_class<LightBulb::AbstractSimpleEvolutionEnvironment>(&environment));
		ar(make_nvp("consumers", environment.consumers));
	}
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(NetworkSimulator);

CEREAL_REGISTER_DYNAMIC_INIT(NetworkSimulator)