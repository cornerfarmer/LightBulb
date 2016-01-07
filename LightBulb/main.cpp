// Includes
#include <Learning/Evolution/RemainderStochasticSamplingSelector.hpp>
#include "Function/WeightedSumFunction.hpp"
#include "Neuron/Edge.hpp"
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "NetworkTopology/LayeredNetwork.hpp"
#include "Function/WeightedSumFunction.hpp"
#include "Function/IdentityFunction.hpp"
#include "Function/HyperbolicTangentFunction.hpp"
#include "Function/FermiFunction.hpp"
#include "ActivationOrder/TopologicalOrder.hpp"
#include "Function/BinaryFunction.hpp"
#include "Learning/SingleLayerPerceptronLearningRule.hpp"
#include "Learning/DeltaLearningRule.hpp"
#include "Learning/BackpropagationLearningRule.hpp"
#include "Teaching/Teacher.hpp"
#include "Teaching/TeachingLessonBooleanInput.hpp"
#include "Graphics/NeuralNetworkResultChart.hpp"
#include "NeuronFactory/DifferentFunctionsNeuronFactory.hpp"
#include "NeuronFactory/SameFunctionsNeuronFactory.hpp"
#include "Neuron/StandardThreshold.hpp"
#include "NetworkTopology/RBFNetwork.hpp"
#include "Learning/RBFInterpolationLearningRule.hpp"
#include "Teaching/TeachingLessonLinearInput.hpp"
#include "Learning/DeltaLearningRule.hpp"
#include "ClusterAnalysis/KMeansRBFNeuronPlacer.hpp"
#include "ClusterAnalysis/KNearestRBFNeuronPlacer.hpp"
#include "ClusterAnalysis/ENearestRBFNeuronPlacer.hpp"
#include "Graphics/RBFNetworkStructureChart.hpp"
#include "ClusterAnalysis/ROLFNeuronPlacer.hpp"
#include "NeuralNetwork/NeuralNetworkIO.hpp"
#include "NetworkTopology/RecurrentLayeredNetwork.hpp"
#include "Learning/BackpropagationThroughTimeLearningRule.hpp"
#include "Graphics/LayeredNetworkTopologyDrawer.hpp"
#include "Learning/TruncatedBackpropagationThroughTimeLearningRule.hpp"
#include "NetworkTopology/FreeNetwork.hpp"
#include "ActivationOrder/SynchronousOrder.hpp"
#include "Graphics/FreeNetworkTopologyDrawer.hpp"
#include "Neuron/StandardNeuron.hpp"
#include "Learning/RealTimeRecurrentLearningRule.hpp"
#include "Learning/SchmidhuberLearningRule.hpp"
#include "NetworkTopology/CascadeCorrelationNetwork.hpp"
#include "Learning/CascadeCorrelationLearningRule.hpp"
#include "NetworkTopology/LVQNetwork.hpp"
#include "Learning/LVQ1LearningRule.hpp"
#include "Learning/LVQ2LearningRule.hpp"
#include "Learning/LVQ3LearningRule.hpp"
#include "Learning/OLVQ1LearningRule.hpp"
#include "Graphics/LVQNetworkStructureChart.hpp"
#include "NetworkTopology/SOMNetwork.hpp"
#include "NetworkTopology/LineStructure.hpp"
#include "NetworkTopology/GridStructure.hpp"
#include "Graphics/SOMNetworkStructureChart.hpp"
#include "Learning/SOMLearningRule.hpp"
#include "Function/GaussianRBFFunction.hpp"
#include "Function/CylinderFunction.hpp"
#include "Function/ConeFunction.hpp"
#include "Function/CosinusFunction.hpp"
#include "Function/MexicanHatFunction.hpp"
#include "Function/ExponentialShrinkFunction.hpp"
#include "Graphics/SOMMappingChart.hpp"
#include "NetworkTopology/CounterpropagationNetwork.hpp"
#include "Learning/CounterpropagationLearningRule.hpp"
#include "Graphics/CounterpropagationNetworkStructureChart.hpp"
#include "NetworkTopology/HopfieldNetwork.hpp"
#include "ActivationOrder/AsynchronousOrder.hpp"
#include "Learning/HopfieldLearningRule.hpp"
#include "Examples/Nature.hpp"
#include "Learning/Evolution/EvolutionLearningRule.hpp"
#include "Learning/Evolution/ConstantCreationCommand.hpp"
#include "Learning/Evolution/BestSelectionCommand.hpp"
#include "Learning/Evolution/BestReuseCommand.hpp"
#include "Learning/Evolution/ConstantMutationCommand.hpp"
#include "Learning/Evolution/Resilient/MutationCommand.hpp"
#include "Learning/Evolution/ConstantRecombinationCommand.hpp"
#include "Examples/TicTacToe.hpp"
#include "Examples/TicTacToeKI.hpp"
#include "Examples/FunctionSimulator.hpp"
#include "Examples/Position.hpp"
#include "Learning/Evolution/RateDifferenceCondition.hpp"
#include "Learning/Evolution/EvolutionStrategy/RecombinationAlgorithm.hpp"
#include "Learning/Evolution/EvolutionStrategy/MutationAlgorithm.hpp"
#include "Diagnostic/LearningRuleAnalyser.hpp"
#include "Diagnostic/ChangeableNumber.hpp"
#include "Diagnostic/ChangeablePointer.hpp"
#include "Examples/NetworkSimulator.hpp"
#include "Examples/Network.hpp"
#include "Learning/Evolution/TeachingEvolutionWorld.hpp"
#include "Learning/Evolution/LinearScalingFitnessFunction.hpp"
#include "Function/RankBasedRandomFunction.hpp"
#include "Function/EqualRandomFunction.hpp"
#include "Learning/Evolution/RandomSelector.hpp"
#include "Learning/Evolution/AbstractMutationSelector.hpp"
#include "Learning/Evolution/StochasticUniversalSamplingSelector.hpp"
#include "Learning/Evolution/PositiveMakerFitnessFunction.hpp"
#include "Learning/Evolution/FitnessSharingFitnessFunction.hpp"
#include "Learning/Evolution/TournamentCombiningStrategy.hpp"
#include "Learning/Evolution/RoundRobinCombiningStrategy.hpp"
#include "Learning/Evolution/ConstantCoevolutionFitnessFunction.hpp"
#include "Learning/Evolution/SharedCoevolutionFitnessFunction.hpp"
#include "Learning/Evolution/FullHallOfFameAlgorithm.hpp"
#include "Learning/Evolution/RandomHallOfFameAlgorithm.hpp"
#include "Learning/Evolution/RandomCombiningStrategy.hpp"
#include "Learning/Evolution/BipartiteEvolutionLearningRule.hpp"
#include "Learning/Evolution/SharedSamplingCombiningStrategy.hpp"
#include "NetworkTopology/FastLayeredNetwork.hpp"
#include <iostream>
#include <exception>
#include <vector>
#include <SFML/Graphics.hpp>

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

	TopologicalOrder topologicalOrder;
	double totalError = teacher.getTotalError(neuralNetwork, topologicalOrder);

	NeuralNetworkIO<double>* teachingPattern = new NeuralNetworkIO<double>(2);
	(*teachingPattern).set(0, 0, 8);
	(*teachingPattern).set(0,1, 7);

	std::unique_ptr<NeuralNetworkIO<double>> outputVector = neuralNetwork.calculate(*teachingPattern, topologicalOrder);
	

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
	SynchronousOrder synchonousOrder;
	double totalError = teacher.getTotalError(neuralNetwork, synchonousOrder);

	
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
		{
			SynchronousOrder synchronousOrder;
			networkTopologyDrawer.startNewCalculation(teachingPattern, synchronousOrder);
		} else if (t <= 4)
			networkTopologyDrawer.nextCalculationStep();
		else
		{
			networkTopologyDrawer.resetCalculation();
			t = -1;
		}
		t++;

		//Sleep(2000);
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
	SynchronousOrder synchronousOrder;
	double totalError = teacher.getTotalError(neuralNetwork, synchronousOrder);

		
	NeuralNetworkIO<double> teachingPattern(1);

	teachingPattern.set(0, 0, 0);		
	teachingPattern.set(1, 0, 1);		
	teachingPattern.set(2, 0, 1);	
	teachingPattern.set(3, 0, 1);	
	teachingPattern.set(4, 0, 0);	
	teachingPattern.set(5, 0, 0);	

	std::unique_ptr<NeuralNetworkIO<double>> outputVector = neuralNetwork.calculate(teachingPattern, synchronousOrder, 0, 8);
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

	SynchronousOrder synchronousOrder;
	double totalError = teacher.getTotalError(neuralNetwork, synchronousOrder);


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

	TopologicalOrder topologicalOrder;
	std::unique_ptr<NeuralNetworkIO<double>> output = neuralNetwork.calculate(*teachingPattern, topologicalOrder);

	
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
	TopologicalOrder topologicalOrder;
	std::unique_ptr<NeuralNetworkIO<double>> output = neuralNetwork.calculate(*(*teacher.getTeachingLessons())[15]->getTeachingPattern(), topologicalOrder);

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
	LVQNetwork* lvqNetwork = new LVQNetwork(2, 7, 3);

	NeuralNetwork neuralNetwork(lvqNetwork);

	Teacher teacher;

	for (double i = 0; i <= 1; i+=0.1)
	{
		for (double l = 0; l <= 1; l+=0.1)
		{
		
			NeuralNetworkIO<double>* teachingPattern = new NeuralNetworkIO<double>(2);
			NeuralNetworkIO<bool>* teachingInput= new NeuralNetworkIO<bool>(3);

			
			(*teachingPattern).set(0, 0, i);
			(*teachingPattern).set(0, 1, l);
			(*teachingInput).set(0, 0, i == l);	
			(*teachingInput).set(0, 1, i > l);	
			(*teachingInput).set(0, 2, i < l);	

			//(*teachingInput)[1] = teachingPattern->back()[0];	
		
			//(*teachingInput)[0] = (i > l);	
			//(*teachingInput)[0] = (i > 0.4 && i < 0.8  && l> 0.4 && l< 0.8 ? 1 : 0);			

			teacher.addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));	
		}
	}
	

	OLVQ1LearningRuleOptions options;
	options.enableDebugOutput = true;
	options.debugOutputInterval = 10;
	options.maxTotalErrorValue = 40;
	options.minIterationsPerTry = 300000;
	options.maxIterationsPerTry = 100000;
	options.maxTries = 100;
	options.totalErrorGoal = 9;
	options.minRandomWeightValue = 0;
	options.maxRandomWeightValue = 1;
	options.learningRateStart = 0.01;
	OLVQ1LearningRule learningRule(options);

	learningRule.doLearning(neuralNetwork, teacher);
	
	NeuralNetworkIO<double> input(2);

	input.set(0, 0, 1);
	input.set(0, 1, 0);
	
	LVQNetworkStructureChartOptions lvqetworkStructureChartOptions;
	lvqetworkStructureChartOptions.lvqNetwork = lvqNetwork;
	lvqetworkStructureChartOptions.yRangeEnd = 1;
	lvqetworkStructureChartOptions.xRangeEnd = 1;
	lvqetworkStructureChartOptions.posX = 300;
	lvqetworkStructureChartOptions.posY = 300;
	LVQNetworkStructureChart lvqNetworkStructureChart(lvqetworkStructureChartOptions);
	lvqNetworkStructureChart.recalculateAllValues();


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
        lvqNetworkStructureChart.draw(window);
        window.display();
    }
	
	NeuralNetworkResultChartOptions neuralNetworkResultChartOptions;
	neuralNetworkResultChartOptions.neuralNetwork = &neuralNetwork;
	neuralNetworkResultChartOptions.binaryInterpretation = false;
	neuralNetworkResultChartOptions.xRangeEnd = 1;
	neuralNetworkResultChartOptions.yRangeEnd = 1;
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
	networkTopologyDrawer.startNewCalculation(input, *new TopologicalOrder());
	networkTopologyDrawer.nextCalculationStep();

    

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

