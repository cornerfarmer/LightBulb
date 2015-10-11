#pragma once

#ifndef _LINESTRUCTURE_H_
#define _LINESTRUCTURE_H_

// Libary includes


// Includes
#include "NetworkTopology/AbstractSOMStructure.hpp"

// Forward declarations

// Describes a line som structure
class LineStructure : public AbstractSOMStructure
{
private:	
public:
	void initialize(SOMNetwork& somNetwork);
};

#endif