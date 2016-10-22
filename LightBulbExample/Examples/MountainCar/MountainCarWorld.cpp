// Includes
#include "Examples/MountainCar/MountainCarWorld.hpp"
#include <Learning/LearningState.hpp>

//Library includes

using namespace LightBulb;

MountainCarWorld::MountainCarWorld(FeedForwardNetworkTopologyOptions& options_, bool epsilonGreedly, double epsilon)
	: AbstractReinforcementWorld(options_, epsilonGreedly, epsilon)
{
	pos = -0.5;
	vel = 0;
	watchMode = false;
}

double MountainCarWorld::doSimulationStep()
{
	if (isTerminalState())
	{
		pos = -0.5;
		vel = 0;
	}

	doNNCalculation();

	if (watchMode)
	{
		throwEvent(EVT_POS_CHANGED, *this);
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
		
	return -1;
}

void MountainCarWorld::getNNInput(std::vector<double>& input)
{
	input.resize(2);
	
	input[0] = pos;
	input[1] = vel;
}

void MountainCarWorld::interpretNNOutput(std::vector<bool>& output)
{
	if (output[0])
		action = -1;
	else if (output[1])
		action = 0;
	else if (output[2])
		action = 1;

	vel += action * 0.001 + std::cos(3 * pos) * -0.0025;
	vel = std::max(-0.07, std::min(0.07, vel));
	pos += vel;
	pos = std::max(-1.2, std::min(0.7, pos));

}


std::vector<std::string> MountainCarWorld::getDataSetLabels() const
{
	auto labels = AbstractReinforcementWorld::getDataSetLabels();
	return labels;
}

bool MountainCarWorld::isTerminalState()
{
	return pos >= 0.6;
}

double MountainCarWorld::getPosition()
{
	return pos;
}

double MountainCarWorld::getVelocity()
{
	return vel;
}

int MountainCarWorld::getAction()
{
	return action;
}

void MountainCarWorld::startWatchMode()
{
	watchMode = true;
}

void MountainCarWorld::stopWatchMode()
{
	watchMode = false;
}