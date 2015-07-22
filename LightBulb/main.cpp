// Includes
#include "Function\WeightedSumFunction.hpp"
#include "Neuron\Edge.hpp"
#include "NeuralNetwork\NeuralNetwork.hpp"
#include "NetworkTopology\LayeredNetwork.hpp"
#include "Function\WeightedSumFunction.hpp"
#include "Function\IdentityFunction.hpp"
#include "Function\HyperbolicTangentFunction.hpp"
#include "Function\FermiFunction.hpp"
#include "ActivationOrder\TopologicalOrder.hpp"
#include "Function\BinaryFunction.hpp"
#include "Learning\SingleLayerPerceptronLearningRule.hpp"
#include "Learning\DeltaLearningRule.hpp"
#include "Learning\BackpropagationLearningRule.hpp"
#include "Teaching\Teacher.hpp"
#include "Teaching\TeachingLessonBooleanInput.hpp"
#include "Graphics\NeuralNetworkResultChart.hpp"
#include "NeuronFactory\DifferentFunctionsNeuronFactory.hpp"
#include "NeuronFactory\SameFunctionsNeuronFactory.hpp"
#include "Neuron\StandardThreshold.hpp"
#include "NetworkTopology\RBFNetwork.hpp"
#include "Learning\RBFInterpolationLearningRule.hpp"
#include "Teaching\TeachingLessonLinearInput.hpp"
#include "Learning\DeltaLearningRule.hpp"
#include "ClusterAnalysis\KMeansRBFNeuronPlacer.hpp"
#include "ClusterAnalysis\KNearestRBFNeuronPlacer.hpp"
#include "ClusterAnalysis\ENearestRBFNeuronPlacer.hpp"
#include "Graphics\RBFNetworkStructureChart.hpp"
#include "ClusterAnalysis\ROLFNeuronPlacer.hpp"
#include "NeuralNetwork\NeuralNetworkIO.hpp"
#include "NetworkTopology\RecurrentLayeredNetwork.hpp"
#include "Learning\BackpropagationThroughTimeLearningRule.hpp"
#include "Graphics\LayeredNetworkTopologyDrawer.hpp"
#include "Learning\TruncatedBackpropagationThroughTimeLearningRule.hpp"
#include "NetworkTopology\FreeNetwork.hpp"
#include "ActivationOrder\SynchronousOrder.hpp"
#include "Graphics\FreeNetworkTopologyDrawer.hpp"
#include "Neuron\StandardNeuron.hpp"
#include "Learning\RealTimeRecurrentLearningRule.hpp"
#include "Learning\SchmidhuberLearningRule.hpp"
#include "NetworkTopology\CascadeCorrelationNetwork.hpp"
#include "Learning\CascadeCorrelationLearningRule.hpp"
#include "NetworkTopology\LVQNetwork.hpp"
// Library includes
#include <iostream>
#include <exception>
#include <vector>
#include <SFML\Graphics.hpp>
#include <windows.h>

