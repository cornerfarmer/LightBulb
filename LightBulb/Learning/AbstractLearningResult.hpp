#ifndef _ABSTRACTLEARNINGRESULT_H_
#define _ABSTRACTLEARNINGRESULT_H_

#include <string>

struct AbstractLearningResult
{
	double quality;

	std::string qualityLabel;

	std::shared_ptr<LearningState> learningState;

	bool succeeded;
};

#endif
