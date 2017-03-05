// Includes
#include "LightBulb/IO/DQNLearningRuleIO.hpp"
#include "LightBulb/IO/EigenMatrixIO.hpp"
#include "LightBulb/IO/TemplateDeclaration.hpp"
// Libraray includes
#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>
#include <cereal/access.hpp>

namespace LightBulb
{
	/**
	* \brief Serializes a Transition.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param transition The Transition to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, TransitionStorage& transition)
	{
		/*archive(cereal::make_nvp("state", transition.state));
		archive(cereal::make_nvp("nextState", transition.nextState));
		archive(cereal::make_nvp("action", transition.action));
		archive(cereal::make_nvp("reward", transition.reward));*/
	}

	DECLARE_SINGLE_SERIALIZATION_TEMPLATE(TransitionStorage);

	/**
	* \brief Serializes a DQNLearningRule.
	* \tparam Archive The archive type.
	* \param archive The archive which should be used.
	* \param learningRule The DQNLearningRule to serialize.
	*/
	template <class Archive>
	void serialize(Archive& archive, DQNLearningRule& learningRule)
	{
		archive(cereal::base_class<AbstractReinforcementLearningRule>(&learningRule));
		archive(cereal::make_nvp("waitUntilLearningStarts", learningRule.waitUntilLearningStarts));
		archive(cereal::make_nvp("transitionStorage", learningRule.transitionStorage));
		archive(cereal::make_nvp("currentTotalError", learningRule.currentTotalError));
		archive(cereal::make_nvp("qAvgSum", learningRule.qAvgSum));
		archive(cereal::make_nvp("gradientDescent", learningRule.gradientDescent));
	}

	DECLARE_SINGLE_SERIALIZATION_TEMPLATE(DQNLearningRule);
}


namespace cereal
{
	template <class Archive>
	void LoadAndConstruct<LightBulb::DQNLearningRule>::construct(Archive& ar, LightBulb::DQNLearningRule& learningRule)
	{
		using namespace LightBulb;
		ar(base_class<AbstractReinforcementLearningRule>(&learningRule));
		ar(make_nvp("waitUntilLearningStarts", learningRule.waitUntilLearningStarts));
		ar(make_nvp("transitions", learningRule.transitionStorage));
		ar(make_nvp("currentTotalError", learningRule.currentTotalError));
		ar(make_nvp("qAvgSum", learningRule.qAvgSum));

		IOStorage<AbstractLearningRule>::push(learningRule.gradientDescent.release());
		ar(make_nvp("gradientDescent", learningRule.gradientDescent));
		learningRule.gradientDescent.reset(static_cast<GradientDescentLearningRule*>(IOStorage<AbstractLearningRule>::pop()));
	}
}


#include "LightBulb/IO/UsedArchives.hpp"

CEREAL_REGISTER_TYPE(LightBulb::DQNLearningRule);

CEREAL_REGISTER_DYNAMIC_INIT(DQNLearningRule)