void doPerceptronTest()
{
	LayeredNetworkOptions layeredNetworkOptions;
	layeredNetworkOptions.neuronFactory = new DifferentFunctionsNeuronFactory(new StandardThreshold(0), new WeightedSumFunction(), new FermiFunction(1), new IdentityFunction(), 
																				new StandardThreshold(0), new WeightedSumFunction(), new FermiFunction(1), new IdentityFunction());
	layeredNetworkOptions.neuronsPerLayerCount = std::vector<unsigned int>(3);
	layeredNetworkOptions.neuronsPerLayerCount[0]=2;
	layeredNetworkOptions.neuronsPerLayerCount[1]=2;
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
	options.resilientLearningRate = false;
//	options.maxTimeSteps = 1;
	BackpropagationLearningRule learningRule(options);

	Teacher teacher;
	for (int i=0;i<8;i+=1)
	{
		for (int l=0;l<8;l+=1)
		{			
			NeuralNetworkIO<double>* teachingPattern = new NeuralNetworkIO<double>(2);
			NeuralNetworkIO<bool>* teachingInput= new NeuralNetworkIO<bool>(1);

			(*teachingPattern).set(0, 0, i);
			(*teachingPattern).set(0, 1, l);
			(*teachingInput).set(0, 0, (i == l));	
			//(*teachingInput)[0] = (i > 0.4 && i < 0.8  && l> 0.4 && l< 0.8 ? 1 : 0);
			teacher.addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));
		}
	}

	//for (double i=0;i<1;i+=0.2)
	//{		
	//	for (double l=0;l<1;l+=0.2)
	//	{			
	//		NeuralNetworkIO* teachingPattern = new NeuralNetworkIO();
	//		std::vector<bool>* teachingInput= new std::vector<bool>(1);

	//		teachingPattern->push_back(std::vector<double>(2));
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

	//teachingPattern->push_back(std::vector<double>(2));
	//teachingPattern->back()[0] = 100;
	//teachingPattern->back()[1] = 100;
	//(*teachingInput)[0] = true;	
	////(*teachingInput)[0] = (i > 0.4 && i < 0.8  && l> 0.4 && l< 0.8 ? 1 : 0);			
	//teacher.addTestingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));
	//}

	bool success = learningRule.doLearning(neuralNetwork, teacher);
	////neuralNetwork.getNetworkTopology()->randomizeWeights(0,1);
	//

	double totalError = teacher.getTotalError(neuralNetwork, TopologicalOrder());

	NeuralNetworkIO<double>* teachingPattern = new NeuralNetworkIO<double>(2);
	(*teachingPattern).set(0, 0, 8);
	(*teachingPattern).set(0,1, 7);

	std::unique_ptr<NeuralNetworkIO<double>> outputVector = neuralNetwork.calculate(*teachingPattern, TopologicalOrder());
	

	NeuralNetworkResultChartOptions neuralNetworkResultChartOptions;
	neuralNetworkResultChartOptions.neuralNetwork = &neuralNetwork;
	neuralNetworkResultChartOptions.binaryInterpretation = true;
	neuralNetworkResultChartOptions.xRangeEnd = 100;
	neuralNetworkResultChartOptions.yRangeEnd = 100;
	neuralNetworkResultChartOptions.activationOrder = new TopologicalOrder();
	
	NeuralNetworkResultChart neuralNetworkResultChart(neuralNetworkResultChartOptions);
	neuralNetworkResultChart.recalculateAllValues();

	
	AbstractNetworkTopologyDrawerOptions networkTopologyDrawerOptions;
	networkTopologyDrawerOptions.width = 700;
	networkTopologyDrawerOptions.height = 600;
	networkTopologyDrawerOptions.posY = 100;
	networkTopologyDrawerOptions.network = &neuralNetwork;
	LayeredNetworkTopologyDrawer networkTopologyDrawer(networkTopologyDrawerOptions);
	networkTopologyDrawer.refresh();
	networkTopologyDrawer.startNewCalculation(*teachingPattern, *new TopologicalOrder());
	networkTopologyDrawer.nextCalculationStep();

    sf::RenderWindow window(sf::VideoMode(800, 700), "LightBulb!");

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
		networkTopologyDrawer.draw(window);
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
			NeuralNetworkIO<double>* teachingPattern = new NeuralNetworkIO<double>(2);
			NeuralNetworkIO<double>* teachingInput= new NeuralNetworkIO<double>(1);

			(*teachingPattern).set(0, 0, i);
			(*teachingPattern).set(0, 1, l);
			(*teachingInput).set(0, 0, (abs(i - 0) <= 5.5f &&  abs(l - 0) <= 5.5f) || (abs(i - 20) <= 5.5f &&  abs(l - 20) <= 5.5f));	
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
	DeltaLearningRuleOptions delteLearningRuleOptions;
	delteLearningRuleOptions.maxIterationsPerTry = 100000;
	delteLearningRuleOptions.maxTries = 1;
	delteLearningRuleOptions.maxTotalErrorValue = 10;
	delteLearningRuleOptions.enableDebugOutput = true;
	delteLearningRuleOptions.changeWeightsBeforeLearning = false;
	delteLearningRuleOptions.resilientLearningRate = true;
	DeltaLearningRule deltaLearningRule(delteLearningRuleOptions);

	deltaLearningRule.doLearning(neuralNetwork, teacher);


	NeuralNetworkResultChartOptions neuralNetworkResultChartOptions;
	neuralNetworkResultChartOptions.neuralNetwork = &neuralNetwork;
	neuralNetworkResultChartOptions.binaryInterpretation = true;
	neuralNetworkResultChartOptions.activationOrder = new TopologicalOrder();
	neuralNetworkResultChartOptions.yRangeEnd = 20;
	neuralNetworkResultChartOptions.xRangeEnd = 20;
	NeuralNetworkResultChart neuralNetworkResultChart(neuralNetworkResultChartOptions);
	neuralNetworkResultChart.recalculateAllValues();

	RBFNetworkStructureChartOptions rbfNetworkStructureChartOptions;
	rbfNetworkStructureChartOptions.rbfNetwork = static_cast<RBFNetwork*>(neuralNetwork.getNetworkTopology());
	rbfNetworkStructureChartOptions.yRangeEnd = 20;
	rbfNetworkStructureChartOptions.xRangeEnd = 20;
	rbfNetworkStructureChartOptions.posX = 300;
	rbfNetworkStructureChartOptions.posY = 0;
	RBFNetworkStructureChart rbfNetworkStructureChart(rbfNetworkStructureChartOptions);
	rbfNetworkStructureChart.recalculateAllValues();


    sf::RenderWindow window(sf::VideoMode(800, 600), "LightBulb!");

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
	//networkOptions.selfConnectOutputLayers = true;
	networkOptions.selfConnectHiddenLayers = true;
	//networkOptions.connectOutputWithInnerNeurons = true;
	RecurrentLayeredNetwork* recurrentNetwork = new RecurrentLayeredNetwork(networkOptions);

	/*std::unique_ptr<LayeredNetwork> unfoldedNetwork = recurrentNetwork->unfold(2);
	NetworkTopologyDrawerOptions networkTopologyDrawerOptions;
	networkTopologyDrawerOptions.width = 700;
	networkTopologyDrawerOptions.height = 600;
	networkTopologyDrawerOptions.networkTopology = unfoldedNetwork.get();
	NetworkTopologyDrawer networkTopologyDrawer(0, 0, networkTopologyDrawerOptions);
	networkTopologyDrawer.refresh();

    sf::RenderWindow window(sf::VideoMode(800, 600), "LightBulb!");

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
	options.minIterationsPerTry = 10000;
	options.maxIterationsPerTry = 30000;
	options.totalErrorGoal = 0.0001f;
	options.maxTries = 1000;
	options.minRandomWeightValue = -0.5;
	options.maxRandomWeightValue = 0.5;
  	options.weightDecayFac = 0;
	options.momentum = 0;
	options.offlineLearning = false;
	options.resilientLearningRate = false;
	options.maxTimeSteps = 2;
	BackpropagationThroughTimeLearningRule learningRule(options);

	Teacher teacher;
	
	for (int i=0;i<4;i++)
	{
		for (int j=0;j<4;j++)
		{
			NeuralNetworkIO<double>* teachingPattern = new NeuralNetworkIO<double>(1);
			NeuralNetworkIO<bool>* teachingInput= new NeuralNetworkIO<bool>(1);

			for (int l = 0; l < 2; l++)
			{
				(*teachingPattern).set(l, 0, (l==0 ? i : j) / 4.0f);
			}

			(*teachingInput).set(1, 0, (i == j));	
			//(*teachingInput)[1] = teachingPattern->back()[0];	
		
			//(*teachingInput)[0] = (i > l);	
			//(*teachingInput)[0] = (i > 0.4 && i < 0.8  && l> 0.4 && l< 0.8 ? 1 : 0);			

			teacher.addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));		
		}
	}

	learningRule.doLearning(neuralNetwork, teacher);
	
	

	NeuralNetworkResultChartOptions neuralNetworkResultChartOptions;
	neuralNetworkResultChartOptions.neuralNetwork = &neuralNetwork;
	neuralNetworkResultChartOptions.binaryInterpretation = true;
	neuralNetworkResultChartOptions.xRangeEnd = 1;
	neuralNetworkResultChartOptions.yRangeEnd = 1;
	neuralNetworkResultChartOptions.yInputNeuronIndex = 0;
	neuralNetworkResultChartOptions.yTimeStep = 1;
	neuralNetworkResultChartOptions.ouputTimeStep = 1;

	neuralNetworkResultChartOptions.activationOrder = new TopologicalOrder();
	
	NeuralNetworkResultChart neuralNetworkResultChart(neuralNetworkResultChartOptions);
	neuralNetworkResultChart.recalculateAllValues();
    sf::RenderWindow window(sf::VideoMode(800, 600), "LightBulb!");

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

void doFreeNetworkTest()
{
	FreeNetworkOptions networkOptions;
	networkOptions.neuronFactory = new SameFunctionsNeuronFactory(new StandardThreshold(0), new WeightedSumFunction(), new FermiFunction(0.1), new IdentityFunction());
	networkOptions.neuronCount = 5;
	networkOptions.realInputNeurons = true;
	networkOptions.inputNeuronCount = 1;
	/*networkOptions.inputNeuronsIndices.resize(1);
	networkOptions.inputNeuronsIndices[0] = 0;*/
	networkOptions.outputNeuronsIndices.resize(1);
	networkOptions.outputNeuronsIndices[0] = 1;
	networkOptions.useBiasNeuron = true;
	
	FreeNetwork* freeNetwork = new FreeNetwork(networkOptions);

	

	NeuralNetwork neuralNetwork(freeNetwork);

	/*std::unique_ptr<LayeredNetwork> unfoldedNetwork = freeNetwork->unfold(2);

	NeuralNetwork unfoldedneuralNetwork(unfoldedNetwork.get());

	freeNetwork->randomizeWeights(-0.5,0.5);

	unfoldedNetwork->copyWeightsFrom(*freeNetwork);

	freeNetwork->randomizeWeights(-0.5,0.5);

	freeNetwork->copyWeightsFrom(*unfoldedNetwork);

	NeuralNetworkIO<double> teachingPattern;

	teachingPattern[0] = std::vector<double>(1);
	teachingPattern.set(0, 0, 0);		
	teachingPattern[1] = std::vector<double>(1);
	teachingPattern.set(1, 0, 1);		

	std::unique_ptr<NeuralNetworkIO<double>> outputVector = neuralNetwork.calculate(teachingPattern, SynchronousOrder());

	std::unique_ptr<NeuralNetworkIO<double>> outputVector2 = unfoldedneuralNetwork.calculate(*teachingPattern.unfold(), TopologicalOrder());*/
	
	BackpropagationThroughTimeLearningRuleOptions options;
	options.enableDebugOutput = true;
	options.debugOutputInterval = 100;
	options.maxTotalErrorValue = 1;
	options.minIterationsPerTry = 3000;
	options.maxIterationsPerTry = 35000;
	options.totalErrorGoal = 0.01f;
	options.maxTries = 10;
	options.minRandomWeightValue = -0.5;
	options.maxRandomWeightValue = 0.5;
  	options.weightDecayFac = 0;
	options.momentum = 0;
	options.resilientLearningRate = false;
	options.maxTimeSteps = 8;
	TruncatedBackpropagationThroughTimeLearningRule learningRule(options);

	Teacher teacher;
	
	for (int i=0;i<=1;i++)
	{
		for (int j=0;j<=1;j++)
		{
			for (int k=0;k<=1;k++)
			{
				NeuralNetworkIO<double>* teachingPattern = new NeuralNetworkIO<double>(1);
				NeuralNetworkIO<bool>* teachingInput = new NeuralNetworkIO<bool>(1);

				for (int l = 0; l < 6; l++)
				{					
					(*teachingPattern).set(l, 0, (l%3==0 ? i : (l%3==1 ? j : k)));		
				}

				(*teachingInput).set(3, 0, (i == j));

				(*teachingInput).set(4, 0, (j == k));	

				(*teachingInput).set(5, 0, (k == i));	

				(*teachingInput).set(6, 0, (i == j));

				(*teachingInput).set(7, 0, (j == k));

				teacher.addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));	
			}
		}
	}
	

	learningRule.doLearning(neuralNetwork, teacher);
	double totalError = teacher.getTotalError(neuralNetwork, SynchronousOrder());

	
	NeuralNetworkIO<double> teachingPattern(1);

	teachingPattern.set(0, 0, 1);		
	teachingPattern.set(1, 0, 1);		

	//std::unique_ptr<NeuralNetworkIO<double>> outputVector = neuralNetwork.calculate(teachingPattern, SynchronousOrder(), 0, 4);

	AbstractNetworkTopologyDrawerOptions networkTopologyDrawerOptions;
	networkTopologyDrawerOptions.width = 700;
	networkTopologyDrawerOptions.height = 600;
	networkTopologyDrawerOptions.network = &neuralNetwork;
	FreeNetworkTopologyDrawer networkTopologyDrawer(networkTopologyDrawerOptions);
	networkTopologyDrawer.refresh();

    sf::RenderWindow window(sf::VideoMode(800, 600), "LightBulb!");

	int t = 0;
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
		if (t == 0)
			networkTopologyDrawer.startNewCalculation(teachingPattern, SynchronousOrder());
		else if (t <= 4)
			networkTopologyDrawer.nextCalculationStep();
		else
		{
			networkTopologyDrawer.resetCalculation();
			t = -1;
		}
		t++;

		Sleep(2000);
    }

}

