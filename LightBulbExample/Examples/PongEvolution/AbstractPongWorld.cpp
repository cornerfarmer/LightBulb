// Includes
#include "Examples/PongEvolution/AbstractPongWorld.hpp"
//Library includes

AbstractPongWorld::AbstractPongWorld()
{
	watchMode = false;
}

void AbstractPongWorld::startWatchMode()
{
	watchMode = true;
}

void AbstractPongWorld::stopWatchMode()
{
	watchMode = false;
}

PongGame* AbstractPongWorld::getGame()
{
	return &game;
}
