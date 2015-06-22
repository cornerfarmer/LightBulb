#pragma once

#ifndef _EDGE_H_
#define _EDGE_H_

// Forward declarations
class AbstractNeuron;
class StandardNeuron;

// A Edge connects two Neurons
class Edge
{
private:
	float weight;
	AbstractNeuron* prevNeuron;
	StandardNeuron* nextNeuron;
public:
	Edge(AbstractNeuron* prevNeuron_, StandardNeuron* nextNeuron_, float weight_);	
	float getWeight();
	void setWeight(float newWeight);
	AbstractNeuron* getPrevNeuron();
	StandardNeuron* getNextNeuron();	
	void setPrevNeuron(AbstractNeuron* newPrevNeuron);
	void setNextNeuron(StandardNeuron* newNextNeuron);	
	void randomizeWeight(float randStart, float randEnd);
};

#endif