void doRTRLTest()
{
	FreeNetworkOptions networkOptions;
	networkOptions.neuronFactory = new SameFunctionsNeuronFactory(new StandardThreshold(0), new WeightedSumFunction(), new FermiFunction(0.1), new IdentityFunction());
	networkOptions.neuronCount = 5;
	networkOptions.inputNeuronsIndices.resize(1);
	networkOptions.inputNeuronsIndices[0] = 0;
	networkOptions.outputNeuronsIndices.resize(1);
	networkOptions.outputNeuronsIndices[0] = 1;
	networkOptions.useBiasNeuron = true;
	
	FreeNetwork* freeNetwork = new FreeNetwork(networkOptions);

	

	NeuralNetwork neuralNetwork(freeNetwork);
	
	RealTimeRecurrentLearningRuleOptions options;
	options.enableDebugOutput = true;
	options.debugOutputInterval = 100;
	options.maxTotalErrorValue = 1;
	options.minIterationsPerTry = 3000;
	options.maxIterationsPerTry = 35000;
	options.totalErrorGoal = 0.01f;
	options.maxTries = 1000;
	options.minRandomWeightValue = -0.5;
	options.maxRandomWeightValue = 0.5;
	options.teacherForcing = false;
	RealTimeRecurrentLearningRule learningRule(options);

	Teacher teacher;
	
	for (int i=0;i<=1;i++)
	{
		for (int j=0;j<=1;j++)
		{
			for (int k=0;k<=1;k++)
			{
				NeuralNetworkIO<double>* teachingPattern = new NeuralNetworkIO<double>(1);
				NeuralNetworkIO<bool>* teachingInput = new NeuralNetworkIO<bool>(1);

				for (int l = 0; l < 6; l++)
				{					
					(*teachingPattern).set(l, 0, (l%3==0 ? i : (l%3==1 ? j : k)));		
				}

				(*teachingInput).set(3, 0, (i == j));

				(*teachingInput).set(4, 0, (j == k));	

				(*teachingInput).set(5, 0, (k == i));	

				(*teachingInput).set(6, 0, (i == j));

				(*teachingInput).set(7, 0, (j == k));	

				teacher.addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));	
			}
		}
	}
	

	learningRule.doLearning(neuralNetwork, teacher);
	double totalError = teacher.getTotalError(neuralNetwork, SynchronousOrder());

		
	NeuralNetworkIO<double> teachingPattern(1);

	teachingPattern.set(0, 0, 0);		
	teachingPattern.set(1, 0, 1);		
	teachingPattern.set(2, 0, 1);	
	teachingPattern.set(3, 0, 1);	
	teachingPattern.set(4, 0, 0);	
	teachingPattern.set(5, 0, 0);	

	std::unique_ptr<NeuralNetworkIO<double>> outputVector = neuralNetwork.calculate(teachingPattern, SynchronousOrder(), 0, 8);
}