void doSOMTest()
{
	SOMNetwork* somNetwork = new SOMNetwork(2, 36, new GridStructure());	

	NeuralNetwork neuralNetwork(somNetwork);

	Teacher teacher;

	for (int i = 0; i < 200; i++)
	{
		double x = (double)rand() / RAND_MAX * 2 - 1;
		double y = (double)rand() / RAND_MAX * 2 - 1;

		if (sqrt(x * x + y * y) < 1)
		{
			NeuralNetworkIO<double>* teachingPattern = new NeuralNetworkIO<double>(2);
			NeuralNetworkIO<bool>* teachingInput= new NeuralNetworkIO<bool>(0);
			
			(*teachingPattern).set(0, 0, x);
			(*teachingPattern).set(0, 1, y);

			teacher.addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));			
		}
		else
			i--;
	}
	
	SOMLearningRuleOptions options;
	options.enableDebugOutput = true;
	options.debugOutputInterval = 10;
	options.maxTotalErrorValue = 40;
	options.minIterationsPerTry = 300000;
	options.maxIterationsPerTry = 1000;
	options.maxTries = 1;
	options.totalErrorGoal = -1;
	options.minRandomWeightValue = -1;
	options.maxRandomWeightValue = 1;
	options.learningRate  = 0.01;
	options.neighborhoodFunction = new GaussianRBFFunction();
	options.distanceShrinkFunction = new ExponentialShrinkFunction(4, 0.5, 200);
	SOMLearningRule learningRule(options);

	learningRule.doLearning(neuralNetwork, teacher);

	SOMNetworkStructureChartOptions somNetworkStructureChartOptions;
	somNetworkStructureChartOptions.somNetwork = somNetwork;
	somNetworkStructureChartOptions.posX = 300;
	somNetworkStructureChartOptions.posY = 300;
	somNetworkStructureChartOptions.xRangeStart = -1;
	somNetworkStructureChartOptions.yRangeStart = -1;
	SOMNetworkStructureChart somNetworkStructureChart(somNetworkStructureChartOptions);
	somNetworkStructureChart.recalculateAllValues();


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
        somNetworkStructureChart.draw(window);
        window.display();
    }
}

