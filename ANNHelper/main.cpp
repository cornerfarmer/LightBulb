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
#include "RBFInterpolationLearningRule.hpp"
#include "TeachingLessonLinearInput.hpp"
#include "ResilientDeltaLearningRule.hpp"
#include "KMeansRBFNeuronPlacer.hpp"
#include "KNearestRBFNeuronPlacer.hpp"
#include "ENearestRBFNeuronPlacer.hpp"
#include "RBFNetworkStructureChart.hpp"
#include "ROLFNeuronPlacer.hpp"

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

	ResilientBackpropagationLearningRuleOptions options;
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
			(*teachingPattern)[l] = (i == l ? 1.0f : 0.0f);
			(*teachingInput)[l] = (i == l);	
			//(*teachingInput)[0] = (i > 0.4 && i < 0.8  && l> 0.4 && l< 0.8 ? 1 : 0);			
		}
		teacher.addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));
	}


	bool success = learningRule.doLearning(neuralNetwork, teacher);
	////neuralNetwork.getNetworkTopology()->randomizeWeights(0,1);
	//

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

}

void doRBFTest()
{
	RBFNetwork* rbfNetwork = new RBFNetwork(2, 20, 1);

	NeuralNetwork neuralNetwork(rbfNetwork);

	Teacher teacher;
	for (int i=0;i<=20;i+=1)
	{
		for (int l=0;l<=20;l+=1)
		{	
			std::vector<float>* teachingPattern = new std::vector<float>(2);
			std::vector<float>* teachingInput= new std::vector<float>(1);

			(*teachingPattern)[0] = i;
			(*teachingPattern)[1] = l;
			(*teachingInput)[0] = (abs(i - 10) <= 5.5f &&  abs(l - 10) <= 5.5f);	
			//(*teachingInput)[0] = (i > l);	
			//(*teachingInput)[0] = (i > 0.4 && i < 0.8  && l> 0.4 && l< 0.8 ? 1 : 0);			

			teacher.addTeachingLesson(new TeachingLessonLinearInput(teachingPattern, teachingInput));
		}
	}

	RBFInterpolationLearningRuleOptions learningRuleOptions;
	learningRuleOptions.enableDebugOutput = true;
	learningRuleOptions.offlineLearning = true;
	learningRuleOptions.totalErrorGoal = 1;
	learningRuleOptions.maxTries = 1;
	learningRuleOptions.neuronPlacer = new ROLFNeuronPlacer();
	RBFInterpolationLearningRule learningRule(learningRuleOptions);

	learningRule.doLearning(neuralNetwork, teacher);	
	ResilientDeltaLearningRuleOptions delteLearningRuleOptions;
	delteLearningRuleOptions.maxIterationsPerTry = 100000;
	delteLearningRuleOptions.maxTries = 1000;
	delteLearningRuleOptions.enableDebugOutput = true;
	delteLearningRuleOptions.neuronPlacer = new KNearestRBFNeuronPlacer();
	ResilientDeltaLearningRule deltaLearningRule(delteLearningRuleOptions);

	//deltaLearningRule.doLearning(neuralNetwork, teacher);


	NeuralNetworkResultChartOptions neuralNetworkResultChartOptions;
	neuralNetworkResultChartOptions.neuralNetwork = &neuralNetwork;
	neuralNetworkResultChartOptions.binaryInterpretation = true;
	neuralNetworkResultChartOptions.activationOrder = new TopologicalOrder();
	neuralNetworkResultChartOptions.yRangeEnd = 20;
	neuralNetworkResultChartOptions.xRangeEnd = 20;
	NeuralNetworkResultChart neuralNetworkResultChart(0, 0, neuralNetworkResultChartOptions);
	neuralNetworkResultChart.recalculateAllValues();

	RBFNetworkStructureChartOptions rbfNetworkStructureChartOptions;
	rbfNetworkStructureChartOptions.rbfNetwork = static_cast<RBFNetwork*>(neuralNetwork.getNetworkTopology());
	rbfNetworkStructureChartOptions.yRangeEnd = 20;
	rbfNetworkStructureChartOptions.xRangeEnd = 20;
	RBFNetworkStructureChart rbfNetworkStructureChart(300, 0, rbfNetworkStructureChartOptions);
	rbfNetworkStructureChart.recalculateAllValues();


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
		rbfNetworkStructureChart.draw(window);
        window.display();
    }

}

int main()
{
	doRBFTest();
    return 0;
}