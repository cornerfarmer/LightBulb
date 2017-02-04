#include "LightBulbApp/App.hpp"
#include "LightBulbApp/Windows/TrainingController.hpp"
#include "LightBulbApp/Repositories/NeuralNetworkRepository.hpp"
#include "LightBulbApp/Repositories/TrainingPlanRepository.hpp"
#include "LightBulbApp/Windows/LearningStateFactory.hpp"
#include "LightBulbApp/Windows/SimulatorFactory.hpp"
#include "LightBulbApp/Windows/LoggerFactory.hpp"
#include "LightBulbApp/Windows/NetworkViewerFactory.hpp"
#include "LightBulbApp/Windows/EvolutionAnalyzerFactory.hpp"
#include "LightBulbApp/TrainingPlans/AbstractTrainingPlan.hpp"
#include "LightBulb/IO/Exporter/BrainJSExporter.hpp"
#include "LightBulb/IO/Exporter/SynapticExporter.hpp"

namespace LightBulb
{
	bool App::OnInit()
	{
		neuralNetworkRepository.reset(new NeuralNetworkRepository());
		trainingPlanRepository.reset(new TrainingPlanRepository());

		trainingController.reset(new TrainingController(*neuralNetworkRepository, *trainingPlanRepository, trainingPlans));
		trainingPlans.clear();
		LoggerFactory* loggerFactory = new LoggerFactory(*trainingPlanRepository);
		SimulatorFactory* simulatorFactory = new SimulatorFactory(*neuralNetworkRepository);
		LearningStateFactory* learningStateFactory = new LearningStateFactory(*trainingPlanRepository);
		NetworkViewerFactory* networkViewerFactory = new NetworkViewerFactory(*neuralNetworkRepository);
		EvolutionAnalyzerFactory* evolutionAnalyzerFactory = new EvolutionAnalyzerFactory(*trainingPlanRepository);

		trainingController->addSubAppFactory(loggerFactory);
		trainingController->addSubAppFactory(simulatorFactory);
		trainingController->addSubAppFactory(learningStateFactory);
		trainingController->addSubAppFactory(networkViewerFactory);
		trainingController->addSubAppFactory(evolutionAnalyzerFactory);

		trainingController->addNetworkExporter(new BrainJSExporter());
		trainingController->addNetworkExporter(new SynapticExporter());

		trainingController->show();
		return true;
	}

	void App::OnUnhandledException()
	{
		throw;
	}

	bool App::OnExceptionInMainLoop()
	{
		throw;
	}

	App::~App() = default;
	
	App::App() = default;

	void App::addTrainingPlan(AbstractTrainingPlan* trainingPlan)
	{
		trainingPlans.push_back(trainingPlan);
	}
}
