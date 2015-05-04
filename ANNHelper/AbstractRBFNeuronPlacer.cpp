#include "AbstractRBFNeuronPlacer.hpp"
#include "Teacher.hpp"
#include "AbstractTeachingLesson.hpp"
#include "RBFNetwork.hpp"
#include "Cluster.hpp"

std::unique_ptr<std::vector<std::vector<float>>> AbstractRBFNeuronPlacer::getPointsFromTeachingLessons(Teacher &teacher, int inputDimension)
{
	// Create a new points vector with the length of the teachingLessons size (A point is also a vector with the size of inputDimension)
	std::unique_ptr<std::vector<std::vector<float>>> points(new std::vector<std::vector<float>>(teacher.getTeachingLessons()->size(), std::vector<float>(inputDimension)));
	
	// Go through all teachingLessons and the corresponding points
	std::vector<std::vector<float>>::iterator point = points->begin();
	for (std::vector<std::unique_ptr<AbstractTeachingLesson>>::const_iterator teachingLesson = teacher.getTeachingLessons()->begin(); teachingLesson != teacher.getTeachingLessons()->end(); teachingLesson++, point++)
	{
		// Go through all coordinates of the point
		std::vector<float>::iterator pointCoordinate = (*point).begin();
		for (std::vector<float>::const_iterator teachingPattern = (*teachingLesson)->getTeachingPattern()->begin(); teachingPattern != (*teachingLesson)->getTeachingPattern()->end(); teachingPattern++, pointCoordinate++)
		{
			// Set the the teachingPattern of the current teachingLesson to the pointCoordinate
			*pointCoordinate = *teachingPattern;
		}
	}

	return points;
}

void AbstractRBFNeuronPlacer::placeRBFNeuronsFromClusters(std::vector<Cluster>* clusters, RBFNetwork &neuralNetwork)
{
	// Go through all clusters
	int neuronIndex = 0;
	for (std::vector<Cluster>::iterator cluster = clusters->begin(); cluster != clusters->end(); cluster++, neuronIndex++)
	{
		// The cluster position will be the new center position of the neuron
		neuralNetwork.setCenterOfRBFNeuron(neuronIndex, (*cluster).position);
		// The cluster width will be the width of the neuron
		neuralNetwork.setWidthOfRBFNeuron(neuronIndex, (*cluster).width);
	}
}

