#pragma once

#ifndef _ABSTRACTRANDOMFUNCTION_H_
#define _ABSTRACTRANDOMFUNCTION_H_

class AbstractRandomFunction
{
private:
public:
	virtual ~AbstractRandomFunction() {}
	// Inherited:	
	virtual int execute(int elementCount) = 0;
};

#endif