void doSchmidhuberTest()
{
	FreeNetworkOptions networkOptions;
	networkOptions.neuronFactory = new SameFunctionsNeuronFactory(new StandardThreshold(0), new WeightedSumFunction(), new FermiFunction(0.1), new IdentityFunction());
	networkOptions.neuronCount = 5;
	//networkOptions.realInputNeurons = true;
	//networkOptions.inputNeuronCount = 1;
	networkOptions.inputNeuronsIndices.resize(1);
	networkOptions.inputNeuronsIndices[0] = 0;
	networkOptions.outputNeuronsIndices.resize(1);
	networkOptions.outputNeuronsIndices[0] = 1;
	networkOptions.useBiasNeuron = true;
	
	FreeNetwork* freeNetwork = new FreeNetwork(networkOptions);	

	NeuralNetwork neuralNetwork(freeNetwork);
	
	SchmidhuberLearningRuleOptions options;
	options.enableDebugOutput = true;
	options.debugOutputInterval = 100;
	options.maxTotalErrorValue = 1;
	options.minIterationsPerTry = 3000;
	options.maxIterationsPerTry = 35000;
	options.totalErrorGoal = 0.01f;
	options.maxTries = 1000;
	options.minRandomWeightValue = -0.5;
	options.maxRandomWeightValue = 0.5;
	SchmidhuberLearningRule learningRule(options);

	Teacher teacher;
	
	for (int i=0;i<=1;i++)
	{
		for (int j=0;j<=1;j++)
		{
			for (int k=0;k<=1;k++)
			{
				NeuralNetworkIO<double>* teachingPattern = new NeuralNetworkIO<double>(1);
				NeuralNetworkIO<bool>* teachingInput = new NeuralNetworkIO<bool>(1);

				for (int l = 0; l < 6; l++)
				{					
					(*teachingPattern).set(l, 0, (l%3==0 ? i : (l%3==1 ? j : k)));		
				}

				(*teachingInput).set(3, 0, (i == j));

				(*teachingInput).set(4, 0, (j == k));	

				(*teachingInput).set(5, 0, (k == i));	

				(*teachingInput).set(6, 0, (i == j));

				(*teachingInput).set(7, 0, (j == k));	

				teacher.addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));	
			}
		}
	}
	

	learningRule.doLearning(neuralNetwork, teacher);
	double totalError = teacher.getTotalError(neuralNetwork, SynchronousOrder());


}