void doSOMColorTest()
{
	SOMNetwork* somNetwork = new SOMNetwork(3, 1600, new GridStructure());	

	NeuralNetwork neuralNetwork(somNetwork);

	Teacher teacher;

	for (int i = 0; i < 200; i++)
	{
		double r = (double)rand() / RAND_MAX * 255;
		double g = (double)rand() / RAND_MAX * 255;
		double b = (double)rand() / RAND_MAX * 255;

		NeuralNetworkIO<double>* teachingPattern = new NeuralNetworkIO<double>(3);
		NeuralNetworkIO<bool>* teachingInput= new NeuralNetworkIO<bool>(0);
			
		(*teachingPattern).set(0, 0, r);
		(*teachingPattern).set(0, 1, g);
		(*teachingPattern).set(0, 2, b);

		teacher.addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));			

	}
	
	SOMLearningRuleOptions options;
	options.enableDebugOutput = true;
	options.debugOutputInterval = 10;
	options.maxTotalErrorValue = 40;
	options.minIterationsPerTry = 300000;
	options.maxIterationsPerTry = 1000;
	options.maxTries = 1;
	options.totalErrorGoal = -1;
	options.minRandomWeightValue = -1;
	options.maxRandomWeightValue = 1;
	options.learningRate  = 0.01;
	options.neighborhoodFunction = new GaussianRBFFunction();
	options.distanceShrinkFunction = new ExponentialShrinkFunction(4, 0.5, 200);
	SOMLearningRule learningRule(options);

	learningRule.doLearning(neuralNetwork, teacher);

	SOMMappingChartOptions somMappingChartOptions;
	somMappingChartOptions.somNetwork = somNetwork;
	somMappingChartOptions.posX = 300;
	somMappingChartOptions.posY = 300;
	somMappingChartOptions.rRangeEnd = 255;
	somMappingChartOptions.gRangeEnd = 255;
	somMappingChartOptions.bRangeEnd = 255;
	SOMMappingChart somMappingChart(somMappingChartOptions);
	somMappingChart.recalculateAllValues();


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
        somMappingChart.draw(window);
        window.display();
    }
}

