#include "App.hpp"
#include <Graphics/TrainingWindow.hpp>

bool App::OnInit()
{
	TrainingWindow *window = new TrainingWindow();
	window->Show(true);
	return true;
}