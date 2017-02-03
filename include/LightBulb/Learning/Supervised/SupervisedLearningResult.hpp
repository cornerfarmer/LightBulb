#ifndef _SUPERVISEDLEARNINGRESULT_H_
#define _SUPERVISEDLEARNINGRESULT_H_

#include "LightBulb/Learning/AbstractLearningResult.hpp"

namespace LightBulb
{
	class AbstractNeuralNetwork;
	/**
	 * \brief Contains all results from a supervised learning rule.
	 */
	struct SupervisedLearningResult : public AbstractLearningResult
	{
		/**
		 * \brief The network which was trained in the learning rule.
		 */
		AbstractNeuralNetwork* trainedNetwork;
		double totalError;
	};
}

#endif
