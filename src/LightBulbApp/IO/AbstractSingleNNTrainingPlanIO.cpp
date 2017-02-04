
// Includes
#include "LightBulbApp/IO/AbstractSingleNNTrainingPlanIO.hpp"
#include "LightBulb/NeuralNetwork/AbstractNeuralNetwork.hpp"
#include "LightBulb/IO/IOStorage.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>

namespace LightBulb
{
	bool onlyUseNeuralNetworkIndex = false;
	
	/**
	* \brief Saves an AbstractSupervisedTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractSupervisedTrainingPlan to save.
	*/
	template <class Archive>
	void save(Archive& archive, AbstractSupervisedTrainingPlan const& trainingPlan)
	{
		if (!onlyUseNeuralNetworkIndex)
		{
			std::unique_ptr<AbstractNeuralNetwork> neuralNetwork(trainingPlan.network);
			archive(cereal::make_nvp("neuralNetwork", neuralNetwork));
			neuralNetwork.release();
		}
		else
		{
			auto networks = IOStorage<const std::vector<std::unique_ptr<AbstractNeuralNetwork>>>::get();
			int neuralNetworkIndex = 0;
			for (auto network = networks->begin(); network != networks->end(); network++, neuralNetworkIndex++)
			{
				if (network->get() == trainingPlan.network)
					break;
			}
			archive(cereal::make_nvp("neuralNetworkIndex", neuralNetworkIndex));
		}
		archive(cereal::base_class<AbstractLearningRuleTrainingPlan>(&trainingPlan));
	}

	/**
	* \brief Loads an AbstractSupervisedTrainingPlan.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param trainingPlan The AbstractSupervisedTrainingPlan to load.
	*/
	template <class Archive>
	void load(Archive& archive, AbstractSupervisedTrainingPlan& trainingPlan)
	{
		if (!onlyUseNeuralNetworkIndex)
		{
			std::unique_ptr<AbstractNeuralNetwork> neuralNetwork;
			archive(cereal::make_nvp("neuralNetwork", neuralNetwork));
			trainingPlan.network = neuralNetwork.release();
		}
		else
		{
			auto networks = IOStorage<const std::vector<std::unique_ptr<AbstractNeuralNetwork>>>::get();
			int neuralNetworkIndex;
			archive(cereal::make_nvp("neuralNetworkIndex", neuralNetworkIndex));
			trainingPlan.network = (*networks)[neuralNetworkIndex].get();
		}
		archive(cereal::base_class<AbstractLearningRuleTrainingPlan>(&trainingPlan));
	}

	DECLARE_SERIALIZATION_TEMPLATE(AbstractSupervisedTrainingPlan);
}

#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::AbstractSupervisedTrainingPlan);

CEREAL_REGISTER_DYNAMIC_INIT(AbstractSupervisedTrainingPlan)