#pragma once

#ifndef _ABSTRACTPONGENVIRONMENT_H_
#define _ABSTRACTPONGENVIRONMENT_H_

// Library Includes

// Include
#include <Examples/PongEvolution/PongGame.hpp>
#include <Event/Observable.hpp>

// Forward declarations


enum PongEvents
{
	EVT_FIELD_CHANGED
};

class AbstractPongEnvironment : public LightBulb::Observable<PongEvents, AbstractPongEnvironment>
{
protected:
	PongGame game;
	bool watchMode;
public:
	AbstractPongEnvironment();
	virtual ~AbstractPongEnvironment() {};
	void startWatchMode();
	void stopWatchMode();
	PongGame& getGame();
};


#endif
