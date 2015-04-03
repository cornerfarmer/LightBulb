#pragma once

#ifndef _INPUTFUNCTION_H_
#define _INPUTFUNCTION_H_

#include <list>

class Edge;

class InputFunction
{
private:
public:
	virtual float execute(std::list<Edge*> input) = 0;
};

#endif