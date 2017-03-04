// Includes
#include "LightBulb/Learning/Reinforcement/AbstractReinforcementEnvironment.hpp"
#include "LightBulb/ActivationOrder/TopologicalOrder.hpp"
#include "LightBulb/NetworkTopology/FeedForwardNetworkTopology.hpp"
#include "LightBulb/NeuralNetwork/NeuralNetwork.hpp"
#include "LightBulb/Random/AbstractRandomGenerator.hpp"
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"
#include "LightBulb/LinearAlgebra/Kernel.hpp"

//Library include

namespace LightBulb
{
	AbstractReinforcementEnvironment::~AbstractReinforcementEnvironment() = default;


	void AbstractReinforcementEnvironment::initializeForLearning()
	{
	}

	void AbstractReinforcementEnvironment::setLearningState(LearningState& learningState_)
	{
		learningState = &learningState_;
	}
	
	std::vector<std::string> AbstractReinforcementEnvironment::getDataSetLabels() const
	{
		std::vector<std::string> labels;
		return labels;
	}
}
