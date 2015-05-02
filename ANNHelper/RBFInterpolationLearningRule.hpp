#pragma once

#ifndef _RBFINTERPOLATIONLEARNINGRULE_H_
#define _RBFINTERPOLATIONLEARNINGRULE_H_

// Library Includes
#include "EigenSrc\Dense"
#include "EigenSrc\Jacobi"

// Includes
#include "AbstractLearningRule.hpp"

// Forward declarations
class NeuralNetwork;
class Teacher;


// The DeltaLearningRule can only be used to train SingleLayerPerceptronNetworks
class RBFInterpolationLearningRule : public AbstractLearningRule
{
private:
	// A matrix which will contain all outputValues from neurons in the second layer in every teachingLesson
	std::unique_ptr<Eigen::MatrixXf> m;
	// Inversion of m
	std::unique_ptr<Eigen::MatrixXf> mInverse;
	// A matrx which will contain all teachingInput values from all output neurons
	std::unique_ptr<Eigen::MatrixXf> t;
	// A vector which will contain all calculated weights
	std::unique_ptr<Eigen::VectorXf> w;	
	// Holds the actual teacher
	Teacher* actTeacher;
protected:
	// Inherited:
	void adjustWeight(Edge* edge, float deltaWeight);
	void printDebugOutput();
	bool learningHasStopped();
	void initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher);
	AbstractActivationOrder* getNewActivationOrder();
	float calculateDeltaWeightFromEdge(Edge* edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, std::vector<float>* errorvector);
	void initializeNeuronWeightCalculation(StandardNeuron* neuron, int lessonIndex, int layerIndex, int neuronIndex, int layerCount, int neuronsInLayerCount, std::vector<float>* errorvector);
public:
	RBFInterpolationLearningRule(AbstractLearningRuleOptions &options_);
};

#endif