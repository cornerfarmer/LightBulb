#ifndef _LEARNINGRESULT_H_
#define _LEARNINGRESULT_H_
#include <vector>
#include <map>
#include <Event/Observable.hpp>

enum LearningStateEvents
{
	EVT_LS_DS_CHANGED
};


// All informations about a finished learning process
struct LearningState : public LightBulb::Observable<LearningStateEvents, LearningState>
{
	// Was the learning process successful
	int successful;

	double quality;
	// How many iterations were needed
	int iterationsNeeded;

	std::map<std::string, std::vector<double>> dataSets;
	LearningState()
	{
		successful = 0;
		quality = 0;
		iterationsNeeded = 0;
	}

	void addData(std::string dataSetLabel, int iteration, double data)
	{
		dataSets[dataSetLabel].push_back(iteration);
		dataSets[dataSetLabel].push_back(data);
		throwEvent(EVT_LS_DS_CHANGED, this);
	}

};

#endif
