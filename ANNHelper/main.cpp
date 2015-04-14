#include <iostream>
#include <exception>
#include <vector>

#include "WeightedSumFunction.hpp"
#include "Edge.hpp"
#include "NeuralNetwork.hpp"
#include "LayeredNetwork.hpp"
#include "WeightedSumFunction.hpp"
#include "IdentityFunction.hpp"
#include "FermiFunction.hpp"
#include "TopologicalOrder.hpp"
#include "BinaryFunction.hpp"
#include "SingleLayerPerceptronLearningRule.hpp"
#include "DeltaLearningRule.hpp"
#include "BackpropagationLearningRule.hpp"
#include "ResilientBackpropagationLearningRule.hpp"
#include "Teacher.hpp"
#include "TeachingLesson.hpp"

int main()
{
	LayeredNetworkOptions layeredNetworkOptions;
	layeredNetworkOptions.inputFunction = new WeightedSumFunction();
	layeredNetworkOptions.activationFunction = new FermiFunction(1);
	layeredNetworkOptions.outputFunction = new IdentityFunction();
	layeredNetworkOptions.neuronsPerLayerCount = std::vector<int>(3);
	layeredNetworkOptions.neuronsPerLayerCount[0]=2;
	layeredNetworkOptions.neuronsPerLayerCount[1]=3;
	layeredNetworkOptions.neuronsPerLayerCount[2]=1;
	layeredNetworkOptions.useBiasNeurons = true;

	LayeredNetwork layeredNetwork(layeredNetworkOptions);

	NeuralNetwork neuralNetwork(&layeredNetwork);

	SingleLayerPerceptronLearningRule singleLayerPerceptronLearningRule;
	DeltaLearningRule deltaLearningRule;
	ResilientBackpropagationLearningRule resilientBackpropagationLearningRule(500, 20, 0.01f, -5, 5);

	Teacher teacher;
	for (int i=0;i<6;i++)
	{
		for (int l=0;l<6;l++)
		{
			std::vector<float>* teachingPattern = new std::vector<float>(2);
			(*teachingPattern)[0] = i;
			(*teachingPattern)[1] = l;
			std::vector<float>* teachingInput= new std::vector<float>(1);
			(*teachingInput)[0] = (i == l ? 1 : 0);
			teacher.addTeachingLesson(new TeachingLesson(teachingPattern, teachingInput));
		}
	}

	bool success = resilientBackpropagationLearningRule.doLearning(neuralNetwork, teacher);

	float totalError = teacher.getTotalError(neuralNetwork, TopologicalOrder());

	std::vector<float> teachingPattern(2);
	teachingPattern[0] = 100;
	teachingPattern[1] = 99;
	neuralNetwork.setInput(teachingPattern);
	neuralNetwork.refreshAllNeurons(TopologicalOrder());
	std::unique_ptr<std::vector<float>> outputVector = neuralNetwork.getOutput();

	
	TopologicalOrder topologicalOrder;
	neuralNetwork.refreshAllNeurons(topologicalOrder);
	std::cout << "ANNHelper!";
	system("pause");
	return 0;
}