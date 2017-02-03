// Includes
#include "LightBulb/LightBulbPrec.hpp"
#include "LightBulb/IO/GradientDescentLearningRuleIO.hpp"
#include "LightBulb/IO/EigenMatrixIO.hpp"
#include "LightBulb/IO/ConstructExisting.hpp"
#include "LightBulb/Learning/Supervised/GradientCalculation/AbstractGradientCalculation.hpp"
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/AbstractGradientDescentAlgorithm.hpp"

// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a GradientDescentLearningRule.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param learningRule The GradientDescentLearningRule to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, GradientDescentLearningRule& learningRule)
	{
		archive(cereal::base_class<AbstractSupervisedLearningRule>(&learningRule));
		archive(cereal::make_nvp("gradientDescentAlgorithm", learningRule.gradientDescentAlgorithm));
		archive(cereal::make_nvp("gradientCalculation", learningRule.gradientCalculation));
	}

	DECLARE_SINGLE_SERIALIZATION_TEMPLATE(GradientDescentLearningRule);
}


namespace cereal
{
	template <class Archive>
	void LoadAndConstruct<LightBulb::GradientDescentLearningRule>::construct(Archive& ar, LightBulb::GradientDescentLearningRule& learningRule)
	{
		using namespace LightBulb;
		ar(base_class<AbstractSupervisedLearningRule>(&learningRule));

		IOStorage<AbstractGradientDescentAlgorithm>::push(learningRule.gradientDescentAlgorithm.release());
		ar(make_nvp("gradientDescentAlgorithm", learningRule.gradientDescentAlgorithm));
		learningRule.gradientDescentAlgorithm.reset(IOStorage<AbstractGradientDescentAlgorithm>::pop());

		IOStorage<AbstractGradientCalculation>::push(learningRule.gradientCalculation.release());
		ar(make_nvp("gradientCalculation", learningRule.gradientCalculation));
		learningRule.gradientCalculation.reset(IOStorage<AbstractGradientCalculation>::pop());
	}
}


#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::GradientDescentLearningRule);
