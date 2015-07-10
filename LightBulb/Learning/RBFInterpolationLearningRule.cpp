#include "Learning\RBFInterpolationLearningRule.hpp"
#include "Teaching\Teacher.hpp"
#include "ActivationOrder\TopologicalOrder.hpp"
#include "Teaching\AbstractTeachingLesson.hpp"
#include "NeuralNetwork\NeuralNetwork.hpp"
#include "Neuron\AbstractNeuron.hpp"
#include "NetworkTopology\AbstractNetworkTopology.hpp"
#include "Neuron\StandardNeuron.hpp"
#include "Neuron\Edge.hpp"
#include "NetworkTopology\RBFNetwork.hpp"
#include "Neuron\RBFThreshold.hpp"


using namespace Eigen;

RBFInterpolationLearningRule::RBFInterpolationLearningRule(RBFInterpolationLearningRuleOptions &options_)
	: AbstractLearningRule(new RBFInterpolationLearningRuleOptions(options_)) 
{
	// Check if all given parameters are correct
	if (!getOptions()->neuronPlacer)
		throw new std::invalid_argument("The neuronPlacer in the given options cannot be null");

	// Never do offlineLearning
	options->offlineLearning = false;
	// Do only one iteration
	options->maxIterationsPerTry = 1;
}

void RBFInterpolationLearningRule::adjustWeight(Edge* edge, double deltaWeight)
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

void RBFInterpolationLearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher, AbstractActivationOrder &activationOrder)
{
	actTeacher = &teacher;

	// Try to cast the given network as RBFNetwork
	RBFNetwork* rbfNetwork = dynamic_cast<RBFNetwork*>(neuralNetwork.getNetworkTopology());

	// Check if all given parameters are correct
	if (!rbfNetwork)
		throw std::invalid_argument("The given neuralNetwork has to contain a layeredNetworkTopology");
	
	// Get all output neurons
	std::vector<StandardNeuron*>* outputNeurons = neuralNetwork.getNetworkTopology()->getOutputNeurons();

	// Initialize a matrix which will contain all outputValues from neurons in the first hidden layer in every teachingLesson
	m.reset(new MatrixXf(teacher.getTeachingLessons()->size(), rbfNetwork->getNeurons()->front().size()));
	// Initialize a new matrx which will contain all teachingInput values from all output neurons
	t.reset(new MatrixXf(m->rows(), neuralNetwork.getNetworkTopology()->getOutputNeurons()->size()));
	// Initialize a new vector which will contain all calculated weights
	w.reset(new VectorXf(m->cols()));

	
}

AbstractActivationOrder* RBFInterpolationLearningRule::getNewActivationOrder(NeuralNetwork &neuralNetwork)
{
	return new TopologicalOrder();
}

double RBFInterpolationLearningRule::calculateDeltaWeightFromEdge(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, Edge& edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, ErrorMap_t* errormap)
{
	// Only change weights in the last layer
	if (layerIndex == currentNeuralNetwork->getNetworkTopology()->getNeurons()->size() - 1)
		return (*w)[edgeIndex];
	else
		return 0;
}

void RBFInterpolationLearningRule::initializeNeuronWeightCalculation(AbstractTeachingLesson& lesson, std::vector<StandardNeuron*>& layer, StandardNeuron& neuron, int lessonIndex, int layerIndex, int neuronIndex, ErrorMap_t* errormap)
{
	// Only change weights in the last layer
	if (layerIndex == currentNeuralNetwork->getNetworkTopology()->getNeurons()->size() - 1)
	{
		// Put the teachingInput concerning current neuron into the collumn of the current neuron in our t matrix
		(*t)(lessonIndex, neuronIndex) = (float)(*lesson.getTeachingInput(neuron.getActivationFunction()))[0][neuronIndex];
		
		if (lessonIndex == t->rows() - 1)
		{
			// Do the magic: Multiplicate the inversed matrix with the techingInputs of the current neuron
			w.reset(new VectorXf((*mInverse) * t->col(neuronIndex)));
		}
	}
}

void RBFInterpolationLearningRule::initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	RBFNetwork* rbfNetwork = dynamic_cast<RBFNetwork*>(neuralNetwork.getNetworkTopology());

	if (options->changeWeightsBeforeLearning)
	{
		// Replace all RBFNeurons with the help of the choosen neuronPlacer
		getOptions()->neuronPlacer->doPlacing(*rbfNetwork, teacher);
	}

	// The TopologicalOrder will be our activationOrder
	TopologicalOrder activationOrder;

	// Go through every TeachingLesson
	for (int i = 0; i < m->rows(); i++)
	{
		// Try the teachingLesson
		(*teacher.getTeachingLessons())[i]->tryLesson(neuralNetwork, activationOrder);

		// Go through every neuron in the second layer
		for (int j = 0; j != m->cols(); j++)
		{
			// Store the output of the neuron into our matrix
			(*m)(i, j) = (float)rbfNetwork->getNeurons()->front()[j]->getActivation();
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

RBFInterpolationLearningRuleOptions* RBFInterpolationLearningRule::getOptions()
{
	return static_cast<RBFInterpolationLearningRuleOptions*>(options.get());
}