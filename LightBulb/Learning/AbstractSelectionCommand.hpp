#pragma once

#ifndef _ABSTRACTSELECTIONCOMMAND_H_
#define _ABSTRACTSELECTIONCOMMAND_H_

// Library Includes

// Forward declarations

class EvolutionWorldInterface;

class AbstractSelectionCommand
{
public:
	virtual void execute(EvolutionWorldInterface& world) = 0;
};

#endif