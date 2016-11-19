// Includes
#include "Examples/MountainCar/MountainCarEnvironment.hpp"
#include <Learning/LearningState.hpp>
#include <thread>

//Library includes

using namespace LightBulb;

MountainCarEnvironment::MountainCarEnvironment(FeedForwardNetworkTopologyOptions& options_, bool epsilonGreedly, double epsilon)
	: AbstractReinforcementEnvironment(options_, epsilonGreedly, epsilon)
{
	pos = -0.5;
	vel = 0;
	watchMode = false;
}

double MountainCarEnvironment::doSimulationStep()
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

void MountainCarEnvironment::getNNInput(std::vector<double>& input)
{
	input.resize(2);

	input[0] = pos;
	input[1] = vel;
}

void MountainCarEnvironment::interpretNNOutput(std::vector<bool>& output)
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


std::vector<std::string> MountainCarEnvironment::getDataSetLabels() const
{
	auto labels = AbstractReinforcementEnvironment::getDataSetLabels();
	return labels;
}

bool MountainCarEnvironment::isTerminalState()
{
	return pos >= 0.6;
}

double MountainCarEnvironment::getPosition()
{
	return pos;
}

double MountainCarEnvironment::getVelocity()
{
	return vel;
}

int MountainCarEnvironment::getAction()
{
	return action;
}

void MountainCarEnvironment::startWatchMode()
{
	watchMode = true;
}

void MountainCarEnvironment::stopWatchMode()
{
	watchMode = false;
}
