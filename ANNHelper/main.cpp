#include <iostream>
#include <exception>
#include <vector>
#include <SFML\Graphics.hpp>

#include "WeightedSumFunction.hpp"
#include "Edge.hpp"
#include "NeuralNetwork.hpp"
#include "LayeredNetwork.hpp"
#include "WeightedSumFunction.hpp"
#include "IdentityFunction.hpp"
#include "HyperbolicTangentFunction.hpp"
#include "FermiFunction.hpp"
#include "TopologicalOrder.hpp"
#include "BinaryFunction.hpp"
#include "SingleLayerPerceptronLearningRule.hpp"
#include "DeltaLearningRule.hpp"
#include "BackpropagationLearningRule.hpp"
#include "ResilientBackpropagationLearningRule.hpp"
#include "Teacher.hpp"
#include "TeachingLessonBooleanInput.hpp"
#include "NeuralNetworkResultChart.hpp"
#include "DifferentFunctionsNeuronFactory.hpp"
#include "StandardThreshold.hpp"
#include "RBFNetwork.hpp"

void doPerceptronTest()
{
	LayeredNetworkOptions layeredNetworkOptions;
	layeredNetworkOptions.neuronFactory = new DifferentFunctionsNeuronFactory(new StandardThreshold(0), new WeightedSumFunction(), new FermiFunction(1), new IdentityFunction(), 
																				new StandardThreshold(0), new WeightedSumFunction(), new FermiFunction(1), new IdentityFunction());
	layeredNetworkOptions.neuronsPerLayerCount = std::vector<unsigned int>(3);
	layeredNetworkOptions.neuronsPerLayerCount[0]=8;
	layeredNetworkOptions.neuronsPerLayerCount[1]=3;
	layeredNetworkOptions.neuronsPerLayerCount[2]=8;
	layeredNetworkOptions.useBiasNeurons = true;

	LayeredNetwork* layeredNetwork = new LayeredNetwork(layeredNetworkOptions);

	NeuralNetwork neuralNetwork(layeredNetwork);

	BackpropagationLearningRuleOptions options;
	options.enableDebugOutput = true;
	options.debugOutputInterval = 100;
	options.maxTotalErrorValue = 50;
	options.minIterationsPerTry = 3000;
	options.maxIterationsPerTry = 1000000;
	options.totalErrorGoal = 0.01f;
	options.maxTries = 1000;
	options.minRandomWeightValue = -0.5;
	options.maxRandomWeightValue = 0.5;
  	options.weightDecayFac = 0;
	ResilientBackpropagationLearningRule learningRule(options);

	Teacher teacher;
	for (int i=0;i<8;i+=1)
	{
		std::vector<float>* teachingPattern = new std::vector<float>(8);
		std::vector<bool>* teachingInput= new std::vector<bool>(8);
		for (int l=0;l<8;l+=1)
		{			
			(*teachingPattern)[l] = (i == l ? 1 : 0);
			(*teachingInput)[l] = (i == l);	
			//(*teachingInput)[0] = (i > 0.4 && i < 0.8  && l> 0.4 && l< 0.8 ? 1 : 0);			
		}
		teacher.addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));
	}


	bool success = learningRule.doLearning(neuralNetwork, teacher);
	////neuralNetwork.getNetworkTopology()->randomizeWeights(0,1);
	//

	float totalError = teacher.getTotalError(neuralNetwork, TopologicalOrder(), 0);

	std::vector<float> teachingPattern(2);
	teachingPattern[0] = 100;
	teachingPattern[1] = 100;
	neuralNetwork.setInput(teachingPattern);
	neuralNetwork.refreshAllNeurons(TopologicalOrder());
	std::unique_ptr<std::vector<float>> outputVector = neuralNetwork.getOutput();


	NeuralNetworkResultChartOptions neuralNetworkResultChartOptions;
	neuralNetworkResultChartOptions.neuralNetwork = &neuralNetwork;
	neuralNetworkResultChartOptions.binaryInterpretation = false;
	neuralNetworkResultChartOptions.activationOrder = new TopologicalOrder();
	
	NeuralNetworkResultChart neuralNetworkResultChart(0, 0, neuralNetworkResultChartOptions);
	neuralNetworkResultChart.recalculateAllValues();
	sf::RenderWindow window(sf::VideoMode(800, 600), "ANNHelper!");

	while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        neuralNetworkResultChart.draw(window);
        window.display();
    }

}

void doRBFTest()
{
	RBFNetwork* rbfNetwork = new RBFNetwork(3, 2, 3);

	NeuralNetwork neuralNetwork(rbfNetwork);
}

int main()
{
	while (true)
	doRBFTest();
    return 0;
}