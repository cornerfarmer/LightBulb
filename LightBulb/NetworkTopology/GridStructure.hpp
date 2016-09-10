#pragma once

#ifndef _GRIDSTRUCTURE_H_
#define _GRIDSTRUCTURE_H_

// Libary includes

// Includes
#include "NetworkTopology/AbstractSOMStructure.hpp"

namespace LightBulb
{
	// Forward declarations

	// Describes a grid som structure  
	class GridStructure : public AbstractSOMStructure
	{
	private:
	public:
		void initialize(SOMNetwork& somNetwork) override;
	};
}

#endif