void doCounterpropagationTest()
{
	CounterpropagationNetwork* cpNetwork = new CounterpropagationNetwork(2, 4, 1);	

	NeuralNetwork neuralNetwork(cpNetwork);

	CounterpropagationLearningRuleOptions options;
	options.enableDebugOutput = true;
	options.debugOutputInterval = 100;
	options.maxTotalErrorValue = 4;
	options.minIterationsPerTry = 3000;
	options.maxIterationsPerTry = 10000;
	options.totalErrorGoal = 0.001f;
	options.maxTries = 1;
	options.minRandomWeightValue = -0.5;
	options.maxRandomWeightValue = 0.5;
	
	CounterpropagationLearningRule learningRule(options);

	Teacher teacher;
	for (int i=0;i<2;i+=1)
	{
		for (int l=0;l<2;l+=1)
		{			
			NeuralNetworkIO<double>* teachingPattern = new NeuralNetworkIO<double>(2);
			NeuralNetworkIO<double>* teachingInput= new NeuralNetworkIO<double>(1);

			(*teachingPattern).set(0, 0, i);
			(*teachingPattern).set(0, 1, l);
			(*teachingInput).set(0, 0, (i == l));	
			//(*teachingInput)[0] = (i > 0.4 && i < 0.8  && l> 0.4 && l< 0.8 ? 1 : 0);
			teacher.addTeachingLesson(new TeachingLessonLinearInput(teachingPattern, teachingInput));
		}
	}

	learningRule.doLearning(neuralNetwork, teacher);

	
	CounterpropagationNetworkStructureChartOptions counterpropagationNetworkStructureChartOptions;
	counterpropagationNetworkStructureChartOptions.network = cpNetwork;
	counterpropagationNetworkStructureChartOptions.yRangeEnd = 2;
	counterpropagationNetworkStructureChartOptions.xRangeEnd = 2;
	counterpropagationNetworkStructureChartOptions.posX = 300;
	counterpropagationNetworkStructureChartOptions.posY = 300;
	CounterpropagationNetworkStructureChart counterpropagationNetworkStructureChart(counterpropagationNetworkStructureChartOptions);
	counterpropagationNetworkStructureChart.recalculateAllValues();


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
        counterpropagationNetworkStructureChart.draw(window);
        window.display();
    }
}

void doHopfieldTest()
{
	HopfieldNetwork* hopfieldNetwork = new HopfieldNetwork(2, true);	

	NeuralNetwork neuralNetwork(hopfieldNetwork);

	
	HopfieldLearningRuleOptions options;
	options.enableDebugOutput = true;

	HopfieldLearningRule learningRule(options);


	Teacher teacher;
	for (int i=-1;i<2;i+=2)
	{
		NeuralNetworkIO<double>* teachingPattern = new NeuralNetworkIO<double>(2);
		NeuralNetworkIO<double>* teachingInput= new NeuralNetworkIO<double>(0);

		(*teachingPattern).set(0, 0, i);
		(*teachingPattern).set(0, 1, i);

		teacher.addTeachingLesson(new TeachingLessonLinearInput(teachingPattern, teachingInput));		
	}

	learningRule.doLearning(neuralNetwork, teacher);

	NeuralNetworkIO<double> teachingPattern(2);

	teachingPattern.set(0, 0, -4.1);
	teachingPattern.set(0, 1, 5.1);

	AsynchronousOrder asynchronousOrder;
	std::unique_ptr<NeuralNetworkIO<double>> outputVector = neuralNetwork.calculate(teachingPattern, asynchronousOrder, 0, 4);

}

void doAssociativHopfieldTest()
{
	HopfieldNetwork* hopfieldNetwork = new HopfieldNetwork(3, true);	

	NeuralNetwork neuralNetwork(hopfieldNetwork);

	
	HopfieldLearningRuleOptions options;
	options.enableDebugOutput = true;
	options.trainHeteroassociation = true;
	HopfieldLearningRule learningRule(options);


	Teacher teacher;
	for (int i=0;i<3;i+=1)
	{
		NeuralNetworkIO<double>* teachingPattern = new NeuralNetworkIO<double>(3);
		NeuralNetworkIO<double>* teachingInput= new NeuralNetworkIO<double>(3);

		(*teachingPattern).set(0, 0, i == 0 ? 1 : -1);
		(*teachingPattern).set(0, 1, i == 1 ? 1 : -1);
		(*teachingPattern).set(0, 2, i == 2 ? 1 : -1);

		if (i == 0)
		{
			(*teachingInput).set(0, 0, 1);
			(*teachingInput).set(0, 1, -1);
			(*teachingInput).set(0, 2, -1);
		}
		else if (i == 1)
		{
			(*teachingInput).set(0, 0, 1);
			(*teachingInput).set(0, 1, 1);
			(*teachingInput).set(0, 2, -1);
		}
		else if (i == 2)
		{
			(*teachingInput).set(0, 0, 1);
			(*teachingInput).set(0, 1, -1);
			(*teachingInput).set(0, 2, 1);
		}

		teacher.addTeachingLesson(new TeachingLessonLinearInput(teachingPattern, teachingInput));		
	}

	learningRule.doLearning(neuralNetwork, teacher);

	NeuralNetworkIO<double> teachingPattern(3);

	teachingPattern.set(0, 0, 0);
	teachingPattern.set(0, 1, 1);
	teachingPattern.set(0, 2, 0);

	AsynchronousOrder asynchronousOrder;
	std::unique_ptr<NeuralNetworkIO<double>> outputVector = neuralNetwork.calculate(teachingPattern, asynchronousOrder, 0, 4);

}

