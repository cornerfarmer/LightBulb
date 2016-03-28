#include "App.hpp"
#include "Windows/TrainingController.hpp"
#include "Windows/LoggerController.hpp"

bool App::OnInit()
{
	TrainingController* window = new TrainingController();
	LoggerController* loggerWindow = new LoggerController();

	//window->addSubWindow(loggerWindow);
	window->setLogger(loggerWindow);

	loggerWindow->show();
	window->show();
	return true;
}
