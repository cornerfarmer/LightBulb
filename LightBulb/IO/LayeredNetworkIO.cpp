// Libary includes
#include <NetworkTopology/LayeredNetwork.hpp>
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

template <class Archive>
void serialize(Archive& archive, LayeredNetwork& layeredNetwork)
{
	archive(CEREAL_NVP(123));
}

namespace cereal
{
	template <> struct LoadAndConstruct<LayeredNetwork>
	{
		template <class Archive>
		static void load_and_construct(Archive & ar, cereal::construct<LayeredNetwork> & construct)
		{
			LayeredNetworkOptions options;
			construct(options);
		}
	};
}

#include <cereal/archives/xml.hpp>

CEREAL_REGISTER_TYPE(LayeredNetwork);