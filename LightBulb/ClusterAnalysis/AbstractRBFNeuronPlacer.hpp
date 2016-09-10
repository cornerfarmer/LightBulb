#pragma once

#ifndef _ABSTRACTRBFNEURONPLACER_H_
#define _ABSTRACTRBFNEURONPLACER_H_

// Library includes
#include <memory>
#include <vector>
#include <list>

namespace LightBulb
{
	// Forward declarations
	struct Cluster;
	struct Point;
	class RBFNetwork;
	class Teacher;
	class PointSet;
	class AbstractRandomGenerator;

	// This class contains all stuff needed to describe a RBFNeuronPlacer 
	class AbstractRBFNeuronPlacer
	{
	protected:
		AbstractRandomGenerator* randomGenerator;

		// Extract all teachingPatterns from all teachingLessons and put them into a vector of points
		std::unique_ptr<PointSet> getPointsFromTeachingLessons(Teacher &teacher, int inputDimension);
		// Replace all RBFNeurons of the given network with the help of the given clusters
		void placeRBFNeuronsFromClusters(std::list<Cluster>* clusters, RBFNetwork &neuralNetwork);
	public:
		// This method should execute the placing process
		virtual void doPlacing(RBFNetwork &neuralNetwork, Teacher &teacher) = 0;
		// Returns a copy of the object
		virtual AbstractRBFNeuronPlacer* getCopy() = 0;

		void setRandomGenerator(AbstractRandomGenerator* randomGenerator_);
	};
}

#endif