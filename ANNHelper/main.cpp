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
#include "TeachingLesson.hpp"
#include "NeuralNetworkResultChart.hpp"
#include "DifferentFunctionsNeuronFactory.hpp"

int main()
{
	LayeredNetworkOptions layeredNetworkOptions;
	layeredNetworkOptions.neuronFactory = new DifferentFunctionsNeuronFactory(new WeightedSumFunction(), new HyperbolicTangentFunction(), new IdentityFunction(), 
																				new WeightedSumFunction(), new HyperbolicTangentFunction(), new IdentityFunction());
	layeredNetworkOptions.neuronsPerLayerCount = std::vector<int>(5);
	layeredNetworkOptions.neuronsPerLayerCount[0]=2;
	layeredNetworkOptions.neuronsPerLayerCount[1]=4;
	layeredNetworkOptions.neuronsPerLayerCount[2]=4;
	layeredNetworkOptions.neuronsPerLayerCount[3]=4;
	layeredNetworkOptions.neuronsPerLayerCount[4]=1;
	layeredNetworkOptions.useBiasNeurons = true;

	LayeredNetwork layeredNetwork(layeredNetworkOptions);

	NeuralNetwork neuralNetwork(&layeredNetwork);

	BackpropagationLearningRuleOptions options;
	options.enableDebugOutput = true;
	options.maxTotalErrorValue = 2;
	options.minIterationsPerTry = 3000;
	options.maxIterationsPerTry = 1000000;
	options.totalErrorGoal = 0.01f;
	ResilientBackpropagationLearningRule resilientBackpropagationLearningRule(options);

	Teacher teacher;
	for (float i=0.3;i<0.9;i+=0.05)
	{
		for (float l=0.3;l<0.9;l+=0.05)
		{
			std::vector<float>* teachingPattern = new std::vector<float>(2);
			(*teachingPattern)[0] = i;
			(*teachingPattern)[1] = l;
			std::vector<float>* teachingInput= new std::vector<float>(1);
			//(*teachingInput)[0] = (std::abs(i - 0.5) < 0.3 && std::abs(l - 0.5) < 0.3 ? 1 : 0);			
			(*teachingInput)[0] = (i > 0.4 && i < 0.8  && l> 0.4 && l< 0.8 ? 1 : 0);
			teacher.addTeachingLesson(new TeachingLesson(teachingPattern, teachingInput));
		}
	}

	bool success = resilientBackpropagationLearningRule.doLearning(neuralNetwork, teacher);
	//neuralNetwork.getNetworkTopology()->randomizeWeights(0,1);
	

	float totalError = teacher.getTotalError(neuralNetwork, TopologicalOrder());

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

    return 0;
}