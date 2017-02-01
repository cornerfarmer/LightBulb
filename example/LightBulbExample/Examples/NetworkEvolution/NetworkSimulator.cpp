// Includes
#include "LightBulbExamplePrec.hpp"
#include "Examples/NetworkEvolution/NetworkSimulator.hpp"
#include "Examples/NetworkEvolution/Network.hpp"
#include "LightBulb/Learning/Evolution/AbstractIndividual.hpp"
//Library includes
#include "LightBulb/LinearAlgebra/KernelHelper.hpp"

using namespace LightBulb;

AbstractIndividual* NetworkSimulator::createNewIndividual()
{
	return new Network(*this);
}

NetworkSimulator::NetworkSimulator(const Vector<> consumers_)
{
	consumers = consumers_;
	/*if (enableGraphics)
	{
		window.create(sf::VideoMode(800, 700), "LightBulb!");
		NetworkDrawerOptions options;
		options.networkSimulator = this;
		options.startX = -1;
		options.endX = 5;
		options.startY = -2;
		options.endY = 2;

		drawer.reset(new NetworkDrawer(options));
	}*/
}

void NetworkSimulator::doSimulationStep()
{
	for (auto position = individuals.begin(); position != individuals.end(); position++)
	{
		(*position)->doNNCalculation();
	}

	/*if (enableGraphics)
	{
		window.clear();
		drawer->recalculateAllValues();
		drawer->draw(window);
		window.display();
	}*/
}

void NetworkSimulator::getFitness(const AbstractIndividual& individual, Scalar<>& fitness) const
{
	const Vector<>& pos = static_cast<const Network&>(individual).getPositions();

	if (isCalculatorType(CT_GPU))
	{
		static viennacl::ocl::kernel& kernel = getKernel("network_evolution_example", "calc_fitness", "network_evolution_example.cl");

		viennacl::ocl::enqueue(kernel(
			viennacl::traits::opencl_handle(pos.getViennaclValue()),
			cl_uint(pos.getViennaclValue().size()),
			viennacl::traits::opencl_handle(consumers.getViennaclValue()),
			viennacl::traits::opencl_handle(fitness.getViennaclValueForEditing())
		));
	}
	else
	{
		fitness.getEigenValueForEditing() = 0;
		for (int p = 0; p < pos.getEigenValue().size(); p += 2)
		{
			fitness.getEigenValueForEditing() -= distanceBetweenPositions(pos.getEigenValue()[p], pos.getEigenValue()[p + 1], consumers.getEigenValue()[p * 2], consumers.getEigenValue()[p * 2 + 1]);
			fitness.getEigenValueForEditing() -= distanceBetweenPositions(pos.getEigenValue()[p], pos.getEigenValue()[p + 1], consumers.getEigenValue()[(p + 1) * 2], consumers.getEigenValue()[(p + 1) * 2 + 1]);
			if (p < pos.getEigenValue().size() - 2)
				fitness.getEigenValueForEditing() -= distanceBetweenPositions(pos.getEigenValue()[p], pos.getEigenValue()[p + 1], pos.getEigenValue()[p + 2], pos.getEigenValue()[p + 3]);
		}

	}
}

double NetworkSimulator::distanceBetweenPositions(float pos1X, float pos1Y, float pos2X, float pos2Y) const
{
	double distance = 0;
	distance += pow(pos1X - pos2X, 2);
	distance += pow(pos1Y - pos2Y, 2);
	return sqrt(distance);
}

Vector<>& NetworkSimulator::getConsumers()
{
	return consumers;
}
