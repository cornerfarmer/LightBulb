#ifndef _LEARNINGRESULT_H_
#define _LEARNINGRESULT_H_
#include <vector>
#include <map>
#include <Event/Observable.hpp>

enum LearningStateEvents
{
	EVT_LS_DS_CHANGED
};

typedef std::vector<double> DataSet;
typedef std::map<std::string, DataSet> DataSetsPerTry;
typedef std::vector<DataSetsPerTry> DataSets;

// All informations about a finished learning process
struct LearningState : public LightBulb::Observable<LearningStateEvents, LearningState>
{
	template <class Archive>
	friend void serialize(Archive& archive, LearningState& learningState);
private:
	int dataSaveInterval;
public:
	// Was the learning process successful
	int successful;

	double quality;
	// How many iterations were needed
	int iterations;

	int tries;

	DataSets dataSets;
	LearningState(int dataSaveInterval_ = 1)
	{
		successful = 0;
		quality = 0;
		iterations = 0;
		tries = 0;
		dataSaveInterval = dataSaveInterval_;
	}

	void addData(std::string dataSetLabel, double data)
	{
		if ((iterations - 1) % dataSaveInterval == 0)
		{
			dataSets[tries - 1][dataSetLabel].push_back(iterations - 1);
			dataSets[tries - 1][dataSetLabel].push_back(data);
			throwEvent(EVT_LS_DS_CHANGED, this);
		}
	}

	void addTry()
	{
		dataSets.push_back(DataSetsPerTry());
		tries++;
	}

};

#include "IO/LearningStateIO.hpp"

#endif
