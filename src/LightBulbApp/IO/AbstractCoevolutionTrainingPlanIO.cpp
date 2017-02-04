#include "LightBulbApp/IO/AbstractCoevolutionTrainingPlanIO.hpp"
#include <LightBulb/Learning/Evolution/AbstractCoevolutionEnvironment.hpp>
#include "LightBulb/Learning/Evolution/AbstractCombiningStrategy.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	/**
	 * \brief Saves an AbstractCoevolutionTrainingPlan.
	 * \tparam Archive The archive type.
	 * \param archive The archive which should be used.
	 * \param trainingPlan The AbstractCoevolutionTrainingPlan to save.
	 */
	template <class Archive>
	void save(Archive& archive, AbstractCoevolutionTrainingPlan const& trainingPlan)
	{
		archive(cereal::make_nvp("parasiteEnvironment", trainingPlan.parasiteEnvironment));
		archive(cereal::base_class<AbstractEvolutionTrainingPlan>(&trainingPlan));
	}

	/**
	* \brief Loads an AbstractCoevolutionTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractCoevolutionTrainingPlan to load.
	*/
	template <class Archive>
	void load(Archive& archive, AbstractCoevolutionTrainingPlan& trainingPlan)
	{
		IOStorage<AbstractEvolutionEnvironment>::push(trainingPlan.createParasiteEnvironment());
		archive(cereal::make_nvp("parasiteEnvironment", trainingPlan.parasiteEnvironment));
		trainingPlan.parasiteEnvironment.reset(IOStorage<AbstractEvolutionEnvironment>::pop());

		archive(cereal::base_class<AbstractEvolutionTrainingPlan>(&trainingPlan));

		trainingPlan.parasiteEnvironment->setLearningState(trainingPlan.getLearningState());
		static_cast<AbstractCoevolutionEnvironment*>(trainingPlan.parasiteEnvironment.get())->getCombiningStrategy().setSecondEnvironment(static_cast<AbstractCoevolutionEnvironment&>(*trainingPlan.environment.get()));
		static_cast<AbstractCoevolutionEnvironment*>(trainingPlan.environment.get())->getCombiningStrategy().setSecondEnvironment(static_cast<AbstractCoevolutionEnvironment&>(*trainingPlan.parasiteEnvironment.get()));
	}

	DECLARE_SERIALIZATION_TEMPLATE(AbstractCoevolutionTrainingPlan);
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::AbstractCoevolutionTrainingPlan);

CEREAL_REGISTER_DYNAMIC_INIT(AbstractCoevolutionTrainingPlan)
