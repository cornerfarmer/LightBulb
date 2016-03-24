#pragma once

#ifndef _ABSTRACTTRAININGPLAN_H_
#define _ABSTRACTTRAININGPLAN_H_

// Library includes
#include <string>
#include <thread>
#include <vector>

// Forward declarations

class AbstractNeuralNetwork;

// A techer manages many techingLessons
class AbstractTrainingPlan
{
private:
	AbstractNeuralNetwork* network;
	std::thread thread;
	AbstractTrainingPlan* pattern;
protected:
	virtual void run() = 0;
	virtual AbstractTrainingPlan* getCopy() = 0;
public:
	void start(AbstractNeuralNetwork* network);
	virtual std::string getName() = 0;
	AbstractNeuralNetwork* getNeuralNetwork();
	virtual std::string getDescription() = 0;
	virtual std::string getLearningRateName() = 0;
	std::string getState();
	AbstractTrainingPlan* getCopyForExecute();
	AbstractTrainingPlan* getTrainingPlanPattern();
};

#endif
