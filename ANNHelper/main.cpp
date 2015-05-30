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
#include "NeuralNetworkIO.hpp"
#include "RecurrentLayeredNetwork.hpp"
#include "BackpropagationThroughTimeLearningRule.hpp"
#include "NetworkTopologyDrawer.hpp"

void doPerceptronTest()
{
	LayeredNetworkOptions layeredNetworkOptions;
	layeredNetworkOptions.neuronFactory = new DifferentFunctionsNeuronFactory(new StandardThreshold(0), new WeightedSumFunction(), new FermiFunction(1), new IdentityFunction(), 
																				new StandardThreshold(0), new WeightedSumFunction(), new FermiFunction(1), new IdentityFunction());
	layeredNetworkOptions.neuronsPerLayerCount = std::vector<unsigned int>(3);
	layeredNetworkOptions.neuronsPerLayerCount[0]=2;
	layeredNetworkOptions.neuronsPerLayerCount[1]=3;
	layeredNetworkOptions.neuronsPerLayerCount[2]=1;
	layeredNetworkOptions.useBiasNeuron = true;

	LayeredNetwork* layeredNetwork = new LayeredNetwork(layeredNetworkOptions);

	NeuralNetwork neuralNetwork(layeredNetwork);

	BackpropagationLearningRuleOptions options;
	options.enableDebugOutput = true;
	options.debugOutputInterval = 100;
	options.maxTotalErrorValue = 4;
	options.minIterationsPerTry = 3000;
	options.maxIterationsPerTry = 1000000;
	options.totalErrorGoal = 0.001f;
	options.maxTries = 1000;
	options.minRandomWeightValue = -0.5;
	options.maxRandomWeightValue = 0.5;
  	options.weightDecayFac = 0;
	options.resilientLearningRate = true;
	BackpropagationLearningRule learningRule(options);

	Teacher teacher;
	for (int i=0;i<8;i+=1)
	{
		for (int l=0;l<8;l+=1)
		{			
			NeuralNetworkIO* teachingPattern = new NeuralNetworkIO();
			std::vector<bool>* teachingInput= new std::vector<bool>(1);

			teachingPattern->push_back(std::vector<float>(2));
			teachingPattern->back()[0] = i;
			teachingPattern->back()[1] = l;
			(*teachingInput)[0] = (i == l);	
			//(*teachingInput)[0] = (i > 0.4 && i < 0.8  && l> 0.4 && l< 0.8 ? 1 : 0);
			teacher.addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));
		}
	}

	//for (float i=0;i<1;i+=0.2)
	//{		
	//	for (float l=0;l<1;l+=0.2)
	//	{			
	//		NeuralNetworkIO* teachingPattern = new NeuralNetworkIO();
	//		std::vector<bool>* teachingInput= new std::vector<bool>(1);

	//		teachingPattern->push_back(std::vector<float>(2));
	//		teachingPattern->back()[0] = i;
	//		teachingPattern->back()[1] = l;
	//		(*teachingInput)[0] = (i == l);	
	//		//(*teachingInput)[0] = (i > 0.4 && i < 0.8  && l> 0.4 && l< 0.8 ? 1 : 0);			
	//		teacher.addTestingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));
	//	}		
	//}
	//{
	//NeuralNetworkIO* teachingPattern = new NeuralNetworkIO();
	//std::vector<bool>* teachingInput= new std::vector<bool>(1);

	//teachingPattern->push_back(std::vector<float>(2));
	//teachingPattern->back()[0] = 100;
	//teachingPattern->back()[1] = 100;
	//(*teachingInput)[0] = true;	
	////(*teachingInput)[0] = (i > 0.4 && i < 0.8  && l> 0.4 && l< 0.8 ? 1 : 0);			
	//teacher.addTestingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));
	//}

	bool success = learningRule.doLearning(neuralNetwork, teacher);
	////neuralNetwork.getNetworkTopology()->randomizeWeights(0,1);
	//

	float totalError = teacher.getTotalError(neuralNetwork, TopologicalOrder());

	NeuralNetworkIO* teachingPattern = new NeuralNetworkIO();
	teachingPattern->push_back(std::vector<float>(2));
	teachingPattern->back()[0] = 8;
	teachingPattern->back()[1] = 8;

	std::unique_ptr<NeuralNetworkIO> outputVector = neuralNetwork.calculate(*teachingPattern, TopologicalOrder());
	

	NeuralNetworkResultChartOptions neuralNetworkResultChartOptions;
	neuralNetworkResultChartOptions.neuralNetwork = &neuralNetwork;
	neuralNetworkResultChartOptions.binaryInterpretation = true;
	neuralNetworkResultChartOptions.xRangeEnd = 100;
	neuralNetworkResultChartOptions.yRangeEnd = 100;
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
	RBFNetwork* rbfNetwork = new RBFNetwork(2, 2, 1);

	NeuralNetwork neuralNetwork(rbfNetwork);

	Teacher teacher;
	for (int i=0;i<=20;i+=1)
	{
		for (int l=0;l<=20;l+=1)
		{	
			NeuralNetworkIO* teachingPattern = new NeuralNetworkIO();
			std::vector<float>* teachingInput= new std::vector<float>(1);

			teachingPattern->push_back(std::vector<float>(2));
			teachingPattern->back()[0] = i;
			teachingPattern->back()[1] = l;
			(*teachingInput)[0] = (abs(i - 0) <= 5.5f &&  abs(l - 0) <= 5.5f) || (abs(i - 20) <= 5.5f &&  abs(l - 20) <= 5.5f);	
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
	delteLearningRuleOptions.maxTries = 1;
	delteLearningRuleOptions.maxTotalErrorValue = 10;
	delteLearningRuleOptions.enableDebugOutput = true;
	delteLearningRuleOptions.changeWeightsBeforeLearning = false;
	ResilientDeltaLearningRule deltaLearningRule(delteLearningRuleOptions);

	deltaLearningRule.doLearning(neuralNetwork, teacher);


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

void doRecurrentLayeredNetworkTest()
{
	RecurrentLayeredNetworkOptions networkOptions;
	networkOptions.neuronFactory = new DifferentFunctionsNeuronFactory(new StandardThreshold(0), new WeightedSumFunction(), new FermiFunction(1), new IdentityFunction(), 
																	new StandardThreshold(0), new WeightedSumFunction(), new FermiFunction(1), new IdentityFunction());
	networkOptions.neuronsPerLayerCount = std::vector<unsigned int>(3);
	networkOptions.neuronsPerLayerCount[0]=1;
	networkOptions.neuronsPerLayerCount[1]=3;
	networkOptions.neuronsPerLayerCount[2]=1;
	networkOptions.useBiasNeuron = true;
	networkOptions.selfConnectHiddenLayers = true;
	RecurrentLayeredNetwork* recurrentNetwork = new RecurrentLayeredNetwork(networkOptions);

	/*std::unique_ptr<LayeredNetwork> unfoldedNetwork = recurrentNetwork->unfold(2);
	NetworkTopologyDrawerOptions networkTopologyDrawerOptions;
	networkTopologyDrawerOptions.width = 700;
	networkTopologyDrawerOptions.networkTopology = unfoldedNetwork.get();
	NetworkTopologyDrawer networkTopologyDrawer(0, 0, networkTopologyDrawerOptions);
	networkTopologyDrawer.refresh();

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
        networkTopologyDrawer.draw(window);
        window.display();
    }*/

	NeuralNetwork neuralNetwork(recurrentNetwork);

	BackpropagationThroughTimeLearningRuleOptions options;
	options.enableDebugOutput = true;
	options.debugOutputInterval = 100;
	options.maxTotalErrorValue = 1;
	options.minIterationsPerTry = 3000;
	options.maxIterationsPerTry = 20000;
	options.totalErrorGoal = 0.0001f;
	options.maxTries = 1000;
	options.minRandomWeightValue = -0.5;
	options.maxRandomWeightValue = 0.5;
  	options.weightDecayFac = 0;
	options.momentum = 0;
	options.maxTimeSteps = 2;
	BackpropagationThroughTimeLearningRule learningRule(options);

	Teacher teacher;
	
	for (int i=0;i<4;i++)
	{
		NeuralNetworkIO* teachingPattern = new NeuralNetworkIO();
		std::vector<bool>* teachingInput= new std::vector<bool>(1);

		int lastPattern = -1;
		for (int l = 0; l < 2; l++)
		{
			if (l != 0)
				lastPattern = teachingPattern->back()[0];
			teachingPattern->push_back(std::vector<float>(1));
			teachingPattern->back()[0] = (l==0 && (i==1 || i==2)) || (l==1 && (i==2 || i==3));				
		}

		(*teachingInput)[0] = (lastPattern == teachingPattern->back()[0]);	
		//(*teachingInput)[1] = teachingPattern->back()[0];	
		
		//(*teachingInput)[0] = (i > l);	
		//(*teachingInput)[0] = (i > 0.4 && i < 0.8  && l> 0.4 && l< 0.8 ? 1 : 0);			

		teacher.addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));		
	}

	learningRule.doLearning(neuralNetwork, teacher);

	
	float totalError = teacher.getTotalError(neuralNetwork, TopologicalOrder());

	NeuralNetworkIO teachingPattern;

	teachingPattern.push_back(std::vector<float>(1));
	teachingPattern.back()[0] = 0;		
	teachingPattern.push_back(std::vector<float>(1));
	teachingPattern.back()[0] = 1;		

	std::unique_ptr<NeuralNetworkIO> outputVector = neuralNetwork.calculate(teachingPattern, TopologicalOrder());
}

int main()
{
	doPerceptronTest();
    return 0;
}