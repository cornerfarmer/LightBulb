#include "App.hpp"
#include <wx/wxprec.h>
#include "Examples/BackpropagationXor/BackpropagationXorExample.hpp"
#include "Examples/TeachedEvolution/TeachedEvolutionExample.hpp"
#include "Examples/TicTacToeEvolution/TicTacToeEvolutionExample.hpp"
#include "Examples/FunctionEvolution/FunctionEvolutionExample.hpp"
#include "Examples/NetworkEvolution/NetworkEvolutionExample.hpp"
#include "Examples/TCProblemEvolution/TCProblemEvolutionExample.hpp"
#include "Examples/TCProblemBackpropagation/TCProblemBackpropagationExample.hpp"
#include "Examples/PongEvolution/PongEvolutionExample.hpp"
#include "Examples/PongReinforcement/PongPolicyGradientExample.hpp"
#include "Examples/SimpleReinforcement/SimpleReinforcementExample.hpp"
#include "Examples/PongReinforcement/PongDQNExample.hpp"
#include "Examples/SimpleReinforcement/SimpleReinforcementDQNExample.hpp"
#include "Examples/MountainCar/MountainCarDQNExample.hpp"
#include "Examples/Nature/NatureExample.hpp"

void main(int argc, char** argv)
{
	LightBulb::App* app = new LightBulb::App();
	app->addTrainingPlan(new BackpropagationXorExample());
	app->addTrainingPlan(new FunctionEvolutionExample());
	app->addTrainingPlan(new NetworkEvolutionExample());
	app->addTrainingPlan(new NatureExample());
	app->addTrainingPlan(new TicTacToeEvolutionExample());
	app->addTrainingPlan(new TeachedEvolutionExample());
	app->addTrainingPlan(new TCProblemEvolutionExample());
	app->addTrainingPlan(new TCProblemBackpropagationExample());
	app->addTrainingPlan(new PongEvolutionExample());
	app->addTrainingPlan(new PongPolicyGradientExample());
	app->addTrainingPlan(new PongDQNExample());
	app->addTrainingPlan(new SimpleReinforcementExample());
	app->addTrainingPlan(new SimpleReinforcementDQNExample());
	app->addTrainingPlan(new MountainCarDQNExample());

	wxApp::SetInstance(app);
	wxEntry(argc, argv);
}
