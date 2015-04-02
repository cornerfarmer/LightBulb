#pragma once

#ifndef _INPUTFUNCTION_H_
#define _INPUTFUNCTION_H_

class InputFunction
{
private:
public:
	virtual float execute(float* input, int inputCount) = 0;
};

#endif