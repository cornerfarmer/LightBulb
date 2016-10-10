#pragma once

#ifndef _RBFNETWORK_H_
#define _RBFNETWORK_H_

// Libary includes

// Includes
#include "NetworkTopology/FeedForwardNetworkTopology.hpp"

namespace LightBulb
{
	/**
	 * \brief A network which describes a linear combination of multiple radial basis functions.
	 */
	class RBFNetwork : public FeedForwardNetworkTopology
	{
		template <class Archive>
		friend void save(Archive& archive, RBFNetwork const & rbfNetwork);
		template <class Archive>
		friend void load(Archive& archive, RBFNetwork & rbfNetwork);
	private:
		/**
		 * \brief Contains all neuron widths.
		 */
		Eigen::VectorXd neuronWidths;
	public:
		/**
		 * \brief Creates the RBFNetwork with the given neuron counts.
		 * \param neuronCountFirstLayer The count of input neurons.
		 * \param neuronCountSecondLayer The count of hidden neurons.
		 * \param neuronCountThirdLayer The count of output neurons.
		 */
		RBFNetwork(unsigned int neuronCountFirstLayer, unsigned int neuronCountSecondLayer, unsigned int neuronCountThirdLayer);
		/**
		 * \brief Creates the RBFNetwork.
		 */
		RBFNetwork();
		/**
		 * \brief Set all neuron centers to new random values between randStart and randEnd.
		 * \param randomGenerator The random generator.
		 * \param randStart The lower boundary of the random centers.
		 * \param randEnd The upper boundary of the random centers.
		 */
		void randomizeCenters(AbstractRandomGenerator* randomGenerator, double randStart, double randEnd);

		/**
		 * \brief Set all neuron width to new random values between randStart and randEnd.
		 * \param randomGenerator The random generator.
		 * \param randStart The lower boundary of the random widths.
		 * \param randEnd The upper boundary of the random widths.
		 */
		void randomizeWidths(AbstractRandomGenerator* randomGenerator, double randStart, double randEnd);
		// Sets the center of the RBFNeuron with the given index
		/**
		 * \brief Sets the center of one hidden neuron.
		 * \param neuronIndex The index of the hidden neuron.
		 * \param newCenterPosition The new center.
		 */
		void setCenterOfRBFNeuron(int neuronIndex, std::vector<double> &newCenterPosition);
		/**
		 * \brief Sets the width of the RBFNeuron with the given index.
		 * \param neuronIndex The index of the hidden neuron.
		 * \param newWidth The new width.
		 */
		void setWidthOfRBFNeuron(int neuronIndex, double newWidth);
		/**
		 * \brief Returns the width of a neuron.
		 * \param neuronIndex The index of the hidden neuron.
		 * \return The width.
		 */
		double getWidthOfRBFNeuron(int neuronIndex);
		// Inherited:
		virtual void randomizeWeights(AbstractRandomGenerator* randomGenerator, double randStart, double randEnd) override;
		AbstractNetworkTopology* clone() override;
	};
}

#include "IO/RBFNetworkIO.hpp"

#endif