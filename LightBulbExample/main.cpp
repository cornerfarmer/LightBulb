#include "App.hpp"
#include <wx/wxprec.h>
#include "Examples/BackpropagationXorExample.hpp"
#include "Examples/TeachedEvolutionExample.hpp"
#include "Examples/NatureEvolutionExample.hpp"
#include "Examples/TicTacToeEvolution/TicTacToeEvolutionExample.hpp"
#include "Examples/FunctionEvolutionExample.hpp"
#include "Examples/NetworkEvolution/NetworkEvolutionExample.hpp"
#include "Examples/RBFNetworkBiggerExample.hpp"
#include "Examples/TCProblemEvolutionExample.hpp"
#include "Examples/TCProblemBackpropagationExample.hpp"
#include "Examples/PongEvolution/PongEvolutionExample.hpp"

void main(int argc, char** argv)
{
	App* app = new App();
	app->addTrainingPlan(new RBFNetworkBiggerExample());
	app->addTrainingPlan(new BackpropagationXorExample());
	app->addTrainingPlan(new FunctionEvolutionExample());
	app->addTrainingPlan(new NetworkEvolutionExample());
	app->addTrainingPlan(new NatureEvolutionExample());
	app->addTrainingPlan(new TicTacToeEvolutionExample());
	app->addTrainingPlan(new TeachedEvolutionExample());
	app->addTrainingPlan(new TCProblemEvolutionExample());
	app->addTrainingPlan(new TCProblemBackpropagationExample());
	app->addTrainingPlan(new PongEvolutionExample());

	wxApp::SetInstance(app);
	wxEntry(argc, argv);
}
