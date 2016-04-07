#pragma once

#ifndef _ABSTRACTLEARNINGRULE_H_
#define _ABSTRACTLEARNINGRULE_H_

// Library Includes´
#include <EigenSrc/Dense>
#include <vector>
#include <map>
#include <memory>
#include <Logging/AbstractLogger.hpp>

// Includes
#include "ActivationOrder/AbstractActivationOrder.hpp"
#include "LearningState.hpp"

// Forward declarations
class AbstractNeuralNetwork;
class Teacher;
class Neuron;
class Edge;
class StandardNeuron;
class AbstractNeuron;
class StandardNeuron;
class AbstractTeachingLesson;
class AbstractNetworkTopology;

typedef std::vector<Eigen::VectorXd> ErrorMap_t;

#define DATA_SET_TRAINING_ERROR "Training error"


struct AbstractLearningRuleOptions
{
	// Sets the maximum iterations per try
	unsigned int maxIterationsPerTry;
	// Sets the maximum number of tries, until the algorithm should abort
	unsigned int maxTries;
	// Sets the highest total error value, when the algorithm should finish successful
	double totalErrorGoal;
	// Sets the lower limit of the random generated weights
	double minRandomWeightValue;
	// Sets the higher limit of the random generated weights
	double maxRandomWeightValue;
	// Sets the minium iterations per try
	unsigned int minIterationsPerTry;
	// Sets the maximum total error value (If a try has after its miniums iterations a greater total error value than the maxTotalErrorValue, skip that try)
	double maxTotalErrorValue;
	// Enable debug output
	AbstractLogger* logger;
	// Sets the debug output interval
	unsigned int debugOutputInterval;
	// Enable offline learning
	bool offlineLearning;
	// Can be used to prevent the learning rule to change the weights of the network before the learning begins
	bool changeWeightsBeforeLearning;
	AbstractLearningRuleOptions()
	{
		maxIterationsPerTry = 10000;
		maxTries = 100;
		totalErrorGoal = 0.01;
		minRandomWeightValue = -0.5f;
		maxRandomWeightValue = 0.5f;
		minIterationsPerTry = 1000;
		maxTotalErrorValue = 2;
		logger = NULL;
		debugOutputInterval = 1000;	
		offlineLearning = false;
		changeWeightsBeforeLearning = true;
	}
	virtual ~AbstractLearningRuleOptions() {}
};

// A LearningRule is used to improve a AbstractNeuralNetwork
class AbstractLearningRule 
{
	template <class Archive>
	friend void serialize(Archive& archive, AbstractLearningRule& learningRule);
private:
	bool pauseRequest;
protected:
	std::unique_ptr<AbstractLearningRuleOptions> options;
	// Holds the current total error
	double totalError;
	// Holds the current iteration
	unsigned int iteration;
	// Holds the current try number
	unsigned int tryCounter;
	// The current network 
	AbstractNeuralNetwork* currentNeuralNetwork;
	// The current network toplogy
	AbstractNetworkTopology* currentNetworkTopology;
	// The current teacher
	Teacher* currentTeacher;

	LearningState learningState;

	std::unique_ptr<AbstractActivationOrder> currentActivationOrder;
	// This method will be called in front of the actual learning algorithm
	virtual void initializeLearningAlgoritm(AbstractNeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder) {};
	// This method should calculate the deltaWeight for the actual edge
	virtual Eigen::MatrixXd calculateDeltaWeightFromLayer(AbstractTeachingLesson& lesson, int lessonIndex, int layerIndex, ErrorMap_t* errormap) = 0;
	// This method should adjust the weight of the current edge
	virtual void adjustWeights(int layerIndex, Eigen::MatrixXd gradients) = 0;
	// Calculate if it is sensible to continue learning
	virtual bool learningHasStopped() = 0;
	// This method could be used to do some work for the current neuron before calculating deltaWeights for every of its edges
	virtual void initializeLayerCalculation(AbstractTeachingLesson& lesson, int lessonIndex, int layerIndex, ErrorMap_t* errormap) {};
	// This method should return the used activationOrder
	virtual AbstractActivationOrder* getNewActivationOrder(AbstractNeuralNetwork &neuralNetwork) = 0;
	// Prints a current summary of the status of the learning process
	virtual std::string printDebugOutput() { return ""; };
	// This method should do something like randomizing all weight
	virtual void initializeTry(AbstractNeuralNetwork &neuralNetwork, Teacher &teacher) = 0;
	// This method can be used to do some work before every iteration
	virtual void initializeIteration(AbstractNeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder) { };
	// This method can be used to do some work before every teaching lesson
	virtual void initializeTeachingLesson(AbstractNeuralNetwork &neuralNetwork, AbstractTeachingLesson &teachingLesson) { };
	// This method could be used to do some work after all weights has been adjusted
	virtual void doCalculationAfterAllWeightAdjustments(AbstractNeuralNetwork &neuralNetwork) { };
	// This method could be used to do some work befora all weights are adjusted
	virtual void initializeAllWeightAdjustments(AbstractNeuralNetwork &neuralNetwork) { };
	// This method could be used to do some prework on the AbstractNeuralNetwork
	virtual AbstractNeuralNetwork* initializeNeuralNetwork(AbstractNeuralNetwork &neuralNetwork) { return &neuralNetwork; };
	// This method could be used to do some prework on the teacher
	virtual Teacher* initializeTeacher(Teacher &teacher) { return &teacher; };
	// This method could be used to do something after the learning process
	virtual void doCalculationAfterLearningProcess(AbstractNeuralNetwork &neuralNetwork, Teacher &teacher) {};
	// This method can return a pointer to a output value map, which should be filled before weight calculation
	virtual std::vector<std::map<AbstractNeuron*, double>>* getOutputValuesInTime() { return NULL; };
	// This method can return a pointer to a netInput value map, which should be filled before weight calculation
	virtual std::vector<std::map<AbstractNeuron*, double>>* getNetInputValuesInTime() { return NULL; };
	// This method should determine the start time and time step count of the next calculation
	virtual bool configureNextErroMapCalculation(int* nextStartTime, int* nextTimeStepCount, AbstractTeachingLesson& teachingLesson);

	void log(std::string message, LogLevel level);

	bool learn(bool resume);
public:	
	AbstractLearningRule(AbstractLearningRuleOptions* options_);
	// Execute the learning process on the given AbstractNeuralNetwork
	// If the learning process succeded the method will return true
	bool start(AbstractNeuralNetwork &neuralNetwork, Teacher &teacher);

	bool resume();

	void sendPauseRequest();

	void setCurrentNeuralNetwork(AbstractNeuralNetwork &neuralNetwork);

	void setCurrentTeacher(Teacher &teacher);

	void setLogger(AbstractLogger* logger);

	LearningState* getLearningState();

	static std::vector<std::string> getDataSetLabels();
};

#endif