void doEvolutionTest()
{
	Nature nature;

	EvolutionLearningRuleOptions options;
	options.creationCommands.push_back(new ConstantCreationCommand(40));
	options.selectionCommands.push_back(new BestSelectionCommand(5));
	options.mutationsCommands.push_back(new ConstantMutationCommand(new MutationAlgorithm(1.6), new RemainderStochasticSamplingSelector(), 23));
	options.recombinationCommands.push_back(new ConstantRecombinationCommand(new RecombinationAlgorithm(), new RemainderStochasticSamplingSelector(), 9));
	options.world = &nature;

	EvolutionLearningRule learningRule(options);

	learningRule.doLearning();
}

void doTicTacToeTest()
{
	SharedSamplingCombiningStrategy* cs1 = new SharedSamplingCombiningStrategy(100);
	SharedSamplingCombiningStrategy* cs2 = new SharedSamplingCombiningStrategy(100, cs1);
	cs1->setOtherCombiningStrategy(cs2);

	AbstractHallOfFameAlgorithm* hof1 = new RandomHallOfFameAlgorithm(100);
	AbstractHallOfFameAlgorithm* hof2 = new RandomHallOfFameAlgorithm(100);

	TicTacToe ticTacToe1(false, cs1, new SharedCoevolutionFitnessFunction(), hof1, hof2);
	TicTacToe ticTacToe2(true, cs2, new SharedCoevolutionFitnessFunction(), hof2, hof1);
	cs1->setSecondWorld(&ticTacToe2);
	cs2->setSecondWorld(&ticTacToe1);

	//ticTacToe.setDebugOutput(false);

	EvolutionLearningRuleOptions options;

	options.creationCommands.push_back(new ConstantCreationCommand(800));
	options.exitConditions.push_back(new RateDifferenceCondition(1000, 150000));
	options.reuseCommands.push_back(new BestReuseCommand(16));
	options.selectionCommands.push_back(new BestSelectionCommand(800, true));
	options.mutationsCommands.push_back(new ConstantMutationCommand(new MutationAlgorithm(1.6), new RandomSelector(new RankBasedRandomFunction()), 1.8, false));
	options.recombinationCommands.push_back(new ConstantRecombinationCommand(new RecombinationAlgorithm(), new RandomSelector(new RankBasedRandomFunction()), 0.3, false));
	//options.fitnessFunctions.push_back(new FitnessSharingFitnessFunction(150));
	options.world = &ticTacToe1;
	
	//options.recombinationCommands.push_back(new ConstantRecombinationCommand(7));

	EvolutionLearningRule learningRule1(options);
	options.world = &ticTacToe2;
	EvolutionLearningRule learningRule2(options);

	BipartiteEvolutionLearningRule learningRule(&learningRule1, &learningRule2);
#define TICTACTOE_SINGLE
#ifdef TICTACTOE_SINGLE
	LearningResult result = learningRule.doLearning();
	std::cout << "total generations: " << result.iterationsNeeded << std::endl;

#else
	ticTacToe.setDebugOutput(false);
	LearningRuleAnalyserOptions analyserOptions;
	analyserOptions.learningRule = &learningRule;
	analyserOptions.changableParameters.push_back(new ChangeableNumber<double, TicTacToe>(&ticTacToe, &TicTacToe::setMaxDistanceShrinkFactor, 0.5, 0.1, 0.9, "shr"));

	analyserOptions.calculationsPerParameterCombination = 1;
	analyserOptions.useQualityInsteadOfSuccessful = true;

	LearningRuleAnalyser learningRuleAnalyser(analyserOptions);

	learningRuleAnalyser.execute();
#endif

	TicTacToeDrawerOptions ticTacToeDrawerOptions;
	ticTacToeDrawerOptions.width = 600;
	ticTacToeDrawerOptions.height = 600;
	ticTacToeDrawerOptions.ticTacToe = &ticTacToe1;
	TicTacToeDrawer ticTacToeDrawer(ticTacToeDrawerOptions);

    sf::RenderWindow window(sf::VideoMode(1300, 1000), "LightBulb!");

	TicTacToeKI* bestAI = static_cast<TicTacToeKI*>(ticTacToe1.getHighscoreList()->front().second);// ticTacToe.getBestAIs()->back();
	


	AbstractNetworkTopologyDrawerOptions networkTopologyDrawerOptions;
	networkTopologyDrawerOptions.width = 700;
	networkTopologyDrawerOptions.height = 1000;
	networkTopologyDrawerOptions.posX = 600;
	networkTopologyDrawerOptions.network = bestAI->getNeuralNetwork();
	//LayeredNetworkTopologyDrawer networkTopologyDrawer(networkTopologyDrawerOptions);
	//networkTopologyDrawer.refresh();


    ticTacToe1.startNewGame(1);
    bestAI->resetNN();
	while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
            	if (ticTacToe1.hasGameFinished()) {
            		ticTacToe1.startNewGame(1);
            		bestAI->resetNN();
            	}
            	else if (ticTacToeDrawer.handleMouseInputEvent(event)) {
            		if (!ticTacToe1.hasGameFinished()) {
            			bestAI->doNNCalculation();
            			if (ticTacToe1.hasGameFinished())
            				std::cout << "AI has failed" << std::endl;
            		}
            		else
            			std::cout << "Player has failed" << std::endl;
            	}
            }
        }

        window.clear();
        ticTacToeDrawer.recalculateAllValues();
        ticTacToeDrawer.draw(window);
        //networkTopologyDrawer.draw(window);
        window.display();
    }


}

static double sixHumpCamelFunction(std::vector<float> pos)
{
	return std::max(0.0, -1 * (4 * pow(pos[0], 2) - 2.1 * pow(pos[0], 4) + pow(pos[0], 6) / 3 + pos[0] * pos[1] - 4 * pow(pos[1], 2) + 4 * pow(pos[1], 4)) + 10000);
}

