#pragma once

#ifndef _ABSTRACTCHANGEABLEPARAMETER_H_
#define _ABSTRACTCHANGEABLEPARAMETER_H_

class AbstractChangeableParameter
{
private:

public:
	virtual ~AbstractChangeableParameter() {};
	virtual bool switchToNextValue() = 0;
	virtual void resetToStart() = 0;
	virtual void printCurrentValue() = 0;
};

#endif /* DIAGNOSTIC_ABSTRACTCHANGEABLEPARAMETER_HPP_ */