void doCascadeCorrelationTest()
{
	CascadeCorrelationNetwork* ccn = new CascadeCorrelationNetwork(2, 1);

	NeuralNetwork neuralNetwork(ccn);

	double twoSpiralValues[][3] = 
	{
	{6.5 ,0 ,1},
	{-6.5 ,0 ,-1},
	{6.3138 ,1.2559 ,1},
	{-6.3138 ,-1.2559 ,-1},
	{5.88973 ,2.43961 ,1},
	{-5.88973 ,-2.43961 ,-1},
	{5.24865 ,3.50704 ,1},
	{-5.24865 ,-3.50704 ,-1},
	{4.41941 ,4.41943 ,1},
	{-4.41941 ,-4.41943 ,-1},
	{3.43758 ,5.14473 ,1},
	{-3.43758 ,-5.14473 ,-1},
	{2.34392 ,5.65877 ,1},
	{-2.34392 ,-5.65877 ,-1},
	{1.18272 ,5.94601 ,1},
	{-1.18272 ,-5.94601 ,-1},
	{-0.00002 ,6 ,1},
	{0.00002 ,-6 ,-1},
	{-1.15837 ,5.82341 ,1},
	{1.15837 ,-5.82341 ,-1},
	{-2.24829 ,5.42778 ,1},
	{2.24829 ,-5.42778 ,-1},
	{-3.22928 ,4.8329 ,1},
	{3.22928 ,-4.8329 ,-1},
	{-4.06589 ,4.06584 ,1},
	{4.06589 ,-4.06584 ,-1},
	{-4.729 ,3.15978 ,1},
	{4.729 ,-3.15978 ,-1},
	{-5.19684 ,2.15256 ,1},
	{5.19684 ,-2.15256 ,-1},
	{-5.45563 ,1.08515 ,1},
	{5.45563 ,-1.08515 ,-1},
	{-5.5 ,-0.00004 ,1},
	{5.5 ,0.00004 ,-1},
	{-5.33301 ,-1.06085 ,1},
	{5.33301 ,1.06085 ,-1},
	{-4.96584 ,-2.05696 ,1},
	{4.96584 ,2.05696 ,-1},
	{-4.41716 ,-2.95151 ,1},
	{4.41716 ,2.95151 ,-1},
	{-3.71228 ,-3.71234 ,1},
	{3.71228 ,3.71234 ,-1},
	{-2.88198 ,-4.31328 ,1},
	{2.88198 ,4.31328 ,-1},
	{-1.9612 ,-4.7349 ,1},
	{1.9612 ,4.7349 ,-1},
	{-0.98759 ,-4.96524 ,1},
	{0.98759 ,4.96524 ,-1},
	{0.00006 ,-5 ,1},
	{-0.00006 ,5 ,-1},
	{0.96331 ,-4.84262 ,1},
	{-0.96331 ,4.84262 ,-1},
	{1.86564 ,-4.50389 ,1},
	{-1.86564 ,4.50389 ,-1},
	{2.67373 ,-4.00141 ,1},
	{-2.67373 ,4.00141 ,-1},
	{3.3588 ,-3.35871 ,1},
	{-3.3588 ,3.35871 ,-1},
	{3.89755 ,-2.60418 ,1},
	{-3.89755 ,2.60418 ,-1},
	{4.27297 ,-1.76985 ,1},
	{-4.27297 ,1.76985 ,-1},
	{4.47485 ,-0.89004 ,1},
	{-4.47485 ,0.89004 ,-1},
	{4.5 ,0.00007 ,1},
	{-4.5 ,-0.00007 ,-1},
	{4.35222 ,0.86578 ,1},
	{-4.35222 ,-0.86578 ,-1},
	{4.04195 ,1.6743 ,1},
	{-4.04195 ,-1.6743 ,-1},
	{3.58567 ,2.39595 ,1},
	{-3.58567 ,-2.39595 ,-1},
	{3.00515 ,3.00525 ,1},
	{-3.00515 ,-3.00525 ,-1},
	{2.32639 ,3.48182 ,1},
	{-2.32639 ,-3.48182 ,-1},
	{1.5785 ,3.81103 ,1},
	{-1.5785 ,-3.81103 ,-1},
	{0.79248 ,3.98445 ,1},
	{-0.79248 ,-3.98445 ,-1},
	{-0.00007 ,4 ,1},
	{0.00007 ,-4 ,-1},
	{-0.76824 ,3.86183 ,1},
	{0.76824 ,-3.86183 ,-1},
	{-1.48297 ,3.58 ,1},
	{1.48297 ,-3.58 ,-1},
	{-2.11817 ,3.16994 ,1},
	{2.11817 ,-3.16994 ,-1},
	{-2.6517 ,2.6516 ,1},
	{2.6517 ,-2.6516 ,-1},
	{-3.06609 ,2.0486 ,1},
	{3.06609 ,-2.0486 ,-1},
	{-3.34909 ,1.38716 ,1},
	{3.34909 ,-1.38716 ,-1},
	{-3.49406 ,0.69493 ,1},
	{3.49406 ,-0.69493 ,-1},
	{-3.5 ,-0.00008 ,1},
	{3.5 ,0.00008 ,-1},
	{-3.37143 ,-0.6707 ,1},
	{3.37143 ,0.6707 ,-1},
	{-3.11806 ,-1.29163 ,1},
	{3.11806 ,1.29163 ,-1},
	{-2.7542 ,-1.84039 ,1},
	{2.7542 ,1.84039 ,-1},
	{-2.29804 ,-2.29815 ,1},
	{2.29804 ,2.29815 ,-1},
	{-1.77082 ,-2.65035 ,1},
	{1.77082 ,2.65035 ,-1},
	{-1.19581 ,-2.88715 ,1},
	{1.19581 ,2.88715 ,-1},
	{-0.59739 ,-3.00367 ,1},
	{0.59739 ,3.00367 ,-1},
	{0.00008 ,-3 ,1},
	{-0.00008 ,3 ,-1},
	{0.57315 ,-2.88104 ,1},
	{-0.57315 ,2.88104 ,-1},
	{1.10029 ,-2.65612 ,1},
	{-1.10029 ,2.65612 ,-1},
	{1.5626 ,-2.33847 ,1},
	{-1.5626 ,2.33847 ,-1},
	{1.9446 ,-1.94449 ,1},
	{-1.9446 ,1.94449 ,-1},
	{2.23462 ,-1.49303 ,1},
	{-2.23462 ,1.49303 ,-1},
	{2.42521 ,-1.00447 ,1},
	{-2.42521 ,1.00447 ,-1},
	{2.51328 ,-0.49985 ,1},
	{-2.51328 ,0.49985 ,-1},
	{2.5 ,0.00007 ,1},
	{-2.5 ,-0.00007 ,-1},
	{2.39065 ,0.4756 ,1},
	{-2.39065 ,-0.4756 ,-1},
	{2.19419 ,0.90894 ,1},
	{-2.19419 ,-0.90894 ,-1},
	{1.92273 ,1.28482 ,1},
	{-1.92273 ,-1.28482 ,-1},
	{1.59094 ,1.59104 ,1},
	{-1.59094 ,-1.59104 ,-1},
	{1.21525 ,1.81888 ,1},
	{-1.21525 ,-1.81888 ,-1},
	{0.81314 ,1.96327 ,1},
	{-0.81314 ,-1.96327 ,-1},
	{0.40231 ,2.02288 ,1},
	{-0.40231 ,-2.02288 ,-1},
	{-0.00007 ,2 ,1},
	{0.00007 ,-2 ,-1},
	{-0.37805 ,1.90026 ,1},
	{0.37805 ,-1.90026 ,-1},
	{-0.71759 ,1.73225 ,1},
	{0.71759 ,-1.73225 ,-1},
	{-1.00702 ,1.507 ,1},
	{1.00702 ,-1.507 ,-1},
	{-1.23748 ,1.23739 ,1},
	{1.23748 ,-1.23739 ,-1},
	{-1.40314 ,0.93748 ,1},
	{1.40314 ,-0.93748 ,-1},
	{-1.50133 ,0.62181 ,1},
	{1.50133 ,-0.62181 ,-1},
	{-1.53249 ,0.30477 ,1},
	{1.53249 ,-0.30477 ,-1},
	{-1.5 ,-0.00006 ,1},
	{1.5 ,0.00006 ,-1},
	{-1.40987 ,-0.28049 ,1},
	{1.40987 ,0.28049 ,-1},
	{-1.27031 ,-0.52624 ,1},
	{1.27031 ,0.52624 ,-1},
	{-1.09128 ,-0.72923 ,1},
	{1.09128 ,0.72923 ,-1},
	{-0.88385 ,-0.88392 ,1},
	{0.88385 ,0.88392 ,-1},
	{-0.6597 ,-0.9874 ,1},
	{0.6597 ,0.9874 ,-1},
	{-0.43048 ,-1.03938 ,1},
	{0.43048 ,1.03938 ,-1},
	{-0.20724 ,-1.04209 ,1},
	{0.20724 ,1.04209 ,-1},
	{0.00004 ,-1 ,1},
	{-0.00004 ,1 ,-1},
	{0.18293 ,-0.91948 ,1},
	{-0.18293 ,0.91948 ,-1},
	{0.33488 ,-0.80838 ,1},
	{-0.33488 ,0.80838 ,-1},
	{0.45143 ,-0.67555 ,1},
	{-0.45143 ,0.67555 ,-1},
	{0.53035 ,-0.53031 ,1},
	{-0.53035 ,0.53031 ,-1},
	{0.57165 ,-0.38193 ,1},
	{-0.57165 ,0.38193 ,-1},
	{0.57744 ,-0.23915 ,1},
	{-0.57744 ,0.23915 ,-1},
	{0.5517 ,-0.10971 ,1},
	{-0.5517 ,0.10971 ,-1},
	{0.5 ,0.00002 ,1},
	{-0.5 ,-0.00002 ,-1}
	};

	Teacher teacher;
	for (int i=0; i<194; i+=1)
	{
		NeuralNetworkIO<double>* teachingPattern = new NeuralNetworkIO<double>(2);
		NeuralNetworkIO<bool>* teachingInput= new NeuralNetworkIO<bool>(1);

		(*teachingPattern).set(0, 0, twoSpiralValues[i][0]);
		(*teachingPattern).set(0, 1, twoSpiralValues[i][1]);
		(*teachingInput).set(0, 0, (twoSpiralValues[i][2] == 1));//(i > 0.4 && i < 0.8  && l> 0.4 && l< 0.8 ? 1 : 0));
		teacher.addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));		
	}

	CascadeCorrelationLearningRuleOptions options;
	options.enableDebugOutput = true;
	options.debugOutputInterval = 10;
	options.maxTotalErrorValue = 4;
	options.minIterationsPerTry = 300000;
	options.maxIterationsPerTry = 1000000;
	options.totalErrorGoal = 0.01f;
	options.minRandomWeightValue = -0.5;
	options.maxRandomWeightValue = 0.5;
	options.addNeuronAfterIterationInterval = 50;
	options.candidateUnitCount = 8;
	options.outputNeuronsLearningRuleOptions.resilientLearningRate = true;
	options.outputNeuronsLearningRuleOptions.resilientLearningRateOptions.minLearningRate = 0.1;
	options.candidateUnitsLearningRuleOptions.resilientLearningRate = true;
	options.candidateUnitsLearningRuleOptions.resilientLearningRateOptions.minLearningRate = 1;
	CascadeCorrelationLearningRule learningRule(options);

	learningRule.doLearning(neuralNetwork, teacher);


	NeuralNetworkResultChartOptions neuralNetworkResultChartOptions;
	neuralNetworkResultChartOptions.neuralNetwork = &neuralNetwork;
	neuralNetworkResultChartOptions.binaryInterpretation = true;
	neuralNetworkResultChartOptions.xRangeStart = -8;
	neuralNetworkResultChartOptions.yRangeStart = -8;
	neuralNetworkResultChartOptions.xRangeEnd = 8;
	neuralNetworkResultChartOptions.yRangeEnd = 8;
	neuralNetworkResultChartOptions.width = 500;
	neuralNetworkResultChartOptions.height = 500;
	neuralNetworkResultChartOptions.activationOrder = new TopologicalOrder();
	
	NeuralNetworkResultChart neuralNetworkResultChart(neuralNetworkResultChartOptions);
	neuralNetworkResultChart.recalculateAllValues();
    sf::RenderWindow window(sf::VideoMode(800, 600), "LightBulb!");

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

