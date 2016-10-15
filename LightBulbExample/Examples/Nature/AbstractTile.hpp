#pragma once

#ifndef _ABSTRACTTILE_H_
#define _ABSTRACTTILE_H_

// Library Includes
#include <wx/wxprec.h>

// Includes

// Forward declarations


class AbstractTile 
{
protected:	
public:
	virtual ~AbstractTile() {};
	virtual float tryToEat() = 0;
	virtual bool isWalkable() = 0;
	virtual double getViewValue() = 0;
	virtual const wxBrush* getColor() = 0;
};
#endif