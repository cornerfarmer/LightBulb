#pragma once

#ifndef _ABSTRACTCREATIONCOMMAND_H_
#define _ABSTRACTCREATIONCOMMAND_H_

// Library Includes

// Forward declarations

class EvolutionWorldInterface;

class AbstractCreationCommand
{
public:
	virtual void execute(EvolutionWorldInterface& world) = 0;
};

#endif