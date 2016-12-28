#include "LightBulbApp/App.hpp"
#include <wx/wxprec.h>
#include "Examples/BackpropagationXor/BackpropagationXorExample.hpp"
#include "Examples/TeachedEvolution/TeachedEvolutionExample.hpp"
#include "Examples/TicTacToeEvolution/TicTacToeEvolutionExample.hpp"
#include "Examples/FunctionEvolution/FunctionEvolutionExample.hpp"
#include "Examples/NetworkEvolution/NetworkEvolutionExample.hpp"
#include "Examples/PongEvolution/PongEvolutionExample.hpp"
#include "Examples/PongReinforcement/PongPolicyGradientExample.hpp"
#include "Examples/PongReinforcement/PongDQNExample.hpp"
#include "Performance/ViennaCLTests.hpp"

int main(int argc, char** argv)
{
	//doViennaCLTest();

	LightBulb::App* app = new LightBulb::App();
	app->addTrainingPlan(new BackpropagationXorExample());
	app->addTrainingPlan(new FunctionEvolutionExample());
	app->addTrainingPlan(new NetworkEvolutionExample());
	app->addTrainingPlan(new TicTacToeEvolutionExample());
	app->addTrainingPlan(new TeachedEvolutionExample());
	app->addTrainingPlan(new PongEvolutionExample());
	app->addTrainingPlan(new PongPolicyGradientExample());
	app->addTrainingPlan(new PongDQNExample());

	wxApp::SetInstance(app);
	wxEntry(argc, argv);

	return 0;
}
