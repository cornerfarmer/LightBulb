// Includes
#include "Examples/PongEvolution/PongAI.hpp"
#include "Examples/PongEvolution/Pong.hpp"

using namespace LightBulb;

PongAI::PongAI(FeedForwardNetworkTopologyOptions& options, Pong& pong_)
	: AbstractDefaultIndividual(pong_)
{
	currentGame = &pong_;
	buildNeuralNetwork(options);
}


void PongAI::getNNInput(std::vector<double>& input)
{
	currentGame->getNNInput(input);
}

void PongAI::interpretNNOutput(std::vector<double>& output)
{
	if (output[0] > 0.5)
		currentGame->getGame().movePaddle(1);
	else if (output[1] > 0.5)
		currentGame->getGame().movePaddle(-1);
}


void PongAI::setPong(Pong& currentGame_)
{
	currentGame = &currentGame_;
}