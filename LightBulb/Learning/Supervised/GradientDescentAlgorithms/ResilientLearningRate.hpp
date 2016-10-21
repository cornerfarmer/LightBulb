#pragma once

#ifndef _RESILIENTLEARNINGRATE_H_
#define _RESILIENTLEARNINGRATE_H_

// Library Includes
#include <vector>

// Includes
#include "AbstractGradientDescentAlgorithm.hpp"

namespace LightBulb
{
	/**
	* \brief All options for the resilient learning rate.
	*/
	struct ResilientLearningRateOptions : public AbstractGradientDescentAlgorithmOptions
	{
		/**
		 * \brief Sets the factor by which the learningRate can grow
		 * \details Default value: 1.2 
		 */
		double learningRateGrowFac;
		/**
		 * \brief Sets the factor by which the learningRate can shrink
		 * \details Default value: 0.5
		 */
		double learningRateShrinkFac;
		/**
		 * \brief Sets the highest possible learningRate
		 * \details Default value: 50
		 */
		double learningRateMax;
		/**
		 * \brief Sets the lowest possible learningRate
		 * \details Default value: 0.000001
		 */
		double learningRateMin;
		/**
		 * \brief Sets the start value of all learningRates
		 * \details Default value: 0.2
		 */
		double learningRateStart;
		/**
		 * \brief The lowest total learning rate (if the current value is smaller than this value the learning process will stop)
		 * \details Default value: 0
		 */
		double minLearningRate;
		ResilientLearningRateOptions()
		{
			learningRateGrowFac = 1.2;
			learningRateShrinkFac = 0.5;
			learningRateMax = 50;
			learningRateMin = 0.000001;
			learningRateStart = 0.2;
			minLearningRate = 0;
		}
	};


	/**
	 * \brief Describes a very flexibel form of gradient descent which adjusts learning rates dynamically
	 * \details If the gradient stays in the same direction, the learning rate will be increased. (multiplied by learningRateGrowFac)\n
	 * If the gradient changes in direction (maybe because there was an minimum), the learning rate will be decreased. (multiplied by learningRateShrinkFac) \n
	 * The learning rate is always kept between learningRateMin and learningRateMax.
	 */
	class ResilientLearningRate : public AbstractGradientDescentAlgorithm
	{
		template <class Archive>
		friend void serialize(Archive& archive, ResilientLearningRate& resilientLearningRate);
		friend struct cereal::LoadAndConstruct<ResilientLearningRate>;
	private:
		/**
		 * \brief Remembers the previous learning rates.
		 */
		std::vector<Eigen::MatrixXd> previousLearningRates;
		/**
		 * \brief Returns our current options in form of a ResilientLearningRateOptions object.
		 * \return The ResilientLearningRateOptions object.
		 */
		ResilientLearningRateOptions& getOptions();
	public:
		/**
		 * \brief Creates the resilient learning rate.
		 * \param options_ The options which configure the resilient learning rate.
		 */
		ResilientLearningRate(ResilientLearningRateOptions& options_);
		/**
		 * \brief Creates the resilient learning rate with default options.
		 */
		ResilientLearningRate();
		// Inherited:
		Eigen::MatrixXd calcDeltaWeight(const AbstractNetworkTopology& networkTopology, int layerIndex, const Eigen::MatrixXd& gradients) override;
		std::string printDebugOutput() override;
		bool learningHasStopped() override;
		void initializeAlgorithm(const AbstractNetworkTopology& networkTopology) override;
	};
}

#include "IO/ResilientLearningRateIO.hpp"

#endif

