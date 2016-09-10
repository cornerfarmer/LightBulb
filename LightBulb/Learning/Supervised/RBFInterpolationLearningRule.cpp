// Includes
#include "Learning/Supervised/RBFInterpolationLearningRule.hpp"
#include "Teaching/Teacher.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "Teaching/AbstractTeachingLesson.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/AbstractNetworkTopology.hpp"
#include "NetworkTopology/RBFNetwork.hpp"
#include "NeuronDescription/NeuronDescription.hpp"

using namespace Eigen;

namespace LightBulb
{

	RBFInterpolationLearningRule::RBFInterpolationLearningRule(RBFInterpolationLearningRuleOptions &options_)
		: AbstractSupervisedLearningRule(new RBFInterpolationLearningRuleOptions(options_))
	{
		// Check if all given parameters are correct
		if (!getOptions()->neuronPlacer)
			throw new std::invalid_argument("The neuronPlacer in the given options cannot be null");

		getOptions()->neuronPlacer->setRandomGenerator(randomGenerator.get());
		// Never do offlineLearning
		getOptions()->offlineLearning = false;
		// Do only one iteration
		options->maxIterationsPerTry = 1;
	}

	std::string RBFInterpolationLearningRule::getName()
	{
		return "RBFInterpolationLearningRule";
	}

	void RBFInterpolationLearningRule::adjustWeights(int layerIndex, Eigen::MatrixXd gradients)
	{
		if (layerIndex == getCurrentNetworkTopology()->getLayerCount() - 1) {
			Eigen::MatrixXd newWeights = getCurrentNetworkTopology()->getAfferentWeightsPerLayer(layerIndex) + gradients;
			getCurrentNetworkTopology()->setAfferentWeightsPerLayer(layerIndex, newWeights);
		}
	}

	bool RBFInterpolationLearningRule::learningHasStopped()
	{
		return false;
	}

	void RBFInterpolationLearningRule::initializeStartLearningAlgoritm()
	{
		AbstractSupervisedLearningRule::initializeStartLearningAlgoritm();

		// Try to cast the given network as RBFNetwork
		RBFNetwork* rbfNetwork = dynamic_cast<RBFNetwork*>(getCurrentNetworkTopology());

		// Check if all given parameters are correct
		if (!rbfNetwork)
			throw std::invalid_argument("The given neuralNetwork has to contain a FeedForwardNetworkTopologyTopology");

		// Initialize a matrix which will contain all outputValues from neurons in the first hidden layer in every teachingLesson
		m.reset(new MatrixXd(getOptions()->teacher->getTeachingLessons()->size(), rbfNetwork->getNeuronCountsPerLayer()[1]));
		// Initialize a new matrx which will contain all teachingInput values from all output neurons
		t.reset(new MatrixXd(m->rows(), getOptions()->neuralNetwork->getNetworkTopology()->getOutputSize()));
		// Initialize a new vector which will contain all calculated weights
		w.reset(new MatrixXd(getOptions()->neuralNetwork->getNetworkTopology()->getOutputSize(), rbfNetwork->getNeuronCountsPerLayer()[1]));


	}

	AbstractActivationOrder* RBFInterpolationLearningRule::getNewActivationOrder()
	{
		return new TopologicalOrder();
	}

	std::vector<Eigen::MatrixXd> RBFInterpolationLearningRule::calculateDeltaWeight(AbstractTeachingLesson& lesson, int lessonIndex, ErrorMap_t* errormap)
	{
		std::vector<Eigen::MatrixXd> deltaWeight(getCurrentNetworkTopology()->getLayerCount() - 1);
		for (int layerIndex = getCurrentNetworkTopology()->getLayerCount() - 1; layerIndex > 0; layerIndex--) {

			// Only change weights in the last layer
			if (layerIndex == getCurrentNetworkTopology()->getLayerCount() - 1)
			{
				// Put the teachingInput concerning current neuron into the collumn of the current neuron in our t matrix
				for (int i = 0; i < t->cols(); i++) {
					(*t)(lessonIndex, i) = lesson.getTeachingInput(getCurrentNetworkTopology()->getOutputNeuronDescription()->getActivationFunction())->get(0, i);
				}

				if (lessonIndex == t->rows() - 1)
				{
					// Do the magic: Multiplicate the inversed matrix with the techingInputs of the current neuron
					w.reset(new MatrixXd(((*mInverse) * *t).transpose()));
				}
			}

			// Only change weights in the last layer
			if (lessonIndex == getOptions()->teacher->getTeachingLessons()->size() - 1 && layerIndex == getCurrentNetworkTopology()->getLayerCount() - 1)
				deltaWeight[layerIndex - 1] = (*w);
			else
				deltaWeight[layerIndex - 1] = Eigen::MatrixXd::Zero(w->rows(), w->cols());
		}
		return deltaWeight;
	}

	void RBFInterpolationLearningRule::initializeTry()
	{
		RBFNetwork* rbfNetwork = dynamic_cast<RBFNetwork*>(getCurrentNetworkTopology());

		if (getOptions()->changeWeightsBeforeLearning)
		{
			// Replace all RBFNeurons with the help of the choosen neuronPlacer
			getOptions()->neuronPlacer->doPlacing(*rbfNetwork, *getOptions()->teacher);

			getCurrentNetworkTopology()->getAfferentWeightsPerLayer(1).setZero();
		}

		// The TopologicalOrder will be our activationOrder
		TopologicalOrder activationOrder;

		// Go through every TeachingLesson
		for (int i = 0; i < m->rows(); i++)
		{
			// Try the teachingLesson
			(*getOptions()->teacher->getTeachingLessons())[i]->tryLesson(*getOptions()->neuralNetwork, activationOrder);

			m->row(i) = *(*rbfNetwork->getAllActivations())[1];
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
}