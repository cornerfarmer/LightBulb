// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/IO/AbstractEvolutionLearningRuleIO.hpp"
// Libraray includes
#include <cereal/cereal.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes an AbstractEvolutionLearningRule
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param evolutionLearning The AbstractEvolutionLearningRule to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, AbstractEvolutionLearningRule& evolutionLearning)
	{
		archive(cereal::base_class<AbstractLearningRule>(&evolutionLearning));
		archive(cereal::make_nvp("zigguratGenerator", evolutionLearning.zigguratGenerator));
	}

	DECLARE_SINGLE_SERIALIZATION_TEMPLATE(AbstractEvolutionLearningRule);
}