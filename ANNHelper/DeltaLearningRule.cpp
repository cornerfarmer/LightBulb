#include "DeltaLearningRule.hpp"
#include "Teacher.hpp"
#include "TopologicalOrder.hpp"
#include "AbstractTeachingLesson.hpp"
#include "NeuralNetwork.hpp"
#include "AbstractNeuron.hpp"
#include "AbstractNetworkTopology.hpp"
#include "StandardNeuron.hpp"
#include "Edge.hpp"
#include "LayeredNetwork.hpp"
#include "RBFNetwork.hpp"

DeltaLearningRule::DeltaLearningRule(AbstractLearningRuleOptions &options_)
	: AbstractDeltaLearningRule(new AbstractLearningRuleOptions(options_)) 
{

}

void DeltaLearningRule::adjustWeight(Edge* edge, float deltaWeight)
{
	// Just add the weight
	edge->setWeight(edge->getWeight() - deltaWeight);
}

bool DeltaLearningRule::learningHasStopped()
{
	return false;
}