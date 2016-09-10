#ifndef _SUPERVISEDLEARNINGRESULT_H_
#define _SUPERVISEDLEARNINGRESULT_H_

#include "Learning/AbstractLearningResult.hpp"
#include <NeuralNetwork/AbstractNeuralNetwork.hpp>

namespace LightBulb
{
	struct SupervisedLearningResult : public AbstractLearningResult
	{
		AbstractNeuralNetwork* trainedNetwork;
	};
}

#endif
