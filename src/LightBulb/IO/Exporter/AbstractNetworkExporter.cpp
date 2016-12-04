// Includes
#include "LightBulb/IO/Exporter/AbstractNetworkExporter.hpp"
#include <fstream>

void LightBulb::AbstractNetworkExporter::exportToFile(std::string path, const AbstractNeuralNetwork& neuralNetwork)
{
	std::ofstream os(path);
	os << exportToString(neuralNetwork);
	os.close();
}
