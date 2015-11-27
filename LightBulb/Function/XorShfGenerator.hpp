#pragma once

#ifndef _XORSHFGENERATOR_H_
#define _XORSHFGENERATOR_H_

class XorShfGenerator
{
private:
public:
	typedef unsigned long result_type;

	unsigned long x, y, z;

	explicit XorShfGenerator()
	{	// construct
		x = 123456789;
		y = 362436069;
		z = 521288629;
	}

	static result_type(min)()
	{	// return minimum possible generated value
		return (0);
	}

	static result_type(max)()
	{	// return maximum possible generated value
		return ((result_type)-1);
	}

	result_type operator()()
	{	
		unsigned long t;
		x ^= x << 16;
		x ^= x >> 5;
		x ^= x << 1;

		t = x;
		x = y;
		y = z;
		z = t ^ x ^ y;

		return z;
	}

	double next()
	{
		return (float)(*this)() / max();
	}
};

#endif