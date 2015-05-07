#include "AbstractRBFNeuronPlacer.hpp"
#include "Teacher.hpp"
#include "AbstractTeachingLesson.hpp"
#include "RBFNetwork.hpp"
#include "Cluster.hpp"
#include "Point.hpp"

std::unique_ptr<std::list<Point*>> AbstractRBFNeuronPlacer::getPointsFromTeachingLessons(Teacher &teacher, int inputDimension)
{
	// Create a new points vector with the length of the teachingLessons size (A point is also a vector with the size of inputDimension)
	std::unique_ptr<std::list<Point*>> points(new std::list<Point*>());
	
	
	// Go through all teachingLessons and the corresponding points
	for (std::vector<std::unique_ptr<AbstractTeachingLesson>>::const_iterator teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++)
	{
		Point* newPoint = new Point(std::vector<float>(inputDimension), std::vector<float>());
		// Go through all coordinates of the point
		std::vector<float>::iterator pointCoordinate = newPoint->position.begin();
		for (std::vector<float>::const_iterator teachingPattern = (*teachingLesson)->getTeachingPattern()->begin(); teachingPattern != (*teachingLesson)->getTeachingPattern()->end(); teachingPattern++, pointCoordinate++)
		{
			// Set the the teachingPattern of the current teachingLesson to the pointCoordinate
			*pointCoordinate = *teachingPattern;
		}
		newPoint->value = *(*teachingLesson)->getTeachingInput(NULL);
		points->push_back(newPoint);
	}

	return points;
}

void AbstractRBFNeuronPlacer::placeRBFNeuronsFromClusters(std::list<Cluster>* clusters, RBFNetwork &neuralNetwork)
{
	// Go through all clusters
	int neuronIndex = 0;
	for (std::list<Cluster>::iterator cluster = clusters->begin(); cluster != clusters->end(); cluster++, neuronIndex++)
	{
		// The cluster position will be the new center position of the neuron
		neuralNetwork.setCenterOfRBFNeuron(neuronIndex, (*cluster).position);
		// The cluster width will be the width of the neuron
		neuralNetwork.setWidthOfRBFNeuron(neuronIndex, (*cluster).width);
	}
}

