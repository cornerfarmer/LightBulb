#include "BackpropagationXorExample.hpp"
#include <NetworkTopology/LayeredNetwork.hpp>
#include <NeuralNetwork/NeuralNetwork.hpp>
#include <Learning/BackpropagationLearningRule.hpp>
#include <NeuronFactory/DifferentNeuronDescriptionFactory.hpp>
#include <Function/WeightedSumFunction.hpp>
#include <Teaching/TeachingLessonBooleanInput.hpp>
#include <Teaching/Teacher.hpp>
#include <ActivationOrder/TopologicalOrder.hpp>
#include <Function/FermiFunction.hpp>
#include <Neuron/NeuronDescription.hpp>
#include <Graphics/NeuralNetworkResultChart.hpp>


void doBackpropagationXorExample()
{
	LayeredNetworkOptions layeredNetworkOptions;
	layeredNetworkOptions.descriptionFactory = new DifferentNeuronDescriptionFactory(new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)), new NeuronDescription(new WeightedSumFunction(), new FermiFunction(1)));
	layeredNetworkOptions.neuronsPerLayerCount = std::vector<unsigned int>(3);
	layeredNetworkOptions.neuronsPerLayerCount[0] = 2;
	layeredNetworkOptions.neuronsPerLayerCount[1] = 2;
	layeredNetworkOptions.neuronsPerLayerCount[2] = 1;

	LayeredNetwork* layeredNetwork = new LayeredNetwork(layeredNetworkOptions);

	NeuralNetwork neuralNetwork(layeredNetwork);

	BackpropagationLearningRuleOptions options;
	options.enableDebugOutput = true;
	options.maxTotalErrorValue = 4;
	options.maxIterationsPerTry = 1000000;
	options.totalErrorGoal = 0.001f;
	options.maxTries = 1000;
	options.weightDecayFac = 0;
	options.learningRate = 0.1;
	options.momentum = 0;
	options.resilientLearningRate = false;
	BackpropagationLearningRule learningRule(options);

	Teacher teacher;
	for (int i = 0; i < 2; i += 1)
	{
		for (int l = 0; l < 2; l += 1)
		{
			std::vector<std::vector<double>> teachingPattern(1, std::vector<double>(2));
			NeuralNetworkIO<bool>* teachingInput = new NeuralNetworkIO<bool>(1);

			teachingPattern[0][0] = i;
			teachingPattern[0][1] = l;
			(*teachingInput).set(0, 0, (i != l));
			teacher.addTeachingLesson(new TeachingLessonBooleanInput(teachingPattern, teachingInput));
		}
	}
	clock_t begin = clock();
	bool success = learningRule.doLearning(neuralNetwork, teacher);
	clock_t end = clock();

	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "time: " << std::fixed << std::setprecision(5) << elapsed_secs << std::endl;

/*
	TopologicalOrder topologicalOrder;
	double totalError = teacher.getTotalError(neuralNetwork, topologicalOrder);

	std::vector<std::vector<double>>* input = new std::vector<std::vector<double>>(1, std::vector<double>(2));
	(*input)[0][0] = 8;
	(*input)[0][1] = 7;
	std::vector<std::vector<double>>* output = new std::vector<std::vector<double>>(1, std::vector<double>(1));

	neuralNetwork.calculate(*input, *output, topologicalOrder);

	NeuralNetworkResultChartOptions neuralNetworkResultChartOptions;
	neuralNetworkResultChartOptions.neuralNetwork = &neuralNetwork;
	neuralNetworkResultChartOptions.binaryInterpretation = true;
	neuralNetworkResultChartOptions.xRangeEnd = 100;
	neuralNetworkResultChartOptions.yRangeEnd = 100;
	neuralNetworkResultChartOptions.activationOrder = new TopologicalOrder();

	NeuralNetworkResultChart neuralNetworkResultChart(neuralNetworkResultChartOptions);
	neuralNetworkResultChart.recalculateAllValues();

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
		window.display();
	}*/

}
