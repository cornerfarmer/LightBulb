#pragma once

#ifndef _ACTIVATIONFUNCTION_H_
#define _ACTIVATIONFUNCTION_H_

class ActivationFunction
{
private:
public:
	virtual float execute(float input) = 0;
};

#endif