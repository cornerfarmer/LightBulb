// Includes
#include "LightBulbApp/TrainingPlans/Preferences/PredefinedPreferenceGroups/Supervised/GradientDescentAlgorithms/RMSPropLearningRatePreferenceGroup.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/DoublePreference.hpp"
#include "LightBulb/Learning/Supervised/GradientDescentAlgorithms/RMSPropLearningRate.hpp"

namespace LightBulb
{
	#define PREFERENCE_LEARNING_RATE "Learning rate"
	#define PREFERENCE_DELTA_WEIGHTS_MOMENTUM "Delta weigths momentum"
	#define PREFERENCE_GRADIENT_MOMENTUM "Gradient momentum"
	#define PREFERENCE_SQUARED_GRADIENT_MOMENTUM "Squared gradient momentum"
	#define PREFERENCE_MIN_SQUARED_GRADIENT "Minimum squared gradient"

	RMSPropLearningRatePreferenceGroup::RMSPropLearningRatePreferenceGroup(const std::string& name)
		:PreferenceGroup(name)
	{
		RMSPropLearningRateOptions options;
		initialize(options);
	}


	RMSPropLearningRatePreferenceGroup::RMSPropLearningRatePreferenceGroup(const RMSPropLearningRateOptions& options, const std::string& name)
		:PreferenceGroup(name)
	{
		initialize(options);
	}

	void RMSPropLearningRatePreferenceGroup::initialize(const RMSPropLearningRateOptions& options)
	{
		addPreference(new DoublePreference(PREFERENCE_LEARNING_RATE, options.learningRate, 0, 0.01));
		addPreference(new DoublePreference(PREFERENCE_DELTA_WEIGHTS_MOMENTUM, options.deltaWeightsMomentum, 0, 1));
		addPreference(new DoublePreference(PREFERENCE_GRADIENT_MOMENTUM, options.gradientMomentum, 0, 1));
		addPreference(new DoublePreference(PREFERENCE_SQUARED_GRADIENT_MOMENTUM, options.squaredGradientMomentum, 0, 1));
		addPreference(new DoublePreference(PREFERENCE_MIN_SQUARED_GRADIENT, options.minSquaredGradient, 0, 1));
	}

	RMSPropLearningRateOptions RMSPropLearningRatePreferenceGroup::create() const
	{
		RMSPropLearningRateOptions options;
		options.learningRate = getDoublePreference(PREFERENCE_LEARNING_RATE);
		options.deltaWeightsMomentum = getDoublePreference(PREFERENCE_DELTA_WEIGHTS_MOMENTUM);
		options.gradientMomentum = getDoublePreference(PREFERENCE_GRADIENT_MOMENTUM);
		options.squaredGradientMomentum = getDoublePreference(PREFERENCE_SQUARED_GRADIENT_MOMENTUM);
		options.minSquaredGradient = getDoublePreference(PREFERENCE_MIN_SQUARED_GRADIENT);
		return options;
	}

	AbstractCloneable* RMSPropLearningRatePreferenceGroup::clone() const
	{
		return new RMSPropLearningRatePreferenceGroup(*this);
	}
}
