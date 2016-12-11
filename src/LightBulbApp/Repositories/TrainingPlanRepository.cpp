// Includes
#include "LightBulbApp/Repositories/TrainingPlanRepository.hpp"
#include <fstream>
#include "LightBulb/IO/UsedArchives.hpp"
#include <cereal/types/memory.hpp>
#include <cereal/types/polymorphic.hpp>
#include "LightBulbApp/TrainingPlans/AbstractSupervisedTrainingPlan.hpp"

namespace LightBulb
{
	int TrainingPlanRepository::getIndexOfTrainingPlan(const AbstractTrainingPlan& trainingPlan) const
	{
		for (int i = 0; i < trainingPlans.size(); i++)
		{
			if (trainingPlans[i].get() == &trainingPlan)
				return i;
		}
		return -1;
	}

	void TrainingPlanRepository::Add(AbstractTrainingPlan* trainingPlan)
	{
		trainingPlans.push_back(std::unique_ptr<AbstractTrainingPlan>(trainingPlan));
		throwEvent(EVT_TP_CHANGED, *this);
	}

	void TrainingPlanRepository::save(const std::string& path, int trainingPlanIndex) const
	{
		std::ofstream os(path, std::ios::out | std::ios::binary);
		cereal::PortableBinaryOutputArchive archive(os);

		onlyUseNeuralNetworkIndex = false;
		archive(trainingPlans[trainingPlanIndex]);
	}

	AbstractTrainingPlan& TrainingPlanRepository::load(const std::string& path)
	{
		std::ifstream is(path, std::ios::in | std::ios::binary);
		cereal::PortableBinaryInputArchive archive(is);

		trainingPlans.push_back(std::unique_ptr<AbstractTrainingPlan>());
		archive(trainingPlans.back());

		throwEvent(EVT_TP_CHANGED, *this);

		return *trainingPlans.back().get();
	}

	AbstractTrainingPlan& TrainingPlanRepository::getByName(const std::string& name) const
	{
		for (int i = 0; i < trainingPlans.size(); i++)
		{
			if (trainingPlans[i]->getName() == name)
				return *trainingPlans[i].get();
		}
		throw std::invalid_argument("No training plan with name \"" + name + "\" could be found.");
	}

	void TrainingPlanRepository::setTrainingPlanName(int trainingPlanIndex, const std::string& newName)
	{
		trainingPlans[trainingPlanIndex]->setName(newName);
		throwEvent(EVT_TP_CHANGED, *this);
	}

	bool TrainingPlanRepository::exists(const std::string& name) const
	{
		for (int i = 0; i < trainingPlans.size(); i++)
		{
			if (trainingPlans[i]->getName() == name)
				return true;
		}
		return false;
	}

	void TrainingPlanRepository::clear()
	{
		trainingPlans.clear();
	}

	const std::vector<std::unique_ptr<AbstractTrainingPlan>>& TrainingPlanRepository::getTrainingPlans() const
	{
		return trainingPlans;
	}
}
