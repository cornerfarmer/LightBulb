// Includes
#include "Graphics/AbstractWindow.hpp"
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFML/Graphics.hpp>

sf::Mutex AbstractWindow::mutex;

void AbstractWindow::run()
{
	build();

	// Create SFML's window.
	sf::RenderWindow render_window(sf::VideoMode(800, 600), "Hello world!");
	render_window.setFramerateLimit(60);
	
	window->SetAllocation(sf::FloatRect(0, 0, render_window.getSize().x, render_window.getSize().y));

	// We're not using SFML to render anything in this program, so reset OpenGL
	// states. Otherwise we wouldn't see anything.
	render_window.resetGLStates();

	// Main loop!
	sf::Event event;
	sf::Clock clock;

	while (render_window.isOpen()) {
		mutex.lock();
		render_window.setActive(true);
		window->Show(true);
		// Event processing.
		while (render_window.pollEvent(event)) {
			desktop->HandleEvent(event);

			// If window is about to be closed, leave program.
			if (event.type == sf::Event::Closed) {
				render_window.close();
			}
			else if (event.type == sf::Event::Resized) {
				window->SetAllocation(sf::FloatRect(0, 0, event.size.width, event.size.height));
			}
		}
		

		// Update SFGUI with elapsed seconds since last call.
		desktop->Update(clock.restart().asSeconds());

		// Rendering.
		render_window.clear();
		sfgui->Display(render_window);
		render_window.display();
		window->Show(false);
		mutex.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void AbstractWindow::build()
{
	sfgui.reset(new sfg::SFGUI());

	// Create a window and add the box layouter to it. Also set the window's title.
	window = sfg::Window::Create(sfg::Window::BACKGROUND);
	window->SetTitle("Hello world!");

	// Create a desktop and add the window to it.
	desktop.reset(new sfg::Desktop());
	desktop->Add(window);
	desktop->LoadThemeFromFile("../LightBulb/default.theme");
}

void AbstractWindow::open()
{
	std::thread* thread = new std::thread(&AbstractWindow::run, this);
}
