#pragma once

#ifndef _ACTIVATIONORDER_H_
#define _ACTIVATIONORDER_H_

class NetworkTopology;

class ActivationOrder
{
private:
public:
	 virtual void executeActivation(NetworkTopology &networkTopology) = 0;
};

#endif