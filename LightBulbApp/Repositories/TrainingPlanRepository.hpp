#pragma once

#ifndef _TRAININGPLANREPOSITORY_H_
#define _TRAININGPLANREPOSITORY_H_

// Library includes
#include <vector>
#include <Event/Observable.hpp>
#include <memory>
#include <TrainingPlans/AbstractTrainingPlan.hpp>

// Includes

namespace LightBulb
{
	// Forward declarations

	enum TrainingPlanRepositoryEvents
	{
		EVT_TP_CHANGED
	};

	class TrainingPlanRepository : public LightBulb::Observable<TrainingPlanRepositoryEvents, TrainingPlanRepository>
	{
		template <class Archive>
		friend void serialize(Archive& archive, TrainingPlanRepository& trainingPlanRepository);
	private:
		std::vector<std::unique_ptr<AbstractTrainingPlan>> trainingPlans;
	public:
		const std::vector<std::unique_ptr<AbstractTrainingPlan>>* getTrainingPlans() const;
		int getIndexOfTrainingPlan(const AbstractTrainingPlan* trainingPlan) const;
		void Add(AbstractTrainingPlan* trainingPlan);
		void save(const std::string& path, int trainingPlanIndex) const;
		AbstractTrainingPlan* load(const std::string& path);
		AbstractTrainingPlan* getByName(const std::string& name) const;
		void setTrainingPlanName(int trainingPlanIndex, const std::string& newName);
	};
}

#include "IO/TrainingPlanRepositoryIO.hpp"

#endif