static double threeHumpCamelFunction(std::vector<float> pos)
{
	return  -1 * (2 * pow(pos[0], 2) - 1.05 * pow(pos[0], 4) + pow(pos[0], 6) / 6 + pos[0] * pos[1] + pow(pos[1], 2));
}

void doFunctionEvolutionTest()
{
	FunctionSimulatorOptions simulatorOptions;
	simulatorOptions.enableGraphics = false;

	FunctionSimulator simulator(simulatorOptions, sixHumpCamelFunction);

	EvolutionLearningRuleOptions options;
	RateDifferenceCondition* rateDifferenceCondition = new RateDifferenceCondition(0.00001, 10);
	options.exitConditions.push_back(rateDifferenceCondition);
	ConstantCreationCommand* constantCreationCommand = new ConstantCreationCommand(20);
	options.creationCommands.push_back(constantCreationCommand);
	options.reuseCommands.push_back(new BestReuseCommand(1));
	BestSelectionCommand* bestSelectionCommand = new BestSelectionCommand(20);
	options.selectionCommands.push_back(bestSelectionCommand);
	MutationAlgorithm* mutationAlgorithm = new MutationAlgorithm(1.6);
	//MutationCommand* constantMutationCommand = new MutationCommand();
	ConstantMutationCommand* constantMutationCommand = new ConstantMutationCommand(mutationAlgorithm, new StochasticUniversalSamplingSelector(), 1.8, false);
	options.mutationsCommands.push_back(constantMutationCommand);
	ConstantRecombinationCommand* constantRecombinationCommand = new ConstantRecombinationCommand(new RecombinationAlgorithm(), new StochasticUniversalSamplingSelector(), 0.3, false);
	options.recombinationCommands.push_back(constantRecombinationCommand);
	options.world = &simulator;
	options.enableDebugOutput = false;
	options.scoreGoal = 1.031627 + 10000;
	//options.scoreGoal = -0.000001;
	EvolutionLearningRule learningRule(options);

//	int iterations = 0;
//	for (int i = 0; i < 20; i++)
//	{
//		iterations += learningRule.doLearning().iterationsNeeded;
//	}
//	std::cout << "Average " << iterations/20;
//	return;

	LearningRuleAnalyserOptions analyserOptions;
	analyserOptions.learningRule = &learningRule;
	//analyserOptions.changableParameters.push_back(new ChangeableNumber<double, MutationAlgorithm>(mutationAlgorithm, &MutationAlgorithm::setMutationStrengthChangeSpeed, 1.3, 0.1, 2.0, "mcs"));
	//analyserOptions.changableParameters.push_back(new ChangeableNumber<int, RateDifferenceCondition>(rateDifferenceCondition, &RateDifferenceCondition::setCount, 0, 10, 50, "cnt"));
	//analyserOptions.changableParameters.push_back(new ChangeableNumber<int, BestSelectionCommand>(bestSelectionCommand, &BestSelectionCommand::setObjectCount, 5, 5, 40, "sel"));
	analyserOptions.changableParameters.push_back(new ChangeableNumber<double, ConstantMutationCommand>(constantMutationCommand, &ConstantMutationCommand::setMutationPercentage, 0, 0.3, 2.0, "mut"));
	analyserOptions.changableParameters.push_back(new ChangeableNumber<double, ConstantRecombinationCommand>(constantRecombinationCommand, &ConstantRecombinationCommand::setRecombinationPercentage, 0, 0.3, 2.0, "rcb"));

	std::vector<std::pair<std::string, AbstractMutationSelector*>> possibleMutationSelectors;
	possibleMutationSelectors.push_back(std::make_pair<std::string, AbstractMutationSelector*>("rank", new RandomSelector(new RankBasedRandomFunction())));
	possibleMutationSelectors.push_back(std::make_pair<std::string, AbstractMutationSelector*>("equa", new RandomSelector(new EqualRandomFunction())));
	possibleMutationSelectors.push_back(std::make_pair<std::string, AbstractMutationSelector*>("rema", new RemainderStochasticSamplingSelector()));
	possibleMutationSelectors.push_back(std::make_pair<std::string, AbstractMutationSelector*>("stoc", new StochasticUniversalSamplingSelector()));

	analyserOptions.changableParameters.push_back(new ChangeablePointer<AbstractMutationSelector, ConstantMutationCommand>(constantMutationCommand, &ConstantMutationCommand::setMutationSelector, possibleMutationSelectors, "sel"));


	LearningRuleAnalyser learningRuleAnalyser(analyserOptions);

	learningRuleAnalyser.execute();
}


