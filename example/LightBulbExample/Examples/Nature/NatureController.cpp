// Includes
#include "Examples/Nature/NatureController.hpp"
// Library includes
#include <TrainingPlans/AbstractTrainingPlan.hpp>
#include "Nature.hpp"
#include "NatureExample.hpp"


using namespace LightBulb;

NatureController::NatureController(AbstractMainApp& mainApp, AbstractTrainingPlan& trainingPlan_, AbstractWindow& parent)
	:AbstractCustomSubApp(mainApp, trainingPlan_)
{
	environment = static_cast<Nature*>(&static_cast<NatureExample*>(trainingPlan)->getEnvironment());
	window.reset(new NatureWindow(*this, parent));
	tiles.resize(environment->getWidth(), std::vector<const wxBrush*>(environment->getHeight()));
	renderingInProgress = false;
}

void NatureController::prepareClose()
{
	stopWatchMode();
}

NatureWindow& NatureController::getWindow()
{
	return *window.get();
}

void NatureController::stopWatchMode()
{
	environment->stopWatchMode();
	environment->removeObserver(EVT_FIELD_CHANGED, &NatureController::fieldChanged, *this);
}


void NatureController::startWatchMode()
{
	environment->startWatchMode();
	environment->registerObserver(EVT_FIELD_CHANGED, &NatureController::fieldChanged, *this);
}


std::string NatureController::getLabel()
{
	return "Nature";
}


std::vector<std::vector<const wxBrush*>>& NatureController::getTiles()
{
	return tiles;
}

void NatureController::fieldChanged(Nature& nature)
{
	if (!renderingInProgress) {
		renderingInProgress = true;
		for (int x = 0; x < nature.getWidth(); x++)
		{
			for (int y = 0; y < nature.getHeight(); y++)
			{
				if (!nature.isTileFree(x, y))
					tiles[x][y] = wxRED_BRUSH;
				else
					tiles[x][y] = &nature.getTile(x, y).getColor();
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		wxThreadEvent evt(NATURE_EVT_FIELD_CHANGED);
		window->GetEventHandler()->QueueEvent(evt.Clone());
	}
}

void NatureController::renderingFinished()
{
	renderingInProgress = false;
}
