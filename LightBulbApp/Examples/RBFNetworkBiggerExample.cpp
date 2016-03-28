#include "RBFNetworkBiggerExample.hpp"
#include <SFML/Window/Event.hpp>
#include <Graphics/RBFNetworkStructureChart.hpp>
#include <Graphics/NeuralNetworkResultChart.hpp>
#include <ClusterAnalysis/ROLFNeuronPlacer.hpp>
#include <Learning/RBFInterpolationLearningRule.hpp>
#include <Learning/DeltaLearningRule.hpp>
#include <ActivationOrder/TopologicalOrder.hpp>
#include <NeuralNetwork/NeuralNetworkIO.hpp>
#include <Teaching/TeachingLessonLinearInput.hpp>
#include <NetworkTopology/RBFNetwork.hpp>
#include <NeuralNetwork/NeuralNetwork.hpp>
#include <Teaching/Teacher.hpp>
#include <ClusterAnalysis/KMeansRBFNeuronPlacer.hpp>


void doRBFNetworkBiggerExample()
{
	RBFNetwork* rbfNetwork = new RBFNetwork(2, 32, 1);

	NeuralNetwork neuralNetwork(rbfNetwork);

	Teacher teacher;
	for (int i = 0; i <= 20; i += 1)
	{
		for (int l = 0; l <= 20; l += 1)
		{
			std::vector<std::vector<double>> teachingPattern(1, std::vector<double>(2));
			NeuralNetworkIO<double>* teachingInput = new NeuralNetworkIO<double>(1);

			teachingPattern[0][0] = i;
			teachingPattern[0][1] = l;
			(*teachingInput).set(0, 0, (i > l));

			teacher.addTeachingLesson(new TeachingLessonLinearInput(teachingPattern, teachingInput));
		}
	}

	RBFInterpolationLearningRuleOptions learningRuleOptions;
	learningRuleOptions.offlineLearning = true;
	learningRuleOptions.totalErrorGoal = 2;
	learningRuleOptions.maxTotalErrorValue = 5;
	learningRuleOptions.maxTries = 1;
	learningRuleOptions.neuronPlacer = new KMeansRBFNeuronPlacer();
	RBFInterpolationLearningRule learningRule(learningRuleOptions);

	TopologicalOrder topologicalOrder;

	learningRule.doLearning(neuralNetwork, teacher);

	DeltaLearningRuleOptions delteLearningRuleOptions;
	delteLearningRuleOptions.maxIterationsPerTry = 100000;
	delteLearningRuleOptions.maxTries = 1;
	delteLearningRuleOptions.totalErrorGoal = 2;
	delteLearningRuleOptions.maxTotalErrorValue = 5;
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
