#pragma once

#ifndef _RBFINTERPOLATIONLEARNINGRULE_H_
#define _RBFINTERPOLATIONLEARNINGRULE_H_

// Library Includes
#include "EigenSrc/Dense"
#include "EigenSrc/Jacobi"
#include <memory>

// Includes
#include "ClusterAnalysis/AbstractRBFNeuronPlacer.hpp"
#include "Learning/Supervised/AbstractSupervisedLearningRule.hpp"

namespace LightBulb
{
	// Forward declarations
	class NeuralNetwork;
	class Teacher;

	/**
	 * \brief All options for the RBF interpolation learning rule.
	 */
	struct RBFInterpolationLearningRuleOptions : AbstractSupervisedLearningRuleOptions
	{
		/**
		 * \brief The neuronPlacer helps to place all RBFNeurons before starting to learn.
		 */
		AbstractRBFNeuronPlacer* neuronPlacer;
		/**
		 * \brief Creates the options and fills them with default options.
		 */
		RBFInterpolationLearningRuleOptions()
		{
			neuronPlacer = NULL;
		}
		~RBFInterpolationLearningRuleOptions()
		{
			delete(neuronPlacer);
		}
		RBFInterpolationLearningRuleOptions(const RBFInterpolationLearningRuleOptions &obj)
		{
			*this = obj;
			neuronPlacer = obj.neuronPlacer->getCopy();
		}
	};

	// The DeltaLearningRule can only be used to train SingleLayerPerceptronNetworks
	/**
	 * \brief This learning rule calculates the weights of an RBF network in just one step.
	 * \details First the given neuron placer (e.q. some clustering algorithm) is executed which places the RBF neurons.
	 * This affects the first weight layer. Then a system of linear equations is solved by matrix inversion which sets the weights in the second layer.
	 */
	class RBFInterpolationLearningRule : public AbstractSupervisedLearningRule
	{
	private:
		/**
		 * \brief A matrix which will contain all outputValues from neurons in the second layer in every teachingLesson.
		 */
		std::unique_ptr<Eigen::MatrixXd> m;
		/**
		 * \brief Inversion of m.
		 */
		std::unique_ptr<Eigen::MatrixXd> mInverse;
		/**
		 * \brief A matrx which will contain all teachingInput values from all output neurons.
		 */
		std::unique_ptr<Eigen::MatrixXd> t;
		/**
		 * \brief A vector which will contain all calculated weights.
		 */
		std::unique_ptr<Eigen::MatrixXd> w;
		/**
		 * \brief The calculated gradients.
		 */
		std::vector<Eigen::MatrixXd> gradients;
	protected:
		/**
		 * \brief Returns our current options in form of a RBFInterpolatioLearningRuleOptions object.
		 * \return The RBFInterpolatioLearningRuleOptions object.
		 */
		RBFInterpolationLearningRuleOptions* getOptions();
		// Inherited:
		void adjustWeights(int layerIndex) override;
		bool learningHasStopped() override;
		void initializeStartLearningAlgoritm() override;
		AbstractActivationOrder* getNewActivationOrder();
		void calculateDeltaWeight(AbstractTeachingLesson& lesson, int lessonIndex, ErrorMap_t* errormap) override;
		void initializeTry() override;
	public:
		/**
		 * \brief Creates the RBF interpolation learning rule.
		 * \param options_ The options which configure the RBF interpolation learning rule.
		 */
		RBFInterpolationLearningRule(RBFInterpolationLearningRuleOptions &options_);
		/**
		 * \brief Returns the name of the learning rule
		 * \return The name
		 */
		static std::string getName();
	};
}

#include "IO/RBFInterpolationLearningRuleIO.hpp"

#endif
