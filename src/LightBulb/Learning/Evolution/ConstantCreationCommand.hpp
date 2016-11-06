#pragma once

#ifndef _CONSTANTCREATIONCOMMAND_H_
#define _CONSTANTCREATIONCOMMAND_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractCreationCommand.hpp"

namespace LightBulb
{
	/**
	 * \brief Adds objects to the world as long as it contains less objects than wished.
	 */
	class ConstantCreationCommand : public AbstractCreationCommand
	{
	private:
		/**
		 * \brief Holds the amount of objects up to which they should be created.
		 */
		int objectCount;
	public:
		virtual ~ConstantCreationCommand() {};
		/**
		 * \brief Creates the constant creation command.
		 * \param objectCount_ The amount of objects up to which they should be created.
		 */
		ConstantCreationCommand(int objectCount_);
		// Inherited:
		void execute(AbstractEvolutionWorld& world, std::vector<AbstractEvolutionObject*>& notUsedObjects) override;
		AbstractCloneable* clone() const override;
	};
}

#endif