void doRecurrentCascadeCorrelationTest()
{
	CascadeCorrelationNetwork* ccn = new CascadeCorrelationNetwork(1, 1);

	NeuralNetwork neuralNetwork(ccn);


	Teacher teacher;

	{
		
		NeuralNetworkIO<double>* teachingPattern = new NeuralNetworkIO<double>(1);
		NeuralNetworkIO<bool>* teachingInput= new NeuralNetworkIO<bool>(1);

		int lastPattern = -1;
		for (int l = 0; l < 6; l++)
		{
			(*teachingPattern).set(l, 0, 1);
			(*teachingInput).set(l, 0, (l%2 == 0));	
		}

		//(*teachingInput)[1] = teachingPattern->back()[0];	
		
		//(*teachingInput)[0] = (i > l);	
		//(*teachingInput)[0] = (i > 0.4 && i < 0.8  && l> 0.4 && l< 0.8 ? 1 : 0);			

		teacher.addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));	
	
	}

	//ccn->addNewLayer(1, 0);
	//StandardNeuron* currentCandidateUnit = static_cast<StandardNeuron*>(ccn->addNeuronIntoLayer(1, true, true));
	//currentCandidateUnit->addNextNeuron(currentCandidateUnit, 1);

	//neuralNetwork.calculate(*teacher.getTeachingLessons()->front()->getTeachingPattern(), TopologicalOrder());

	CascadeCorrelationLearningRuleOptions options;
	options.enableDebugOutput = true;
	options.debugOutputInterval = 10;
	options.maxTotalErrorValue = 4;
	options.minIterationsPerTry = 300000;
	options.maxIterationsPerTry = 1000000;
	options.totalErrorGoal = 0.01f;
	options.minRandomWeightValue = -0.5;
	options.maxRandomWeightValue = 0.5;
	options.addNeuronAfterIterationInterval = 50;	
	options.candidateUnitCount = 8;
	options.recurrent = true;
	options.outputNeuronsLearningRuleOptions.resilientLearningRate = true;
	options.outputNeuronsLearningRuleOptions.resilientLearningRateOptions.minLearningRate = 0.1;
	options.candidateUnitsLearningRuleOptions.resilientLearningRate = true;
	options.candidateUnitsLearningRuleOptions.resilientLearningRateOptions.minLearningRate = 1;
	CascadeCorrelationLearningRule learningRule(options);

	learningRule.doLearning(neuralNetwork, teacher);


	NeuralNetworkIO<double>* teachingPattern = new NeuralNetworkIO<double>(1);

	int lastPattern = -1;
	for (int l = 0; l < 16; l++)
	{
		(*teachingPattern).set(l, 0, 1);
	}

	std::unique_ptr<NeuralNetworkIO<double>> output = neuralNetwork.calculate(*teachingPattern, TopologicalOrder());

	
	NeuralNetworkResultChartOptions neuralNetworkResultChartOptions;
	neuralNetworkResultChartOptions.neuralNetwork = &neuralNetwork;
	neuralNetworkResultChartOptions.binaryInterpretation = true;
	neuralNetworkResultChartOptions.xRangeEnd = 1;
	neuralNetworkResultChartOptions.yRangeEnd = 1;
	neuralNetworkResultChartOptions.yInputNeuronIndex = 0;
	neuralNetworkResultChartOptions.yTimeStep = 1;
	neuralNetworkResultChartOptions.ouputTimeStep = 1;

	neuralNetworkResultChartOptions.activationOrder = new TopologicalOrder();
	
	NeuralNetworkResultChart neuralNetworkResultChart(neuralNetworkResultChartOptions);
	neuralNetworkResultChart.recalculateAllValues();
    sf::RenderWindow window(sf::VideoMode(800, 600), "LightBulb!");

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


