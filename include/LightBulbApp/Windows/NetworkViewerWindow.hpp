#pragma once

#ifndef _NETWORKVIEWERWINDOW_H_
#define _NETWORKVIEWERWINDOW_H_

// Library include
#include <memory>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

// Includes
#include "Windows/AbstractSubAppWindow.hpp"

// Forward declarations
class wxDataViewListCtrl;

namespace LightBulb
{
	// Forward declarations
	class NetworkViewerController;
	class AbstractNeuralNetwork;
	/**
	 * \brief The window of the network viewer app.
	 */
	class NetworkViewerWindow : public AbstractSubAppWindow
	{
	private:
		/**
		 * \brief The choice to select the neural network which should be thrown.
		 */
		wxChoice* neuralNetworksChoice;
		/**
		 * \brief The main sizer.
		 */
		wxBoxSizer* sizer;
		/**
		 * \brief The currently selected network.
		 */
		AbstractNeuralNetwork* selectedNetwork;
		/**
		 * \brief A list which shows all effernt edges.
		 */
		wxDataViewListCtrl* efferentEdgesList;
		/**
		 * \brief A list which shows all afferent edges.
		 */
		wxDataViewListCtrl* afferentEdgesList;
		/**
		 * \brief Is called after the network has been changed.
		 * \param event The event data.
		 */
		void networkChanged(wxCommandEvent& event);
		/**
		 * \brief Is called after the scroll position has changed.
		 * \param event The event data.
		 */
		void scrollEvent(wxScrollWinEvent& event);
		/**
		 * \brief Is called after the panel has been clicked.
		 * \param event The event data.
		 */
		void panelClick(wxMouseEvent& event);
		/**
		 * \brief Returns the corresponding controller
		 * \return The controller.
		 */
		NetworkViewerController& getController();
		/**
		 * \brief The panel where the network is drawn on.
		 */
		wxScrolledWindow* panel;
		/**
		 * \brief The layer count of the current network.
		 */
		int layerCount;
		/**
		 * \brief The panel width.
		 */
		int width;
		/**
		 * \brief The panel height.
		 */
		int height;
		/**
		 * \brief The index of the selected neuron.
		 */
		int selectedNeuronIndex;
		/**
		 * \brief The index of the selected layer.
		 */
		int selectedLayerIndex;
		/**
		 * \brief Computes the x coordinate of all neurons in the given layer.
		 * \param layerIndex The index of the layer.
		 * \return The x position
		 */
		int getXPos(int layerIndex) const;
		/**
		 * \brief Computes the y coordinate of the given neurons in the given layer.
		 * \param neuronIndex The index of the neuron.
		 * \param neuronCount The index of the layer.
		 * \return The y pos.
		 */
		int getYPos(int neuronIndex, int neuronCount) const;
		/**
		 * \brief Refreshes the details of the selected neuron.
		 */
		void refreshDetail();
		/**
		 * \brief Is called when the background has been erased.
		 * \param event The event data.
		 */
		void eraseBackGround(wxEraseEvent& event);
	protected:
		DECLARE_EVENT_TABLE();
	public:
		/**
		* \brief Creates the window.
		* \param controller_ The corresponding controller.
		* \param parent The parent window.
		 */
		NetworkViewerWindow(NetworkViewerController& controller_, AbstractWindow& parent);
		/**
		 * \brief Refreshes the neural network choice.
		 */
		void refreshNeuralNetworks();
		/**
		 * \brief Is called when the paint event has been thrown.
		 * \param evt The event data.
		 */
		void paintEvent(wxPaintEvent& evt);
		/**
		* \brief Is called when the window has been resized.
		* \param evt The event data.
		*/
		void resize(wxSizeEvent& evt);
		/**
		* \brief Repaints the panel.
		*/
		void paintNow();
		/**
		 * \brief Does all rendering.
		 * \param dc The canvas.
		 */
		void render(wxDC& dc);
	};
}

#endif
