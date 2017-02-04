#include "LightBulbApp/IO/AbstractEvolutionTrainingPlanIO.hpp"
#include "LightBulb/Learning/Evolution/AbstractEvolutionEnvironment.hpp"
#include "LightBulb/IO/IOStorage.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	/**
	* \brief Saves an AbstractEvolutionTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractEvolutionTrainingPlan to save.
	*/
	template <class Archive>
	void save(Archive& archive, AbstractEvolutionTrainingPlan const& trainingPlan)
	{
		archive(cereal::make_nvp("environment", trainingPlan.environment));
		archive(cereal::base_class<AbstractLearningRuleTrainingPlan>(&trainingPlan));
	}

	/**
	* \brief Loads an AbstractEvolutionTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractEvolutionTrainingPlan to load.
	*/
	template <class Archive>
	void load(Archive& archive, AbstractEvolutionTrainingPlan& trainingPlan)
	{
		IOStorage<AbstractEvolutionEnvironment>::push(trainingPlan.createEnvironment());
		archive(cereal::make_nvp("environment", trainingPlan.environment));
		trainingPlan.environment.reset(IOStorage<AbstractEvolutionEnvironment>::pop());

		archive(cereal::base_class<AbstractLearningRuleTrainingPlan>(&trainingPlan));

		trainingPlan.environment->setLearningState(trainingPlan.getLearningState());
	}

	DECLARE_SERIALIZATION_TEMPLATE(AbstractEvolutionTrainingPlan);
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::AbstractEvolutionTrainingPlan);

CEREAL_REGISTER_DYNAMIC_INIT(AbstractEvolutionTrainingPlan)
