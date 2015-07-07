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
#include "DeltaLearningRule.hpp"
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

	float twoSpiralValues[][3] = 
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
		NeuralNetworkIO<float>* teachingPattern = new NeuralNetworkIO<float>();
		NeuralNetworkIO<bool>* teachingInput= new NeuralNetworkIO<bool>();

		(*teachingPattern)[0] = std::vector<float>(2);
		(*teachingPattern)[0][0] = twoSpiralValues[i][0];
		(*teachingPattern)[0][1] = twoSpiralValues[i][1];
		(*teachingInput)[0] = std::vector<bool>(1);
		(*teachingInput)[0][0] = (twoSpiralValues[i][2] == 1);//(i > 0.4 && i < 0.8  && l> 0.4 && l< 0.8 ? 1 : 0);
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

void doRecurrentCascadeCorrelationTest()
{
	CascadeCorrelationNetwork* ccn = new CascadeCorrelationNetwork(1, 1);

	NeuralNetwork neuralNetwork(ccn);


	Teacher teacher;

	{
		
		NeuralNetworkIO<float>* teachingPattern = new NeuralNetworkIO<float>();
		NeuralNetworkIO<bool>* teachingInput= new NeuralNetworkIO<bool>();

		int lastPattern = -1;
		for (int l = 0; l < 6; l++)
		{
			(*teachingPattern)[l] = std::vector<float>(1);
			(*teachingPattern)[l][0] = 1;
			(*teachingInput)[l] = std::vector<bool>(1);
			(*teachingInput)[l][0] = (l%2 == 0);	
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


	NeuralNetworkIO<float>* teachingPattern = new NeuralNetworkIO<float>();

	int lastPattern = -1;
	for (int l = 0; l < 16; l++)
	{
		(*teachingPattern)[l] = std::vector<float>(1);
		(*teachingPattern)[l][0] = 1;
	}

	std::unique_ptr<NeuralNetworkIO<float>> output = neuralNetwork.calculate(*teachingPattern, TopologicalOrder());

	
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

int main()
{
	doRecurrentLayeredNetworkTest();
    return 0;
}