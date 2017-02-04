// Includes
#include "Examples/PongEvolution/AbstractPongEnvironment.hpp"
//Library includes

AbstractPongEnvironment::AbstractPongEnvironment()
{
	watchMode = false;
}

void AbstractPongEnvironment::startWatchMode()
{
	watchMode = true;
}

void AbstractPongEnvironment::stopWatchMode()
{
	watchMode = false;
}

PongGame& AbstractPongEnvironment::getGame()
{
	return game;
}
