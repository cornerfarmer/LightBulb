#include "RBFInterpolationLearningRule.hpp"
#include "Teacher.hpp"
#include "TopologicalOrder.hpp"
#include "AbstractTeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "AbstractNeuron.hpp"
#include "AbstractNetworkTopology.hpp"
#include "StandardNeuron.hpp"
#include "Edge.hpp"
#include "RBFNetwork.hpp"
#include "RBFThreshold.hpp"


using namespace Eigen;

RBFInterpolationLearningRule::RBFInterpolationLearningRule(AbstractLearningRuleOptions &options_)
	: AbstractLearningRule(new AbstractLearningRuleOptions(options_)) 
{
	// Never do offlineLearning
	options->offlineLearning = false;
	// Do only one iteration
	options->maxIterationsPerTry = 1;
}

void RBFInterpolationLearningRule::adjustWeight(Edge* edge, float deltaWeight)
{
	// Set the calculated weight as new weight
	edge->setWeight(deltaWeight);
}

void RBFInterpolationLearningRule::printDebugOutput()
{
}

bool RBFInterpolationLearningRule::learningHasStopped()
{
	return false;
}

void RBFInterpolationLearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	actTeacher = &teacher;

	// Try to cast the given network as RBFNetwork
	RBFNetwork* rbfNetwork = dynamic_cast<RBFNetwork*>(neuralNetwork.getNetworkTopology());

	// Check if all given parameters are correct
	if (!rbfNetwork)
		throw std::invalid_argument("The given neuralNetwork has to contain a layeredNetworkTopology");
	
	// The TopologicalOrder will be our activationOrder
	TopologicalOrder activationOrder;

	// Get all output neurons
	std::vector<AbstractNeuron*>* outputNeurons = neuralNetwork.getNetworkTopology()->getOutputNeurons();

	// Initialize a matrix which will contain all outputValues from neurons in the second layer in every teachingLesson
	m.reset(new MatrixXf(teacher.getTeachingLessons()->size(), rbfNetwork->getNeuronsInLayer(1)->size()));
	// Initialize a new matrx which will contain all teachingInput values from all output neurons
	t.reset(new MatrixXf(m->rows(), neuralNetwork.getNetworkTopology()->getOutputNeurons()->size()));
	// Initialize a new vector which will contain all calculated weights
	w.reset(new VectorXf(m->cols()));

	rbfNetwork->randomizeCenters(0, 1);
	
	// Go through every TeachingLesson
	for (int i = 0; i < m->rows(); i++)
	{
		// Try the teachingLesson
		(*teacher.getTeachingLessons())[i]->tryLesson(neuralNetwork, activationOrder);

		// Go through every neuron in the second layer
		for (int j = 0; j != m->cols(); j++)
		{
			// Store the output of the neuron into our matrix
			(*m)(i, j) = (*rbfNetwork->getNeuronsInLayer(1))[j]->getActivation();
		}
	}
	
	// If our matrix is a square matrix
	if (m->cols() == m->rows())
	{
		// Do a normal inversion
		mInverse.reset(new MatrixXf(m->inverse()));
	}
	else
	{
		mInverse.reset(new MatrixXf(m->rows(), m->cols()));
		// Create a jacobiSVD object
		Eigen::JacobiSVD<MatrixXf> jacobiSVD(*m, ComputeThinU | ComputeThinV);	
		// Do a pseudo inverse
		jacobiSVD.pinv(*mInverse);
	}
}

AbstractActivationOrder* RBFInterpolationLearningRule::getNewActivationOrder()
{
	return new TopologicalOrder();
}

float RBFInterpolationLearningRule::calculateDeltaWeightFromEdge(Edge* edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, std::vector<float>* errorvector)
{
	// Only change weights in the last layer
	if (layerIndex == layerCount - 1)
		return (*w)[edgeIndex];
	else
		return 0;
}

void RBFInterpolationLearningRule::initializeNeuronWeightCalculation(StandardNeuron* neuron, int lessonIndex, int layerIndex, int neuronIndex, int layerCount, int neuronsInLayerCount, std::vector<float>* errorvector)
{
	// Only change weights in the last layer
	if (layerIndex == layerCount - 1)
	{
		// Put the teachingInput concerning current neuron into the collumn of the current neuron in our t matrix
		(*t)(lessonIndex, neuronIndex) = (*(*actTeacher->getTeachingLessons())[lessonIndex]->getTeachingInput(neuron->getActivationFunction()))[neuronIndex];
		
		if (lessonIndex == t->rows() - 1)
		{
			// Do the magic: Multiplicate the inversed matrix with the techingInputs of the current neuron
			w.reset(new VectorXf((*mInverse) * t->col(neuronIndex)));
		}
	}
}

void RBFInterpolationLearningRule::initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher)
{

}
