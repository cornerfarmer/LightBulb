#include "LightBulbApp/LightBulbAppPrec.hpp"
#include "LightBulbApp/IO/TrainingPlanRepositoryIO.hpp"
#include "LightBulbApp/TrainingPlans/AbstractTrainingPlan.hpp"
#include "LightBulbApp/IO/AbstractSingleNNTrainingPlanIO.hpp"
// Libraray includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a TrainingPlanRepository.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlanRepository The TrainingPlanRepository to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, TrainingPlanRepository& trainingPlanRepository)
	{
		onlyUseNeuralNetworkIndex = true;
		archive(cereal::make_nvp("trainingPlans", trainingPlanRepository.trainingPlans));
		trainingPlanRepository.throwEvent(EVT_TP_CHANGED, trainingPlanRepository);
	}

	DECLARE_SINGLE_SERIALIZATION_TEMPLATE(TrainingPlanRepository);
}
