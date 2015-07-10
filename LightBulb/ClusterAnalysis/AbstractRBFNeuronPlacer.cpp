// Includes
#include "ClusterAnalysis\AbstractRBFNeuronPlacer.hpp"
#include "Teaching\Teacher.hpp"
#include "Teaching\AbstractTeachingLesson.hpp"
#include "NetworkTopology\RBFNetwork.hpp"
#include "ClusterAnalysis\Cluster.hpp"
#include "ClusterAnalysis\Point.hpp"
#include "ClusterAnalysis\PointSet.hpp"
#include "NeuralNetwork\NeuralNetworkIO.hpp"

std::unique_ptr<PointSet> AbstractRBFNeuronPlacer::getPointsFromTeachingLessons(Teacher &teacher, int inputDimension)
{
	// Create a new points list
	std::unique_ptr<PointSet> points(new PointSet());
		
	// Go through all teachingLessons and the corresponding points
	for (std::vector<std::unique_ptr<AbstractTeachingLesson>>::const_iterator teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++)
	{
		// Create a new point in the right dimension and with the same value as the current teachingInput
		Point* newPoint = new Point(std::vector<double>(inputDimension), (*(*teachingLesson)->getTeachingInput(NULL))[0]);
		// Go through all coordinates of the point
		std::vector<double>::iterator pointCoordinate = newPoint->valPos.position.begin();
		for (std::vector<double>::const_iterator teachingPattern = (*(*teachingLesson)->getTeachingPattern())[0].begin(); teachingPattern != (*(*teachingLesson)->getTeachingPattern())[0].end(); teachingPattern++, pointCoordinate++)
		{
			// Set the the teachingPattern of the current teachingLesson to the pointCoordinate
			*pointCoordinate = *teachingPattern;
		}
		// Add the point to the list
		points->push_back(newPoint);
	}

	// Make sure the max distances are calculated
	points->refreshMaxDistances();

	return points;
}

void AbstractRBFNeuronPlacer::placeRBFNeuronsFromClusters(std::list<Cluster>* clusters, RBFNetwork &neuralNetwork)
{
	// Go through all clusters
	int neuronIndex = 0;
	for (auto cluster = clusters->begin(); cluster != clusters->end(); cluster++, neuronIndex++)
	{
		// The cluster position will be the new center position of the neuron
		neuralNetwork.setCenterOfRBFNeuron(neuronIndex, (*cluster).center.position);
		// The cluster radius will be the width of the neuron
		neuralNetwork.setWidthOfRBFNeuron(neuronIndex, (*cluster).radius);
	}
}

