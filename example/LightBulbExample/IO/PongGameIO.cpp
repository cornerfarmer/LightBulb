#include "LightBulbExamplePrec.hpp"
#include "IO/PongGameIO.hpp"

#include <cereal/cereal.hpp>

template <class Archive>
void serialize(Archive& archive, PongGameState& state)
{
	archive(cereal::make_nvp("ballPosX", state.ballPosX));
	archive(cereal::make_nvp("ballPosY", state.ballPosY));
	archive(cereal::make_nvp("ballVelX", state.ballVelX));
	archive(cereal::make_nvp("ballVelY", state.ballVelY));
	archive(cereal::make_nvp("paddle1Pos", state.paddle1Pos));
	archive(cereal::make_nvp("paddle2Pos", state.paddle2Pos));
}

DECLARE_SINGLE_SERIALIZATION_TEMPLATE(PongGameState);

template <class Archive>
void serialize(Archive& archive, PongGame& game)
{
	archive(cereal::make_nvp("state", game.state));
}

DECLARE_SINGLE_SERIALIZATION_TEMPLATE(PongGame);

namespace cereal
{
	template <class Archive>
	void LoadAndConstruct<PongGame>::construct(Archive& ar, PongGame& game)
	{
		ar(make_nvp("state", game.state));
	}
}

