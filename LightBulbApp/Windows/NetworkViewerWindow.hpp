#pragma once

#ifndef _NETWORKVIEWERWINDOW_H_
#define _NETWORKVIEWERWINDOW_H_

// Library include
#include <memory>

// Includes
#include "Windows/AbstractSubAppWindow.hpp"

// Forward declarations
class NetworkViewerController;
class AbstractNeuralNetwork;

class NetworkViewerWindow : public AbstractSubAppWindow
{
private:
	wxChoice* neuralNetworksChoice;
	wxBoxSizer* sizer;
	AbstractNeuralNetwork* selectedNetwork;
	void networkChanged(wxCommandEvent& event);
	void scrollEvent(wxScrollWinEvent& event);
	NetworkViewerController* getController();
	wxScrolledWindow* panel;
	int layerCount, width, height;
	int getXPos(int layerIndex);
	int getYPos(int neuronIndex, int neuronCount);
protected:
	DECLARE_EVENT_TABLE();
public:
	NetworkViewerWindow(NetworkViewerController* controller_, AbstractWindow* parent = NULL);
	void refreshNeuralNetworks();
	void paintEvent(wxPaintEvent & evt);
	void resize(wxSizeEvent & evt);
	void paintNow();
	void render(wxDC& dc);
};

#endif
