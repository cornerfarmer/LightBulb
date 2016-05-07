// Includes
#include "TrainingPlanRepository.hpp"
#include <fstream>
#include <cereal/archives/xml.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>
#include <TrainingPlans/AbstractSingleNNTrainingPlan.hpp>

int TrainingPlanRepository::getIndexOfTrainingPlan(AbstractTrainingPlan* trainingPlan)
{
	for (int i = 0; i < trainingPlans.size(); i++)
	{
		if (trainingPlans[i].get() == trainingPlan)
			return i;
	}
	return -1;
}

void TrainingPlanRepository::Add(AbstractTrainingPlan* trainingPlan)
{
	trainingPlans.push_back(std::unique_ptr<AbstractTrainingPlan>(trainingPlan));
	throwEvent(EVT_TP_CHANGED, this);
}

void TrainingPlanRepository::save(std::string path, int trainingPlanIndex)
{
	std::ofstream os(path);
	cereal::XMLOutputArchive archive(os);

	onlyUseNeuralNetworkIndex = false;
	archive(trainingPlans[trainingPlanIndex]);
}

AbstractTrainingPlan* TrainingPlanRepository::load(std::string path)
{
	std::ifstream is(path);
	cereal::XMLInputArchive archive(is);

	trainingPlans.push_back(std::unique_ptr<AbstractTrainingPlan>());
	archive(trainingPlans.back());

	throwEvent(EVT_TP_CHANGED, this);

	return trainingPlans.back().get();
}

AbstractTrainingPlan* TrainingPlanRepository::getByName(std::string name)
{
	for (int i = 0; i < trainingPlans.size(); i++)
	{
		if (trainingPlans[i]->getName() == name)
			return trainingPlans[i].get();
	}
	return NULL;
}

void TrainingPlanRepository::setTrainingPlanName(int trainingPlanIndex, std::string newName)
{
	trainingPlans[trainingPlanIndex]->setName(newName);
	throwEvent(EVT_TP_CHANGED, this);
}

std::vector<std::unique_ptr<AbstractTrainingPlan>>* TrainingPlanRepository::getTrainingPlans()
{
	return &trainingPlans;
}
