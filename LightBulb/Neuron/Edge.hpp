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
	double weight;
	AbstractNeuron* prevNeuron;
	StandardNeuron* nextNeuron;
public:
	// Creates a new edge between the two given neurons with the given weight
	Edge(AbstractNeuron* prevNeuron_, StandardNeuron* nextNeuron_, double weight_);	
	// Returns the weight
	double getWeight();
	// Sets the weight 
	void setWeight(double newWeight);
	// Returns the prevneuron
	AbstractNeuron* getPrevNeuron();
	// Returns the next neuron
	StandardNeuron* getNextNeuron();	
	// Sets the prev neuron
	void setPrevNeuron(AbstractNeuron* newPrevNeuron);
	// Sets the next neuron
	void setNextNeuron(StandardNeuron* newNextNeuron);	
	// Sets the weight to a new random value between randStart and randEnd
	void randomizeWeight(double randStart, double randEnd);
};

#endif