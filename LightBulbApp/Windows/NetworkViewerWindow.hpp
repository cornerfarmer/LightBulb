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
class wxDataViewListCtrl;

class NetworkViewerWindow : public AbstractSubAppWindow
{
private:
	wxChoice* neuralNetworksChoice;
	wxBoxSizer* sizer;
	AbstractNeuralNetwork* selectedNetwork;
	wxDataViewListCtrl* efferentEdgesList;
	wxDataViewListCtrl* afferentEdgesList;
	void networkChanged(wxCommandEvent& event);
	void scrollEvent(wxScrollWinEvent& event);
	void panelClick(wxMouseEvent& event);
	NetworkViewerController* getController();
	wxScrolledWindow* panel;
	int layerCount, width, height;
	int selectedNeuronIndex;
	int selectedLayerIndex;
	int getXPos(int layerIndex);
	int getYPos(int neuronIndex, int neuronCount);
	void refreshDetail();
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
