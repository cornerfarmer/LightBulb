#pragma once

#ifndef _CONSTANTMUTATIONCOMMAND_H_
#define _CONSTANTMUTATIONCOMMAND_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractMutationCommand.hpp"

namespace LightBulb
{
	/**
	 * \brief Mutates a constant amount of individuals
	 */
	class ConstantMutationCommand : public AbstractMutationCommand
	{
	private:
		/**
		 * \brief The amount of individuals which should be mutated.
		 */
		int individualCount;
		/**
		 * \brief Alternative: The percentage of individuals which should be mutated.
		 */
		double mutationPercentage;
	public:
		virtual ~ConstantMutationCommand() {};
		ConstantMutationCommand() = default;
		ConstantMutationCommand(const ConstantMutationCommand& other) = default;
		/**
		 * \brief Creates a command which mutates a static amount of individuals.
		 * \param mutationAlgorithm_ The mutation algorithm to use.
		 * \param mutationSelector_ The mutation selector to use.
		 * \param individualCount_ The amount of individuals which should be mutated.
		 */
		ConstantMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, AbstractMutationSelector* mutationSelector_, int individualCount_);
		/**
		 * \brief Creates a command which mutates a percentage of individuals.
		 * \param mutationAlgorithm_ The mutation algorithm to use.
		 * \param mutationSelector_ The mutation selector to use.
		 * \param mutationPercentage_ The percentage of individuals which should be mutated.
		 */
		ConstantMutationCommand(AbstractMutationAlgorithm* mutationAlgorithm_, AbstractMutationSelector* mutationSelector_, double mutationPercentage_);
		ConstantMutationCommand(ConstantMutationCommand&& other) noexcept;
		ConstantMutationCommand& operator=(ConstantMutationCommand other);
		friend void swap(ConstantMutationCommand& lhs, ConstantMutationCommand& rhs) noexcept;
		// Inherited:
		void select(const std::vector<std::pair<double, AbstractIndividual*>>& highscore, std::map<AbstractIndividual*, int>& counter) override;
		AbstractCloneable* clone() const override;
	};
}

#endif
