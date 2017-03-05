// Includes
#include "Examples/PongReinforcement/PongReinforcementIndividual.hpp"
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementEnvironment.hpp"
#include "PongReinforcementEnvironment.hpp"

PongReinforcementIndividual::PongReinforcementIndividual(LightBulb::AbstractReinforcementEnvironment* environment_, LightBulb::FeedForwardNetworkTopologyOptions& options, bool epsilonGreedly, double epsilon)
	:AbstractDefaultReinforcementIndividual(environment_, options, epsilonGreedly, epsilon)
{
}

PongReinforcementIndividual::PongReinforcementIndividual()
{
}

void PongReinforcementIndividual::interpretNNOutput(LightBulb::Vector<char>& output)
{
	static_cast<PongReinforcementEnvironment*>(environment)->interpretNNOutput(output);
}

void PongReinforcementIndividual::isTerminalState(LightBulb::Scalar<char>& isTerminalState) const
{
	static_cast<PongReinforcementEnvironment*>(environment)->isTerminalState(isTerminalState);
}

void PongReinforcementIndividual::getNNInput(LightBulb::Vector<>& input) const
{
	static_cast<PongReinforcementEnvironment*>(environment)->getNNInput(input);
}

void PongReinforcementIndividual::getReward(LightBulb::Scalar<>& reward) const
{
	reward.getEigenValueForEditing() = static_cast<PongReinforcementEnvironment*>(environment)->getGame().whoHasWon();
}
