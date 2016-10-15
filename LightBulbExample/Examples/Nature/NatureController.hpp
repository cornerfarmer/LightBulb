#pragma once

#ifndef _NATURECONTROLLER_H_
#define _NATURECONTROLLER_H_

// Includes
#include <Windows/AbstractCustomSubApp.hpp>
#include <memory>
#include "NatureWindow.hpp"
#include "Nature.hpp"


class NatureController : public LightBulb::AbstractCustomSubApp
{
private:
	std::unique_ptr<NatureWindow> window;
	Nature* world;
	std::vector<std::vector<const wxBrush*>> tiles;
	bool renderingInProgress;
protected:
	void prepareClose() override;
public:
	NatureController(LightBulb::AbstractMainApp* mainApp, LightBulb::AbstractTrainingPlan* trainingPlan, LightBulb::AbstractWindow* parent = nullptr);
	NatureWindow* getWindow();
	void stopWatchMode();
	void startWatchMode();
	static std::string getLabel();
	std::vector<std::vector<const wxBrush*>>* getTiles();
	void fieldChanged(Nature* nature);
	void renderingFinished();
};

#endif
