#pragma once

#ifndef _BACKPROPAGATION_H_
#define _BACKPROPAGATION_H_

// Library Includes
#include <vector>

// Includes
#include "LightBulb/Learning/Supervised/GradientCalculation/AbstractGradientCalculation.hpp"
#include "LightBulbApp/TrainingPlans/Preferences/AbstractPreferenceElement.hpp"
#include "LightBulb/LinearAlgebra/Vector.hpp"

namespace LightBulb
{
	/**
	 * \brief Computes the gradient by backpropagating the error.
	 * \details Calculates: \n \n 
	 * \f$ \Delta\omega_{k,h} = o_k \delta_h\f$\n
	 * \f$ \delta_h = {\begin{cases} f'(net_h+ \beta)*(t_h-y_h)&\mbox{(h: output layer)} \\ f'(net_h + \beta)*\sum_{l \in L}(\delta_l\omega_{h,l})&\mbox{(h: hidden layer)} \end{cases}}\f$ \n\n
	 * \f$\beta: flat spot elimination factor\f$ 
	 */
	class Backpropagation : public AbstractGradientCalculation
	{
		template <class Archive>
		friend void serialize(Archive& archive, Backpropagation& backpropagation);
		friend struct cereal::LoadAndConstruct<Backpropagation>;
	private:
		/**
		 * \brief This vector should keep all delta values
		 */
		std::vector<Vector> lastDeltaVectorOutputLayer;
		/**
		 * \brief Can be used to overcome long plateaus.
		 */
		double flatSpotEliminationFac;
		Vector nextLayerErrorValueFactor;
		void backpropagateLastLayer(const viennacl::vector_base<float>& errorVec, const viennacl::vector_base<float>& derivVec, const viennacl::vector_base<float>& actVec, viennacl::vector_base<float>& deltaVec, viennacl::matrix_base<float>& G);
		void backpropagateInnerLayer(viennacl::vector_base<float>& errorVec, const viennacl::vector_base<float>& derivVec, const viennacl::vector_base<float>& actVec, const viennacl::vector_base<float>& lastDeltaVec, viennacl::vector_base<float>& deltaVec, const viennacl::matrix_base<float>& W, viennacl::matrix_base<float>& G);
	public:
		/**
		 * \brief Creates Backpropagation
		 * \param flatSpotEliminationFac_ Can be used to overcome long plateaus.
		 */
		Backpropagation(double flatSpotEliminationFac_ = 0);
		// Inherited:
		void calcGradient(const AbstractNetworkTopology& networkTopology, const std::vector<Vector>& netInputs, const std::vector<Vector>& activations, const Vector& errorVector) override;
		AbstractCloneable* clone() const override;
		void initGradient(const AbstractNetworkTopology& networkTopology) override;
	};
}

#include "LightBulb/IO/BackpropagationIO.hpp"

#endif

