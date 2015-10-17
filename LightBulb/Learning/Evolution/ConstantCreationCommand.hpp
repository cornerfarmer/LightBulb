#pragma once

#ifndef _CONSTANTCREATIONCOMMAND_H_
#define _CONSTANTCREATIONCOMMAND_H_

// Library Includes

// Includes
#include "Learning/Evolution/AbstractCreationCommand.hpp"

// Forward declarations

class ConstantCreationCommand : public AbstractCreationCommand
{
private:
	int objectCount;
public:
	ConstantCreationCommand(int objectCount_, bool enableDebugOutput_ = false);
	void execute(AbstractEvolutionWorld& world);
	void setObjectCount(int newObjectCount);
};

#endif
