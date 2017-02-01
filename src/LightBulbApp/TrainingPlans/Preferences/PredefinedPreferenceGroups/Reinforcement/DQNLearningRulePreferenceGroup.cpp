// Includes
#include "LightBulbApp/LightBulbAppPrec.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/Reinforcement/DQNLearningRulePreferenceGroup.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/IntegerPreference.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/DoublePreference.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/BooleanPreference.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/Supervised/GradientDescentLearningRulePreferenceGroup.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/Supervised/GradientDescentAlgorithms/RMSPropLearningRatePreferenceGroup.hpp"

namespace LightBulb
{
	#define PREFERENCE_MINIBATCH_SIZE "Minibatch size"
	#define PREFERENCE_TARGET_NETWORK_UPDATE_FREQUENCY "Target network update frequency"
	#define PREFERENCE_REPLAY_MEMORY_SIZE "replay memory size"
	#define PREFERENCE_INITIAL_EXPLORATION "initial exploration"
	#define PREFERENCE_FINAL_EXPLORATION "final exploration"
	#define PREFERENCE_FINAL_EXPLORATION_FRAME "final exploration frame"
	#define PREFERENCE_REPLAY_START_SIZE "Replay start size"
	#define PREFERENCE_DISCOUNT_FACTOR "Discount factor"
	#define PREFERENCE_REPLACE_STORED_TRANSITIONS "Replace stored transitions"

	DQNLearningRulePreferenceGroup::DQNLearningRulePreferenceGroup(const std::string& name)
		:AbstractReinforcementLearningRulePreferenceGroup(name)
	{
		DQNLearningRuleOptions options;
		initialize(options);
	}

	DQNLearningRulePreferenceGroup::DQNLearningRulePreferenceGroup(const DQNLearningRuleOptions& options, const std::string& name)
		:AbstractReinforcementLearningRulePreferenceGroup(options, name)
	{
		initialize(options);
	}

	void DQNLearningRulePreferenceGroup::initialize(const DQNLearningRuleOptions& options)
	{
		AbstractReinforcementLearningRulePreferenceGroup::initialize(options);

		addPreference(new IntegerPreference(PREFERENCE_MINIBATCH_SIZE, options.minibatchSize, 1, 100));
		addPreference(new IntegerPreference(PREFERENCE_REPLAY_MEMORY_SIZE, options.replayMemorySize, 10000, 10000000));
		addPreference(new IntegerPreference(PREFERENCE_TARGET_NETWORK_UPDATE_FREQUENCY, options.targetNetworkUpdateFrequency, 1, 100000));
		addPreference(new DoublePreference(PREFERENCE_DISCOUNT_FACTOR, options.discountFactor, 0, 1));
		addPreference(new DoublePreference(PREFERENCE_INITIAL_EXPLORATION, options.initialExploration, 0, 1));
		addPreference(new DoublePreference(PREFERENCE_FINAL_EXPLORATION, options.finalExploration, 0, 1));
		addPreference(new IntegerPreference(PREFERENCE_FINAL_EXPLORATION_FRAME, options.finalExplorationFrame, 1, 10000000));
		addPreference(new IntegerPreference(PREFERENCE_REPLAY_START_SIZE, options.replayStartSize, 0, 500000));
		addPreference(new BooleanPreference(PREFERENCE_REPLACE_STORED_TRANSITIONS, options.replaceStoredTransitions));

		addPreference(new GradientDescentLearningRulePreferenceGroup(options.gradientDescentOptions, true));
		addPreference(new RMSPropLearningRatePreferenceGroup(options.rmsPropOptions));
	}
	
	DQNLearningRuleOptions DQNLearningRulePreferenceGroup::create() const
	{
		DQNLearningRuleOptions options;
		fillOptions(options);

		options.minibatchSize = getIntegerPreference(PREFERENCE_MINIBATCH_SIZE);
		options.replayMemorySize = getIntegerPreference(PREFERENCE_REPLAY_MEMORY_SIZE);
		options.targetNetworkUpdateFrequency = getIntegerPreference(PREFERENCE_TARGET_NETWORK_UPDATE_FREQUENCY);
		options.discountFactor = getDoublePreference(PREFERENCE_DISCOUNT_FACTOR);
		options.initialExploration = getDoublePreference(PREFERENCE_INITIAL_EXPLORATION);
		options.finalExploration = getDoublePreference(PREFERENCE_FINAL_EXPLORATION);
		options.finalExplorationFrame = getIntegerPreference(PREFERENCE_FINAL_EXPLORATION_FRAME);
		options.replayStartSize = getIntegerPreference(PREFERENCE_REPLAY_START_SIZE);
		options.replaceStoredTransitions = getBooleanPreference(PREFERENCE_REPLACE_STORED_TRANSITIONS);

		options.gradientDescentOptions = createFromGroup<GradientDescentLearningRuleOptions, GradientDescentLearningRulePreferenceGroup>();
		options.rmsPropOptions = createFromGroup<RMSPropLearningRateOptions, RMSPropLearningRatePreferenceGroup>();
		return options;
	}

	AbstractCloneable* DQNLearningRulePreferenceGroup::clone() const
	{
		return new DQNLearningRulePreferenceGroup(*this);
	}
}
