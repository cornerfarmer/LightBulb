#include <iostream>
#include <exception>
#include <vector>

#include "WeightedSumFunction.hpp"
#include "Edge.hpp"
#include "NeuralNetwork.hpp"
#include "LayeredNetwork.hpp"
#include "WeightedSumFunction.hpp"
#include "IdentityFunction.hpp"
#include "TopologicalOrder.hpp"
#include "BinaryFunction.hpp"
#include "SingleLayerPerceptronLearningRule.hpp"
#include "Teacher.hpp"
#include "TeachingLesson.hpp"

int main()
{
	LayeredNetworkOptions layeredNetworkOptions;
	layeredNetworkOptions.inputFunction = new WeightedSumFunction();
	layeredNetworkOptions.activationFunction = new BinaryFunction();
	layeredNetworkOptions.outputFunction = new IdentityFunction();
	layeredNetworkOptions.neuronsPerLayerCount = std::vector<int>(2);
	layeredNetworkOptions.neuronsPerLayerCount[0]=2;
	layeredNetworkOptions.neuronsPerLayerCount[1]=1;
	layeredNetworkOptions.useBiasNeurons = true;

	LayeredNetwork layeredNetwork(layeredNetworkOptions);

	NeuralNetwork neuralNetwork(&layeredNetwork);

	SingleLayerPerceptronLearningRule singleLayerPerceptronLearningRule;

	Teacher teacher;
	for (int i=0;i<2;i++)
	{
		for (int l=0;l<2;l++)
		{
			std::vector<float>* teachingPattern = new std::vector<float>(2);
			(*teachingPattern)[0] = i;
			(*teachingPattern)[1] = l;
			std::vector<float>* teachingInput= new std::vector<float>(1);
			(*teachingInput)[0] = (i == 1 || l == 1 ? 1 : 0);
			teacher.addTeachingLesson(new TeachingLesson(teachingPattern, teachingInput));
		}
	}
	singleLayerPerceptronLearningRule.doLearning(neuralNetwork, teacher);

	TopologicalOrder topologicalOrder;
	neuralNetwork.refreshAllNeurons(topologicalOrder);
	std::cout << "ANNHelper!";
	system("pause");
	return 0;
}