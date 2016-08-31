#pragma once

#ifndef _ABSTRACTRANDOMFUNCTION_H_
#define _ABSTRACTRANDOMFUNCTION_H_

// Includes
#include "Random/AbstractRandomGeneratorUser.hpp"

class AbstractRandomFunction : public AbstractRandomGeneratorUser
{
private:
public:
	virtual ~AbstractRandomFunction() {}
	// Inherited:	
	virtual int execute(int elementCount) = 0;
};

#endif
