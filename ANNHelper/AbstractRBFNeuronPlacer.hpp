#pragma once

#ifndef _ABSTRACTRBFNEURONPLACER_H_
#define _ABSTRACTRBFNEURONPLACER_H_

// Library includes
#include <memory>
#include <vector>

// Forward declarations
struct Cluster;
struct Point;
class RBFNetwork;
class Teacher;

// This class contains all stuff needed to describe a RBFNeuronPlacer 
class AbstractRBFNeuronPlacer 
{
protected:
	// Extract all teachingPatterns from all teachingLessons and put them into a vector of points
	std::unique_ptr<std::vector<Point>> getPointsFromTeachingLessons(Teacher &teacher, int inputDimension);
	// Replace all RBFNeurons of the given network with the help of the given clusters
	void placeRBFNeuronsFromClusters(std::vector<Cluster>* clusters, RBFNetwork &neuralNetwork);
public:
	// This method should execute the placing process
	virtual void doPlacing(RBFNetwork &neuralNetwork, Teacher &teacher) = 0;
	// Returns a copy of the object
	virtual AbstractRBFNeuronPlacer* getCopy() = 0;
};

#endif