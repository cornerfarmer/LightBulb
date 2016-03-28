#include "App.hpp"
#include "Windows/TrainingController.hpp"
#include "Windows/LoggerController.hpp"

bool App::OnInit()
{
	TrainingController* trainingController = new TrainingController();
	LoggerController* loggerController = new LoggerController(trainingController->getWindow());

	trainingController->addSubWindow(loggerController->getWindow());
	trainingController->setLogger(loggerController);

	trainingController->show();
	return true;
}
