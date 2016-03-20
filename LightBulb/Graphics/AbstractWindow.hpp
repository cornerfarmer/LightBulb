#pragma once

#ifndef _ABSTRACTWINDOW_H_
#define _ABSTRACTWINDOW_H_

// Includes
#include "Graphics/GraphicObject.hpp"
#include <SFML/Graphics.hpp>
#include <list>
#include <thread>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/Desktop.hpp>
#include <SFML/System/Mutex.hpp>

// Forward declarations

// A chart which shows the location of neurons
class AbstractWindow
{
protected:
	std::thread thread;
	static sf::Mutex mutex;
	std::unique_ptr<sfg::SFGUI> sfgui;
	std::shared_ptr<sfg::Window> window;
	std::unique_ptr<sfg::Desktop >desktop;
	void run();
	virtual void build();
public:
	void open();
};

#endif
