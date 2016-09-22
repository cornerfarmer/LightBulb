#ifndef _SUPERVISEDLEARNINGRESULT_H_
#define _SUPERVISEDLEARNINGRESULT_H_

#include "Learning/AbstractLearningResult.hpp"
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>

namespace LightBulb
{
	/**
	 * \brief Contains all results from a supervised learning rule.
	 */
	struct SupervisedLearningResult : public AbstractLearningResult
	{
		/**
		 * \brief The network which was trained in the learning rule.
		 */
		AbstractNeuralNetwork* trainedNetwork;
	};
}

#endif
