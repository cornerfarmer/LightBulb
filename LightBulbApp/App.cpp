#include "App.hpp"
#include "Windows/TrainingWindow.hpp"

bool App::OnInit()
{
	TrainingWindow *window = new TrainingWindow();
	window->Show(true);
	return true;
}