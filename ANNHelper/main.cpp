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
#include "Teacher.hpp"
#include "TeachingLessonBooleanInput.hpp"
#include "NeuralNetworkResultChart.hpp"
#include "DifferentFunctionsNeuronFactory.hpp"
#include "SameFunctionsNeuronFactory.hpp"
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
#include "LayeredNetworkTopologyDrawer.hpp"
#include "TruncatedBackpropagationThroughTimeLearningRule.hpp"
#include "FreeNetwork.hpp"
#include "SynchronousOrder.hpp"
#include "FreeNetworkTopologyDrawer.hpp"
#include "StandardNeuron.hpp"
#include "RealTimeRecurrentLearningRule.hpp"
#include "SchmidhuberLearningRule.hpp"
#include "CascadeCorrelationNetwork.hpp"
#include "CascadeCorrelationLearningRule.hpp"

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
	options.resilientLearningRate = false;
//	options.maxTimeSteps = 1;
	BackpropagationLearningRule learningRule(options);

	Teacher teacher;
	for (int i=0;i<8;i+=1)
	{
		for (int l=0;l<8;l+=1)
		{			
			NeuralNetworkIO<float>* teachingPattern = new NeuralNetworkIO<float>();
			NeuralNetworkIO<bool>* teachingInput= new NeuralNetworkIO<bool>();

			(*teachingPattern)[0] = std::vector<float>(2);
			(*teachingPattern)[0][0] = i;
			(*teachingPattern)[0][1] = l;
			(*teachingInput)[0] = std::vector<bool>(1);
			(*teachingInput)[0][0] = (i == l);	
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

	NeuralNetworkIO<float>* teachingPattern = new NeuralNetworkIO<float>();
	(*teachingPattern)[0] = std::vector<float>(2);
	(*teachingPattern)[0][0] = 8;
	(*teachingPattern)[0][1] = 8;

	std::unique_ptr<NeuralNetworkIO<float>> outputVector = neuralNetwork.calculate(*teachingPattern, TopologicalOrder());
	

	NeuralNetworkResultChartOptions neuralNetworkResultChartOptions;
	neuralNetworkResultChartOptions.neuralNetwork = &neuralNetwork;
	neuralNetworkResultChartOptions.binaryInterpretation = true;
	neuralNetworkResultChartOptions.xRangeEnd = 100;
	neuralNetworkResultChartOptions.yRangeEnd = 100;
	neuralNetworkResultChartOptions.activationOrder = new TopologicalOrder();
	
	NeuralNetworkResultChart neuralNetworkResultChart(neuralNetworkResultChartOptions);
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
			NeuralNetworkIO<float>* teachingPattern = new NeuralNetworkIO<float>();
			NeuralNetworkIO<float>* teachingInput= new NeuralNetworkIO<float>();

			(*teachingPattern)[0] = std::vector<float>(2);
			(*teachingPattern)[0][0] = i;
			(*teachingPattern)[0][1] = l;
			(*teachingInput)[0] = std::vector<float>(1);
			(*teachingInput)[0][0] = (abs(i - 0) <= 5.5f &&  abs(l - 0) <= 5.5f) || (abs(i - 20) <= 5.5f &&  abs(l - 20) <= 5.5f);	
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
			NeuralNetworkIO<float>* teachingPattern = new NeuralNetworkIO<float>();
			NeuralNetworkIO<bool>* teachingInput= new NeuralNetworkIO<bool>();

			int lastPattern = -1;
			for (int l = 0; l < 2; l++)
			{
				if (l != 0)
					lastPattern = (*teachingPattern)[l-1][0];
				(*teachingPattern)[l] = std::vector<float>(1);
				(*teachingPattern)[l][0] = (l==0 ? i : j) / 4.0f;		

			}

			(*teachingInput)[1] = std::vector<bool>(1);
			(*teachingInput)[1][0] = (i == j);	
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

void doFreeNetworkTest()
{
	FreeNetworkOptions networkOptions;
	networkOptions.neuronFactory = new SameFunctionsNeuronFactory(new StandardThreshold(0), new WeightedSumFunction(), new FermiFunction(0.1), new IdentityFunction());
	networkOptions.neuronCount = 5;
	networkOptions.realInputNeurons = false;
	networkOptions.inputNeuronCount = 1;
	networkOptions.inputNeuronsIndices.resize(1);
	networkOptions.inputNeuronsIndices[0] = 0;
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

	NeuralNetworkIO<float> teachingPattern;

	teachingPattern[0] = std::vector<float>(1);
	teachingPattern[0][0] = 0;		
	teachingPattern[1] = std::vector<float>(1);
	teachingPattern[1][0] = 1;		

	std::unique_ptr<NeuralNetworkIO<float>> outputVector = neuralNetwork.calculate(teachingPattern, SynchronousOrder());

	std::unique_ptr<NeuralNetworkIO<float>> outputVector2 = unfoldedneuralNetwork.calculate(*teachingPattern.unfold(), TopologicalOrder());*/
	
	BackpropagationThroughTimeLearningRuleOptions options;
	options.enableDebugOutput = true;
	options.debugOutputInterval = 100;
	options.maxTotalErrorValue = 1;
	options.minIterationsPerTry = 3000;
	options.maxIterationsPerTry = 35000;
	options.totalErrorGoal = 0.01f;
	options.maxTries = 1000;
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
				NeuralNetworkIO<float>* teachingPattern = new NeuralNetworkIO<float>();
				NeuralNetworkIO<bool>* teachingInput = new NeuralNetworkIO<bool>();

				for (int l = 0; l < 6; l++)
				{					
					(*teachingPattern)[l] = std::vector<float>(1);
					(*teachingPattern)[l][0] = (l%3==0 ? i : (l%3==1 ? j : k));		
				}

				(*teachingInput)[3] = std::vector<bool>(1);
				(*teachingInput)[3][0] = (i == j);

				(*teachingInput)[4] = std::vector<bool>(1);
				(*teachingInput)[4][0] = (j == k);	

				(*teachingInput)[5] = std::vector<bool>(1);
				(*teachingInput)[5][0] = (k == i);	

				(*teachingInput)[6] = std::vector<bool>(1);
				(*teachingInput)[6][0] = (i == j);

				(*teachingInput)[7] = std::vector<bool>(1);
				(*teachingInput)[7][0] = (j == k);	

				teacher.addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));	
			}
		}
	}
	

	learningRule.doLearning(neuralNetwork, teacher);
	float totalError = teacher.getTotalError(neuralNetwork, SynchronousOrder());

	
	/*NeuralNetworkIO<float> teachingPattern;

	teachingPattern[0] = std::vector<float>(1);
	teachingPattern[0][0] = 50;		
	teachingPattern[1] = std::vector<float>(1);
	teachingPattern[1][0] = 49;		

	std::unique_ptr<NeuralNetworkIO<float>> outputVector = neuralNetwork.calculate(teachingPattern, SynchronousOrder(), 0, 4);*/

	AbstractNetworkTopologyDrawerOptions networkTopologyDrawerOptions;
	networkTopologyDrawerOptions.width = 700;
	networkTopologyDrawerOptions.height = 600;
	networkTopologyDrawerOptions.networkTopology = freeNetwork;
	FreeNetworkTopologyDrawer networkTopologyDrawer(networkTopologyDrawerOptions);
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
				NeuralNetworkIO<float>* teachingPattern = new NeuralNetworkIO<float>();
				NeuralNetworkIO<bool>* teachingInput = new NeuralNetworkIO<bool>();

				for (int l = 0; l < 6; l++)
				{					
					(*teachingPattern)[l] = std::vector<float>(1);
					(*teachingPattern)[l][0] = (l%3==0 ? i : (l%3==1 ? j : k));		
				}

				(*teachingInput)[3] = std::vector<bool>(1);
				(*teachingInput)[3][0] = (i == j);

				(*teachingInput)[4] = std::vector<bool>(1);
				(*teachingInput)[4][0] = (j == k);	

				(*teachingInput)[5] = std::vector<bool>(1);
				(*teachingInput)[5][0] = (k == i);	

				(*teachingInput)[6] = std::vector<bool>(1);
				(*teachingInput)[6][0] = (i == j);

				(*teachingInput)[7] = std::vector<bool>(1);
				(*teachingInput)[7][0] = (j == k);	

				teacher.addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));	
			}
		}
	}
	

	learningRule.doLearning(neuralNetwork, teacher);
	float totalError = teacher.getTotalError(neuralNetwork, SynchronousOrder());

		
	NeuralNetworkIO<float> teachingPattern;

	teachingPattern[0] = std::vector<float>(1);
	teachingPattern[0][0] = 0;		
	teachingPattern[1] = std::vector<float>(1);
	teachingPattern[1][0] = 1;		
	teachingPattern[2] = std::vector<float>(1);
	teachingPattern[2][0] = 1;	
	teachingPattern[3] = std::vector<float>(1);
	teachingPattern[3][0] = 1;	
	teachingPattern[4] = std::vector<float>(1);
	teachingPattern[4][0] = 0;	
	teachingPattern[5] = std::vector<float>(1);
	teachingPattern[5][0] = 0;	

	std::unique_ptr<NeuralNetworkIO<float>> outputVector = neuralNetwork.calculate(teachingPattern, SynchronousOrder(), 0, 8);
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
				NeuralNetworkIO<float>* teachingPattern = new NeuralNetworkIO<float>();
				NeuralNetworkIO<bool>* teachingInput = new NeuralNetworkIO<bool>();

				for (int l = 0; l < 6; l++)
				{					
					(*teachingPattern)[l] = std::vector<float>(1);
					(*teachingPattern)[l][0] = (l%3==0 ? i : (l%3==1 ? j : k));		
				}

				(*teachingInput)[3] = std::vector<bool>(1);
				(*teachingInput)[3][0] = (i == j);

				(*teachingInput)[4] = std::vector<bool>(1);
				(*teachingInput)[4][0] = (j == k);	

				(*teachingInput)[5] = std::vector<bool>(1);
				(*teachingInput)[5][0] = (k == i);	

				(*teachingInput)[6] = std::vector<bool>(1);
				(*teachingInput)[6][0] = (i == j);

				(*teachingInput)[7] = std::vector<bool>(1);
				(*teachingInput)[7][0] = (j == k);	

				teacher.addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));	
			}
		}
	}
	

	learningRule.doLearning(neuralNetwork, teacher);
	float totalError = teacher.getTotalError(neuralNetwork, SynchronousOrder());


}


