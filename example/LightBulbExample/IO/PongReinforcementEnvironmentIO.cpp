#include "IO/PongReinforcementEnvironmentIO.hpp"

// Libary includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

template <class Archive>
void serialize(Archive& archive, PongReinforcementEnvironment& environment)
{
	archive(cereal::base_class<LightBulb::AbstractReinforcementEnvironment>(&environment));
	archive(cereal::make_nvp("time", environment.time));
	archive(cereal::make_nvp("game", environment.game));
}

DECLARE_SINGLE_SERIALIZATION_TEMPLATE(PongReinforcementEnvironment);

namespace cereal
{
	template <class Archive>
	void LoadAndConstruct<PongReinforcementEnvironment>::construct(Archive& ar, PongReinforcementEnvironment& environment)
	{
		using namespace LightBulb;
		ar(base_class<AbstractReinforcementEnvironment>(&environment));
		ar(make_nvp("time", environment.time));

		IOStorage<PongGame>::push(&environment.game);
		ar(make_nvp("game", environment.game));
		IOStorage<PongGame>::clear();
	}
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(PongReinforcementEnvironment);

CEREAL_REGISTER_DYNAMIC_INIT(PongReinforcementEnvironment)