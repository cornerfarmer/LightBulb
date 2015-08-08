#pragma once

#ifndef _GRIDSTRUCTURE_H_
#define _GRIDSTRUCTURE_H_

// Libary includes


// Includes
#include "NetworkTopology\AbstractSOMStructure.hpp"

// Forward declarations

class GridStructure : public AbstractSOMStructure
{
private:	
public:
	void initialize(SOMNetwork& somNetwork);
};

#endif