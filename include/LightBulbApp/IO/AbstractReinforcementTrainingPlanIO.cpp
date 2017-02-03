#include "LightBulbApp/LightBulbAppPrec.hpp"
#include "LightBulbApp/IO/AbstractReinforcementTrainingPlanIO.hpp"
#include "LightBulb/IO/IOStorage.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	/**
	* \brief Saves an AbstractReinforcementTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractReinforcementTrainingPlan to save.
	*/
	template <class Archive>
	void save(Archive& archive, AbstractReinforcementTrainingPlan const& trainingPlan)
	{
		archive(cereal::make_nvp("environment", trainingPlan.environment));
		archive(cereal::base_class<AbstractLearningRuleTrainingPlan>(&trainingPlan));
	}

	/**
	* \brief Loads an AbstractReinforcementTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractReinforcementTrainingPlan to load.
	*/
	template <class Archive>
	void load(Archive& archive, AbstractReinforcementTrainingPlan& trainingPlan)
	{
		IOStorage<AbstractReinforcementEnvironment>::push(trainingPlan.createEnvironment());
		archive(cereal::make_nvp("environment", trainingPlan.environment));
		trainingPlan.environment.reset(IOStorage<AbstractReinforcementEnvironment>::pop());

		archive(cereal::base_class<AbstractLearningRuleTrainingPlan>(&trainingPlan));

		trainingPlan.environment->setLearningState(trainingPlan.getLearningState());
	}

	DECLARE_SERIALIZATION_TEMPLATE(AbstractReinforcementTrainingPlan);
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::AbstractReinforcementTrainingPlan);