void doNetworkEvolutionTest()
{
	std::vector<std::vector<float>> consumers(8, std::vector<float>(2));
	consumers[0][0] = 1;
	consumers[0][1] = 1;
	consumers[1][0] = 1;
	consumers[1][1] = -1;

	consumers[2][0] = 2;
	consumers[2][1] = 1;
	consumers[3][0] = 2;
	consumers[3][1] = -1;

	consumers[4][0] = 3;
	consumers[4][1] = 1;
	consumers[5][0] = 3;
	consumers[5][1] = -1;

	consumers[6][0] = 4;
	consumers[6][1] = 1;
	consumers[7][0] = 4;
	consumers[7][1] = -1;

	NetworkSimulator simulator(false, consumers);

	EvolutionLearningRuleOptions options;
	RateDifferenceCondition* rateDifferenceCondition = new RateDifferenceCondition(0.00001, 10);
	options.exitConditions.push_back(rateDifferenceCondition);
	ConstantCreationCommand* constantCreationCommand = new ConstantCreationCommand(20);
	options.creationCommands.push_back(constantCreationCommand);
	options.reuseCommands.push_back(new BestReuseCommand(1));
	BestSelectionCommand* bestSelectionCommand = new BestSelectionCommand(20);
	options.selectionCommands.push_back(bestSelectionCommand);
	MutationAlgorithm* mutationAlgorithm = new MutationAlgorithm(1.6);
	ConstantMutationCommand* constantMutationCommand = new ConstantMutationCommand(mutationAlgorithm, new RemainderStochasticSamplingSelector(), 2.0);
	options.mutationsCommands.push_back(constantMutationCommand);
	options.recombinationCommands.push_back(new ConstantRecombinationCommand(new RecombinationAlgorithm(), new RemainderStochasticSamplingSelector(), 0));
	options.world = &simulator;
	options.enableDebugOutput = false;
	options.scoreGoal = -10.47;
	EvolutionLearningRule learningRule(options);

	LearningRuleAnalyserOptions analyserOptions;
	analyserOptions.learningRule = &learningRule;
	analyserOptions.changableParameters.push_back(new ChangeableNumber<double, MutationAlgorithm>(mutationAlgorithm, &MutationAlgorithm::setMutationStrengthChangeSpeed, 1.3, 0.1, 2.0, "mcs"));
	analyserOptions.changableParameters.push_back(new ChangeableNumber<int, RateDifferenceCondition>(rateDifferenceCondition, &RateDifferenceCondition::setCount, 0, 10, 50, "cnt"));

	LearningRuleAnalyser learningRuleAnalyser(analyserOptions);

	learningRuleAnalyser.execute();

}



void doTeachedEvolution838Test() {
	LayeredNetworkOptions layeredNetworkOptions;
	layeredNetworkOptions.neuronFactory = new DifferentFunctionsNeuronFactory(new StandardThreshold(0), new WeightedSumFunction(), new FermiFunction(1), new IdentityFunction(),
																				new StandardThreshold(0), new WeightedSumFunction(), new FermiFunction(1), new IdentityFunction());
	layeredNetworkOptions.neuronsPerLayerCount = std::vector<unsigned int>(3);
	layeredNetworkOptions.neuronsPerLayerCount[0]=8;
	layeredNetworkOptions.neuronsPerLayerCount[1]=3;
	layeredNetworkOptions.neuronsPerLayerCount[2]=8;
	layeredNetworkOptions.useBiasNeuron = true;


	Teacher teacher;
	for (int i=0;i<8;i+=1)
	{
		NeuralNetworkIO<double>* teachingPattern = new NeuralNetworkIO<double>(8);
		NeuralNetworkIO<bool>* teachingInput= new NeuralNetworkIO<bool>(8);
		for (int l=0;l<8;l+=1)
		{
			(*teachingPattern).set(0, l, i == l);
			(*teachingInput).set(0, l, i == l);
		}

		teacher.addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));
	}
	/*for (int i=0;i<80;i+=5)
	{
		for (int l=0;l<80;l+=5)
		{
			NeuralNetworkIO<double>* teachingPattern = new NeuralNetworkIO<double>(2);
			NeuralNetworkIO<bool>* teachingInput= new NeuralNetworkIO<bool>(1);
			(*teachingPattern).set(0, 0, i);
			(*teachingPattern).set(0, 1, l);
			(*teachingInput).set(0, 0, i == l);
			teacher.addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));
		}
	}*/

	LayeredNetwork layeredNetwork(layeredNetworkOptions);

	NeuralNetwork neuralNetwork(&layeredNetwork);

	BackpropagationLearningRuleOptions bOptions;
	bOptions.enableDebugOutput = true;
	bOptions.debugOutputInterval = 100;
	bOptions.maxTotalErrorValue = 4;
	bOptions.minIterationsPerTry = 3000;
	bOptions.maxIterationsPerTry = 1000000;
	bOptions.totalErrorGoal = 0.001f;
	bOptions.maxTries = 1000;
	bOptions.minRandomWeightValue = -0.5;
	bOptions.maxRandomWeightValue = 0.5;
	bOptions.weightDecayFac = 0;
	bOptions.resilientLearningRate = false;