void doCascadeCorrelationTest()
{
	CascadeCorrelationNetwork* ccn = new CascadeCorrelationNetwork(2, 1);

	NeuralNetwork neuralNetwork(ccn);


	Teacher teacher;
	for (int i=0;i<8;i+=1)
	{
		for (int l=0;l<8;l+=1)
		{			
			NeuralNetworkIO<float>* teachingPattern = new NeuralNetworkIO<float>();
			NeuralNetworkIO<bool>* teachingInput= new NeuralNetworkIO<bool>();

			(*teachingPattern)[0] = std::vector<float>(2);
			(*teachingPattern)[0][0] = i;
			(*teachingPattern)[0][1] = l;
			(*teachingInput)[0] = std::vector<bool>(1);
			(*teachingInput)[0][0] = (i == l);	
			//(*teachingInput)[0] = (i > 0.4 && i < 0.8  && l> 0.4 && l< 0.8 ? 1 : 0);
			teacher.addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));
		}
	}

	CascadeCorrelationLearningRuleOptions options;
	options.enableDebugOutput = true;
	options.debugOutputInterval = 100;
	options.maxTotalErrorValue = 4;
	options.minIterationsPerTry = 300000;
	options.maxIterationsPerTry = 1000000;
	options.totalErrorGoal = 0.001f;
	options.minRandomWeightValue = -0.5;
	options.maxRandomWeightValue = 0.5;
	options.backpropagationLearningRuleOptions.resilientLearningRate = false;
	options.backpropagationLearningRuleOptions.learningRate = 0.45;
	CascadeCorrelationLearningRule learningRule(options);

	learningRule.doLearning(neuralNetwork, teacher);
}

int main()
{
	doCascadeCorrelationTest();
    return 0;
}