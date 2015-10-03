#pragma once

#ifndef _ABSTRACTCREATIONCOMMAND_H_
#define _ABSTRACTCREATIONCOMMAND_H_

// Library Includes

// Forward declarations

class AbstractEvolutionWorld;

class AbstractCreationCommand
{
public:
	virtual void execute(AbstractEvolutionWorld& world) = 0;
};

#endif