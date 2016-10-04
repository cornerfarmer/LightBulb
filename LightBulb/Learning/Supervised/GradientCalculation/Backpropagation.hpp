#pragma once

#ifndef _BACKPROPAGATION_H_
#define _BACKPROPAGATION_H_

// Library Includes
#include <vector>

// Includes
#include "AbstractGradientCalculation.hpp"

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
		Eigen::VectorXd lastDeltaVectorOutputLayer;
		/**
		 * \brief Can be used to overcome long plateaus.
		 */
		double flatSpotEliminationFac;
	public:
		/**
		 * \brief Creates Backpropagation
		 * \param flatSpotEliminationFac_ Can be used to overcome long plateaus.
		 */
		Backpropagation(double flatSpotEliminationFac_ = 0);
		// Inherited:
		void calcGradient(AbstractNetworkTopology* networkTopology, std::vector<Eigen::VectorXd>& netInputs, std::vector<Eigen::VectorBlock<Eigen::VectorXd>>& activations, ErrorMap_t* errormap) override;
	};
}

#include "IO/BackpropagationIO.hpp"

#endif

