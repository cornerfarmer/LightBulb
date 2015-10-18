#ifndef _LEARNINGRESULT_H_
#define _LEARNINGRESULT_H_

struct LearningResult
{
	int successful;
	int iterationsNeeded;
	LearningResult()
	{
		successful = 0;
		iterationsNeeded = 0;
	}
};

#endif
