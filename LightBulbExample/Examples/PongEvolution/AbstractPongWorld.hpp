#pragma once

#ifndef _ABSTRACTPONGWORLD_H_
#define _ABSTRACTPONGWORLD_H_

// Library Includes

// Include
#include <Examples/PongEvolution/PongGame.hpp>
#include <Event/Observable.hpp>

// Forward declarations


enum PongEvents
{
	EVT_FIELD_CHANGED
};

class AbstractPongWorld : public LightBulb::Observable<PongEvents, AbstractPongWorld>
{
protected:
	PongGame game;
	bool watchMode;
public:
	AbstractPongWorld();
	virtual ~AbstractPongWorld() {};
	void startWatchMode();
	void stopWatchMode();
	PongGame* getGame();
};


#endif
