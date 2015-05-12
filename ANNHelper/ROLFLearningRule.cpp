#include "ROLFLearningRule.hpp"
#include "Teacher.hpp"
#include "TopologicalOrder.hpp"
#include "AbstractTeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "AbstractNeuron.hpp"
#include "AbstractNetworkTopology.hpp"
#include "StandardNeuron.hpp"
#include "Edge.hpp"
#include "LayeredNetwork.hpp"
#include "RBFThreshold.hpp"
#include "RBFNetwork.hpp"

ROLFLearningRule::ROLFLearningRule(ROLFLearningRuleOptions &options_)
	: AbstractLearningRule(new ROLFLearningRuleOptions(options_)) 
{
	getOptions()->offlineLearning = false;
	lerningHasStopped = false;
}

void ROLFLearningRule::adjustWeight(Edge* edge, float deltaWeight)
{
}

bool ROLFLearningRule::learningHasStopped()
{
	return lerningHasStopped;
}

void ROLFLearningRule::initializeLearningAlgoritm(NeuralNetwork &neuralNetwork, Teacher &teacher)
{
	// Check if all given parameters are correct


	currentTeacher = &teacher;
	currentNeuralNetwork = &neuralNetwork;
}

AbstractActivationOrder* ROLFLearningRule::getNewActivationOrder()
{
	return new TopologicalOrder();
}

float ROLFLearningRule::calculateDeltaWeightFromEdge(Edge* edge, int lessonIndex, int layerIndex, int neuronIndex, int edgeIndex, int layerCount, int neuronsInLayerCount, std::vector<float>* errorVector)
{
	return 0;
}

void ROLFLearningRule::initializeTry(NeuralNetwork &neuralNetwork, Teacher &teacher)
{

}

void ROLFLearningRule::initializeNeuronWeightCalculation(StandardNeuron* neuron, int lessonIndex, int layerIndex, int neuronIndex, int layerCount, int neuronsInLayerCount, std::vector<float>* errorvector)
{
	static StandardNeuron* nearestNeuron;
	if (layerIndex == 1)
	{
		if (neuronIndex == 0)
		{
			nearestNeuron = NULL;
			lerningHasStopped = true;
		}

		RBFThreshold& threshold = static_cast<RBFThreshold&>(*neuron->getThreshold());

		if (neuron->getNetInput() < threshold.getWidth())
		{
			if (nearestNeuron == NULL || nearestNeuron->getActivation() < neuron->getActivation())
			{
				nearestNeuron = neuron;
			}
		}

		if (neuronIndex == neuronsInLayerCount - 1)
		{
			std::vector<float>& currentTeachingPattern = *(*currentTeacher->getTeachingLessons())[lessonIndex]->getTeachingPattern();
			if (nearestNeuron)
			{
				RBFThreshold& nearestNeuronthreshold = static_cast<RBFThreshold&>(*nearestNeuron->getThreshold());

				std::vector<float>& center = *nearestNeuronthreshold.getCenterVector();
				for (int i = 0; i < center.size(); i++)
				{
					center[i] = center[i] + getOptions()->centerLearningRate * (currentTeachingPattern[i] - center[i]);
				}

				nearestNeuronthreshold.setWidth((nearestNeuronthreshold.getWidth() / getOptions()->widthMultiplier + getOptions()->widthLearningRate * (getDistanceBetweenPositions(currentTeachingPattern, center) - nearestNeuronthreshold.getWidth() / getOptions()->widthMultiplier)) * getOptions()->widthMultiplier);
			}
			else
			{
				StandardNeuron* newNeuron = static_cast<StandardNeuron*>(currentNeuralNetwork->getNetworkTopology()->addNeuronIntoLayer(layerIndex));

				RBFThreshold& newNeuronthreshold = static_cast<RBFThreshold&>(*newNeuron->getThreshold());

				newNeuronthreshold.setCenterVector(currentTeachingPattern);
				newNeuronthreshold.setWidth(1.5f);

				lerningHasStopped = false;
			}
		}
	}
}

ROLFLearningRuleOptions* ROLFLearningRule::getOptions()
{
	return static_cast<ROLFLearningRuleOptions*>(options.get());
}
