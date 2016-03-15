// Includes
#include "Learning/RBFInterpolationLearningRule.hpp"
#include "Teaching/Teacher.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "NetworkTopology/RBFNetwork.hpp"


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

void RBFInterpolationLearningRule::adjustWeights(int layerIndex, Eigen::MatrixXd gradients)
{
	if (layerIndex == currentNeuralNetwork->getNetworkTopology()->getLayerCount() - 1) {
		Eigen::MatrixXd newWeights = currentNetworkTopology->getAfferentWeightsPerLayer(layerIndex) + gradients;
		currentNetworkTopology->setAfferentWeightsPerLayer(layerIndex, newWeights);
	}
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
	
	// Initialize a matrix which will contain all outputValues from neurons in the first hidden layer in every teachingLesson
	m.reset(new MatrixXd(teacher.getTeachingLessons()->size(), rbfNetwork->getNeuronCountInLayer(1)));
	// Initialize a new matrx which will contain all teachingInput values from all output neurons
	t.reset(new MatrixXd(m->rows(), neuralNetwork.getNetworkTopology()->getOutputSize()));
	// Initialize a new vector which will contain all calculated weights
	w.reset(new MatrixXd(m->cols(), t->cols()));

	
}

AbstractActivationOrder* RBFInterpolationLearningRule::getNewActivationOrder(NeuralNetwork &neuralNetwork)
{
	return new TopologicalOrder();
}

Eigen::MatrixXd RBFInterpolationLearningRule::calculateDeltaWeightFromLayer(AbstractTeachingLesson& lesson, int lessonIndex, int layerIndex, ErrorMap_t* errormap)
{
	// Only change weights in the last layer
	if (lessonIndex == currentTeacher->getTeachingLessons()->size() - 1 && layerIndex == currentNeuralNetwork->getNetworkTopology()->getNeurons()->size() - 1)
		return (*w);
	else
		return Eigen::MatrixXd::Zero(w->rows(), w->cols());
}

void RBFInterpolationLearningRule::initializeLayerCalculation(class AbstractTeachingLesson& lesson, int lessonIndex, int layerIndex, ::ErrorMap_t* errormap)
{
	// Only change weights in the last layer
	if (layerIndex == currentNeuralNetwork->getNetworkTopology()->getLayerCount() - 1)
	{
		// Put the teachingInput concerning current neuron into the collumn of the current neuron in our t matrix
		for (int i = 0; i < t->cols(); i++) {
			(*t)(lessonIndex, i) = lesson.getTeachingInput(currentNeuralNetwork->getNetworkTopology()->getOutputActivationFunction())->get(0, i);
		}

		if (lessonIndex == t->rows() - 1)
		{
			// Do the magic: Multiplicate the inversed matrix with the techingInputs of the current neuron
			w.reset(new MatrixXd((*mInverse) * *t));
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

		neuralNetwork.getNetworkTopology()->getAfferentWeightsPerLayer(1).setZero();
	}

	// The TopologicalOrder will be our activationOrder
	TopologicalOrder activationOrder;

	// Go through every TeachingLesson
	for (int i = 0; i < m->rows(); i++)
	{
		// Try the teachingLesson
		(*teacher.getTeachingLessons())[i]->tryLesson(neuralNetwork, activationOrder);

		m->row(i) = (*rbfNetwork->getActivations())[0];
	}
	
	// If our matrix is a square matrix
	if (m->cols() == m->rows())
	{
		// Do a normal inversion
		mInverse.reset(new MatrixXd(m->inverse()));
	}
	else
	{
		mInverse.reset(new MatrixXd(m->rows(), m->cols()));
		// Create a jacobiSVD object
		Eigen::JacobiSVD<MatrixXd> jacobiSVD(*m, ComputeThinU | ComputeThinV);	
		// Do a pseudo inverse
		jacobiSVD.pinv(*mInverse);
	}
}

RBFInterpolationLearningRuleOptions* RBFInterpolationLearningRule::getOptions()
{
	return static_cast<RBFInterpolationLearningRuleOptions*>(options.get());
}