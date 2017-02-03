#include "LightBulbApp/LightBulbAppPrec.hpp"
#include "LightBulbApp/IO/AbstractTrainingPlanIO.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/common.hpp>

namespace LightBulb
{
	/**
	* \brief Saves an AbstractTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractTrainingPlan to save.
	*/
	template <class Archive>
	void save(Archive& archive, AbstractTrainingPlan const& trainingPlan)
	{
		archive(cereal::make_nvp("state", trainingPlan.state));
		archive(cereal::make_nvp("logger", trainingPlan.logger));
		archive(cereal::make_nvp("name", trainingPlan.name));
		archive(cereal::make_nvp("preferenceGroup", trainingPlan.preferenceGroup));
		archive(cereal::make_nvp("concludedRunTime", trainingPlan.concludedRunTime.count()));
		archive(cereal::make_nvp("patternName", trainingPlan.patternName));
	}

	/**
	* \brief Loads an AbstractTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractTrainingPlan to load.
	*/
	template <class Archive>
	void load(Archive& archive, AbstractTrainingPlan& trainingPlan)
	{
		archive(cereal::make_nvp("state", trainingPlan.state));
		archive(cereal::make_nvp("logger", trainingPlan.logger));
		archive(cereal::make_nvp("name", trainingPlan.name));
		archive(cereal::make_nvp("preferenceGroup", trainingPlan.preferenceGroup));
		double concludedRunTime;
		archive(cereal::make_nvp("concludedRunTime", concludedRunTime));
		trainingPlan.concludedRunTime = std::chrono::duration<double>(concludedRunTime);
		archive(cereal::make_nvp("patternName", trainingPlan.patternName));
	}

	DECLARE_SERIALIZATION_TEMPLATE(AbstractTrainingPlan);
}