//	options.maxTimeSteps = 1;
	BackpropagationLearningRule bLearningRule(bOptions);

	//bLearningRule.doLearning(neuralNetwork, teacher);

	TeachingEvolutionWorld world(&teacher, layeredNetworkOptions);

	EvolutionLearningRuleOptions options;
	RateDifferenceCondition* rateDifferenceCondition = new RateDifferenceCondition(0.00001, 50, true);
	options.exitConditions.push_back(rateDifferenceCondition);
	ConstantCreationCommand* constantCreationCommand = new ConstantCreationCommand(80);
	options.creationCommands.push_back(constantCreationCommand);
	options.reuseCommands.push_back(new BestReuseCommand(1));
	BestSelectionCommand* bestSelectionCommand = new BestSelectionCommand(80);
	options.selectionCommands.push_back(bestSelectionCommand);
	MutationAlgorithm* mutationAlgorithm = new MutationAlgorithm(1.6);
	ConstantMutationCommand* constantMutationCommand = new ConstantMutationCommand(mutationAlgorithm, new RandomSelector(new RankBasedRandomFunction()), 2.0);
	options.mutationsCommands.push_back(constantMutationCommand);
	options.recombinationCommands.push_back(new ConstantRecombinationCommand(new RecombinationAlgorithm(), new RandomSelector(new RankBasedRandomFunction()), 0));
	options.world = &world;
	options.enableDebugOutput = true;
	options.scoreGoal = -0.1;
	options.maxTries = 100;
	EvolutionLearningRule learningRule(options);

	LearningRuleAnalyserOptions analyserOptions;
	analyserOptions.learningRule = &learningRule;
	analyserOptions.calculationsPerParameterCombination = 2;
	analyserOptions.changableParameters.push_back(new ChangeableNumber<double, MutationAlgorithm>(mutationAlgorithm, &MutationAlgorithm::setMutationStrengthChangeSpeed, 0.1, 0.4, 2.0, "mcs"));
	analyserOptions.changableParameters.push_back(new ChangeableNumber<int, RateDifferenceCondition>(rateDifferenceCondition, &RateDifferenceCondition::setCount, 10, 20, 100, "cnt"));

	LearningRuleAnalyser learningRuleAnalyser(analyserOptions);

	//learningRuleAnalyser.execute();
	learningRule.doLearning();

	NeuralNetwork* bestNetwork =  world.getEvolutionObjects()->front()->getNeuralNetwork();

	TopologicalOrder topologicalOrder;
	double totalError = teacher.getTotalError(*bestNetwork, topologicalOrder);

	NeuralNetworkIO<double>* teachingPattern = new NeuralNetworkIO<double>(2);
	(*teachingPattern).set(0, 0, 10);
	(*teachingPattern).set(0, 1, 10);

	std::unique_ptr<NeuralNetworkIO<double>> outputVector = bestNetwork->calculate(*teachingPattern, topologicalOrder);

	std::cout << "end";

	NeuralNetworkResultChartOptions neuralNetworkResultChartOptions;
	neuralNetworkResultChartOptions.neuralNetwork = bestNetwork;
	neuralNetworkResultChartOptions.binaryInterpretation = true;
	neuralNetworkResultChartOptions.xRangeEnd = 1000;
	neuralNetworkResultChartOptions.yRangeEnd = 1000;
	neuralNetworkResultChartOptions.activationOrder = new TopologicalOrder();

	NeuralNetworkResultChart neuralNetworkResultChart(neuralNetworkResultChartOptions);
	neuralNetworkResultChart.recalculateAllValues();


	AbstractNetworkTopologyDrawerOptions networkTopologyDrawerOptions;
	networkTopologyDrawerOptions.width = 700;
	networkTopologyDrawerOptions.height = 600;
	networkTopologyDrawerOptions.posY = 100;
	networkTopologyDrawerOptions.network = bestNetwork;
	LayeredNetworkTopologyDrawer networkTopologyDrawer(networkTopologyDrawerOptions);
	networkTopologyDrawer.refresh();

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

void doCompare()
{
	LayeredNetworkOptions layeredNetworkOptions;
	layeredNetworkOptions.neuronFactory = new SameFunctionsNeuronFactory(new StandardThreshold(0), new WeightedSumFunction(), new BinaryFunction(), new IdentityFunction());
	layeredNetworkOptions.neuronsPerLayerCount = std::vector<unsigned int>(3);
	layeredNetworkOptions.neuronsPerLayerCount[0]=8;
	layeredNetworkOptions.neuronsPerLayerCount[1]=3;
	layeredNetworkOptions.neuronsPerLayerCount[2]=8;
	layeredNetworkOptions.useBiasNeuron = true;

	LayeredNetwork layeredNetwork(layeredNetworkOptions);

	NeuralNetwork neuralNetwork(&layeredNetwork);

	FastLayeredNetworkOptions fastLayeredNetworkOptions;
	fastLayeredNetworkOptions.activationFunction = new BinaryFunction();
	fastLayeredNetworkOptions.threshold = new StandardThreshold(0);
	fastLayeredNetworkOptions.inputFunction = new WeightedSumFunction();
	fastLayeredNetworkOptions.outputFunction = new IdentityFunction();
	fastLayeredNetworkOptions.neuronsPerLayerCount = std::vector<unsigned int>(3);
	fastLayeredNetworkOptions.neuronsPerLayerCount[0]=8;
	fastLayeredNetworkOptions.neuronsPerLayerCount[1]=3;
	fastLayeredNetworkOptions.neuronsPerLayerCount[2]=8;
	fastLayeredNetworkOptions.useBiasNeuron = true;

	FastLayeredNetwork fastLayeredNetwork(fastLayeredNetworkOptions);

	NeuralNetwork fastNeuralNetwork(&fastLayeredNetwork);

	NeuralNetworkIO<double> input(8);
	input.set(0, 0, 1);
	input.set(0, 1, 1);
	input.set(0, 2, 2);
	input.set(0, 3, 1);
	input.set(0, 4, 0.5);
	input.set(0, 5, 1);
	input.set(0, 6, 3);
	input.set(0, 7, 0);

	TopologicalOrder topologicalOrder;

	clock_t begin = clock();
	for (int i = 0; i < 1000000; i++)
		NeuralNetworkIO<double>* output = neuralNetwork.calculate(input, topologicalOrder).get();
	clock_t end = clock();

	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	begin = clock();
	NeuralNetworkIO<double> fastOutput(fastLayeredNetwork.getOutputSize());
	for (int i = 0; i < 1000000; i++)
	{
		fastNeuralNetwork.calculate(input, fastOutput, topologicalOrder);
	}
	end = clock();

	double fastelapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	std::cout << "normal: " << std::fixed << std::setprecision(5) << elapsed_secs << std::endl;
	std::cout << "fast: " << std::fixed << std::setprecision(5) << fastelapsed_secs << std::endl;

	fastelapsed_secs = 0;
}


int main()
{
	doTicTacToeTest();
    return 0;
}
