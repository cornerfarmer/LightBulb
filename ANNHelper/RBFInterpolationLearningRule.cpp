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
#include "EigenSrc\Dense"
#include "EigenSrc\Jacobi"

using namespace Eigen;


bool RBFInterpolationLearningRule::doLearning(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	// Try to cast the given network as RBFNetwork
	RBFNetwork* rbfNetwork = dynamic_cast<RBFNetwork*>(neuralNetwork.getNetworkTopology());

	// Check if all given parameters are correct
	if (!rbfNetwork)
		throw std::invalid_argument("The given neuralNetwork has to contain a layeredNetworkTopology");
	if (teacher.getTeachingLessons()->size() == 0)
		throw std::invalid_argument("The given teacher does not contain any teachingLessons. So what should i learn??");

	// The TopologicalOrder will be our activationOrder
	TopologicalOrder activationOrder;

	// Get all output neurons
	std::vector<AbstractNeuron*>* outputNeurons = neuralNetwork.getNetworkTopology()->getOutputNeurons();

	// Initialize a matrix which will contain all outputValues from neurons in the second layer in every teachingLesson
	MatrixXf m(teacher.getTeachingLessons()->size(), rbfNetwork->getNeuronsInLayer(1)->size());
	// Initialize a new vector which will contain all teachingInput values from the current output neuron
	VectorXf t(m.rows());
	// Initialize a new vector which will contain all calculated weights
	VectorXf w(m.cols());

	// Go through every neuron in the second layer
	for (int j = 0; j != m.cols(); j++)
	{
		// Extract the center vector
		std::vector<float>* t = dynamic_cast<RBFThreshold*>((dynamic_cast<StandardNeuron*>((*rbfNetwork->getNeuronsInLayer(1))[j]))->getThreshold())->getCenterVector();
		// Put in random values
		(*t)[0] = (float)rand()/RAND_MAX * 1;
		(*t)[1] = (float)rand()/RAND_MAX * 1;
	}
	
	// Go through every TeachingLesson
	for (int i = 0; i < m.rows(); i++)
	{
		// Try the teachingLesson
		(*teacher.getTeachingLessons())[i]->tryLesson(neuralNetwork, activationOrder);

		// Go through every neuron in the second layer
		for (int j = 0; j != m.cols(); j++)
		{
			// Store the output of the neuron into our matrix
			m(i, j) = (*rbfNetwork->getNeuronsInLayer(1))[j]->getActivation();
		}
	}
	// This matrix will contain the inverse version of m
	MatrixXf mInverse;
	// If our matrix is a square matrix
	if (m.cols() == m.rows())
	{
		// Do a normal inversion
		mInverse = m.inverse();
	}
	else
	{
		// Create a jacobiSVD object
		Eigen::JacobiSVD<MatrixXf> jacobiSVD(m, ComputeThinU | ComputeThinV);	
		// Do a pseudo inverse
		jacobiSVD.pinv(mInverse);
	}

	// Go through all output neurons
	int outputNeuronIndex = 0;
	for (std::vector<AbstractNeuron*>::iterator outputNeuron = outputNeurons->begin(); outputNeuron != outputNeurons->end(); outputNeuron++, outputNeuronIndex++)
	{
		// Go through every TeachingLesson
		for (int i = 0; i < m.rows(); i++)
		{
			// Put the teachingInput concerning current neuron into the our t-vector
			t[i] = (*(*teacher.getTeachingLessons())[i]->getTeachingInput((dynamic_cast<StandardNeuron*>(*outputNeuron))->getActivationFunction()))[outputNeuronIndex];
		}

		// Do the magic: Multiplicate the inversed matrix with the techingInputs
		w = mInverse * t;

		std::vector<Edge*>* afferentEdges = (dynamic_cast<StandardNeuron*>(*outputNeuron))->getAfferentEdges();
		// Go through all afferentEdges of the actual neuron
		int edgeIndex = 0;
		for (std::vector<Edge*>::iterator edge = afferentEdges->begin(); edge != afferentEdges->end(); edge++, edgeIndex++)
		{					
			// Insert the calculated weight
			(*edge)->setWeight(w[edgeIndex]);					
		}		
	}

	return true;
}