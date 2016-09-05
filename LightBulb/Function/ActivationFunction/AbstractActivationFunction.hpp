#pragma once

#ifndef _ABSTRACTACTIVATIONFUNCTION_H_
#define _ABSTRACTACTIVATIONFUNCTION_H_

// Library includes
#include <vector>
#include <EigenSrc/Cholesky>
#include <memory>

// Forward declaration
class AbstractThreshold;


/**
 * \brief This abstract class describes a function, which can calculate the activation of a neuron from its input
 */
class AbstractActivationFunction
{
private:
public:
	virtual ~AbstractActivationFunction() {}
	/**
	 * \brief Calculate the activation from the given input for all neurons in one layer
	 * \param layerNr The layer number which should be considered
	 * \param activations A layerwise list of all activations which will contain the calculated activations
	 * \param netInputs A layerwise list of all inputs which will be used for the computation 
	 */
	virtual void execute(int layerNr, std::vector<std::unique_ptr<Eigen::VectorBlock<Eigen::VectorXd>>> &activations, std::vector<Eigen::VectorXd> &netInputs);
	/**
	 * \brief Calculates the activation for one neuron
	 * \param input The input of the neuron
	 * \return The activation of the neuron
	 */
	virtual double execute(double input) = 0;
	/**
	 * \brief Calculates the derivated activation from the given input
	 * \param input The input of the neuron
	 * \return The calculated activation derivation
	 */
	virtual double executeDerivation(double input) = 0;
	/**
	 * \brief Calculate the derivated activation from the given input of every neuron for one layer
	 * \param input One layer of input values
	 * \return The calculated activation derivations for the whole layer
	 */
	virtual Eigen::VectorXd executeDerivation(Eigen::VectorXd input);
	/**
	 * \brief Create a copy of the object
	 * \return The copy
	 */
	virtual AbstractActivationFunction* getActivationFunctionCopy() = 0;
	/**
	 * \brief Returns the maximum possible output/activation value of this function
	 * \return The maximum
	 */
	virtual double getMaximum() = 0;
	/**
	* \brief Returns the lowest possible output/activation value of this function
	* \return The minimum
	*/
	virtual double getMinimum() = 0;
	/**
	 * \brief Returns if the function has an max/minimum.
	 * \return Max/minimum exists
	 */
	virtual bool hasAMaxAndMinimum() = 0;
};

#endif