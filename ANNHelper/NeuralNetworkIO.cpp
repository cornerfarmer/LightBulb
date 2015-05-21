#include "NeuralNetworkIO.hpp"


NeuralNetworkIO* NeuralNetworkIO::unfold()
{
	NeuralNetworkIO* unfoldedNetworkIO = new NeuralNetworkIO();
	unfoldedNetworkIO->push_back(std::vector<float>());
	for (NeuralNetworkIO::iterator ioSeries = begin(); ioSeries != end(); ioSeries++)
	{
		unfoldedNetworkIO->front().insert(unfoldedNetworkIO->front().end(), ioSeries->begin(), ioSeries->end());
	}
	return unfoldedNetworkIO;
}