void doRecurrentCascadeCorrelationMorseTest()
{
	CascadeCorrelationNetwork* ccn = new CascadeCorrelationNetwork(1, 27);

	NeuralNetwork neuralNetwork(ccn);

	Teacher teacher;

	std::string text = "abcdefghijklmnopqrstuvwqyz"; 

	std::string morse[] = {".-","-...","-.-.","-..", ".", "..-.", "--.",
	                      "....", "..", ".---", "-.-", ".-..", "--",
	                      "-.", "---", ".--.", "--.-", ".-.", "...", "-",
	                      "..-", "...-", ".--", "-..-", "-.--", "--.."}; 

	{
		
		int lastPattern = -1;
		for (int m = 0; m < 26; m++)
		{
			NeuralNetworkIO<double>* teachingPattern = new NeuralNetworkIO<double>(1);
			NeuralNetworkIO<bool>* teachingInput= new NeuralNetworkIO<bool>(27);

			int t = 0;
			for (int s = 0; s < morse[m].length(); s++)
			{
				//(*teachingInput).set(t, 26, false);

				(*teachingPattern).set(t++, 0, 1);
				if (morse[m][s] == '-')
				{
					//(*teachingInput).set(t, 26, false);
					(*teachingPattern).set(t++, 0, 1);
				}

			//	(*teachingInput).set(t, 26, false);
				(*teachingPattern).set(t++, 0, 0);				
			}
			(*teachingPattern).set(t, 0, 0);

			for (int b = 0; b < 27; b++)
			{
				if (b == text[m] - 'a')				
					(*teachingInput).set(t, b, true);	
				else
					(*teachingInput).set(t, b, false);	
			}
			(*teachingInput).set(t, 26, true);

			teacher.addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));	
		}
		//(*teachingInput)[1] = teachingPattern->back()[0];	
		
		//(*teachingInput)[0] = (i > l);	
		//(*teachingInput)[0] = (i > 0.4 && i < 0.8  && l> 0.4 && l< 0.8 ? 1 : 0);			

	
	}

	//ccn->addNewLayer(1, 0);
	//StandardNeuron* currentCandidateUnit = static_cast<StandardNeuron*>(ccn->addNeuronIntoLayer(1, true, true));
	//currentCandidateUnit->addNextNeuron(currentCandidateUnit, 1);

	//neuralNetwork.calculate(*teacher.getTeachingLessons()->front()->getTeachingPattern(), TopologicalOrder());

	CascadeCorrelationLearningRuleOptions options;
	options.enableDebugOutput = true;
	options.debugOutputInterval = 10;
	options.maxTotalErrorValue = 4;
	options.minIterationsPerTry = 300000;
	options.maxIterationsPerTry = 1000000;
	options.totalErrorGoal = 0.01f;
	options.minRandomWeightValue = -0.5;
	options.maxRandomWeightValue = 0.5;
	options.addNeuronAfterIterationInterval = 50;	
	options.candidateUnitCount = 8;
	options.recurrent = true;
	options.outputNeuronsLearningRuleOptions.resilientLearningRate = true;
	options.outputNeuronsLearningRuleOptions.resilientLearningRateOptions.minLearningRate = 0.1;
	options.candidateUnitsLearningRuleOptions.resilientLearningRate = true;
	options.candidateUnitsLearningRuleOptions.resilientLearningRateOptions.minLearningRate = 1;
	CascadeCorrelationLearningRule learningRule(options);

	learningRule.doLearning(neuralNetwork, teacher);


	NeuralNetworkIO<double>* teachingPattern = new NeuralNetworkIO<double>(1);

	int lastPattern = -1;
	for (int l = 0; l < 16; l++)
	{
		(*teachingPattern).set(l, 0, 1);
	}

	std::unique_ptr<NeuralNetworkIO<double>> output = neuralNetwork.calculate(*(*teacher.getTeachingLessons())[15]->getTeachingPattern(), TopologicalOrder());

	for (auto v = (*output).rbegin()->second.begin(); v != (*output).rbegin()->second.end(); v++)
	{
		if (v->second>0)
			std::cout << "1,";
		else
			std::cout << "0,";
	}
	
	NeuralNetworkResultChartOptions neuralNetworkResultChartOptions;
	neuralNetworkResultChartOptions.neuralNetwork = &neuralNetwork;
	neuralNetworkResultChartOptions.binaryInterpretation = true;
	neuralNetworkResultChartOptions.xRangeEnd = 1;
	neuralNetworkResultChartOptions.yRangeEnd = 1;
	neuralNetworkResultChartOptions.yInputNeuronIndex = 0;
	neuralNetworkResultChartOptions.yTimeStep = 1;
	neuralNetworkResultChartOptions.ouputTimeStep = 1;

	neuralNetworkResultChartOptions.activationOrder = new TopologicalOrder();
	
	NeuralNetworkResultChart neuralNetworkResultChart(neuralNetworkResultChartOptions);
	neuralNetworkResultChart.recalculateAllValues();
    sf::RenderWindow window(sf::VideoMode(800, 600), "LightBulb!");

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

void doLVQTest()
{
	LVQNetwork* lvqNetwork = new LVQNetwork(2, 3);

	NeuralNetwork neuralNetwork(lvqNetwork);
}

int main()
{
	doLVQTest();
    return 0;
}
