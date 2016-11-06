#ifndef _ABSTRACTLEARNINGRESULT_H_
#define _ABSTRACTLEARNINGRESULT_H_

#include <string>

namespace LightBulb
{
	/**
	 * \brief Contains all results from a learning rule.
	 */
	struct AbstractLearningResult
	{
		/**
		 * \brief Describes how good the result is.
		 */
		double quality;
		/**
		 * \brief Gives more details about the quality value.
		 */
		std::string qualityLabel;
		/**
		 * \brief Contains the latest learning state.
		 */
		std::shared_ptr<LearningState> learningState;
		/**
		 * \brief Determines if the learning was successful.
		 */
		bool succeeded;

		virtual ~AbstractLearningResult() {};
	};
}

#endif
