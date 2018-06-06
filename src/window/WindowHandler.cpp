//
// Created by black on 24.05.18.
//

#include "WindowHandler.hpp"
#include <SFML/Graphics.hpp>
#include <MainController.hpp>

namespace MainScreenManager
{
	WindowHandler::WindowHandler(
			sf::VideoMode const& videoMode
			, sf::String const& title
			, uint32_t style
			, std::shared_ptr<WindowStorage> const& windowStoragePtr
	)
	{
		renderWindow_ = std::make_unique<sf::RenderWindow>(videoMode, title, sf::Style::Default);
		renderWindow_->setActive(false);

		windowStoragePtr_ = windowStoragePtr ? windowStoragePtr : std::make_shared<WindowStorage>();
	}

	void WindowHandler::Run()
	{
		// Switch window possession to current thread
		renderWindow_->setActive(true);
		state = State::RUNNING;

		while ( state != State::STOP )
		{
			renderWindow_->setFramerateLimit(60);
			sf::Event event{};
			while ( renderWindow_->pollEvent(event))
			{
				switch ( event.type )
				{
					case sf::Event::Closed:
						spd::get("main")->info("User closed the window.");
						state = State::STOP;
						renderWindow_->close();
						break;
				}
			}

			renderWindow_->clear(sf::Color::White);
			windowStoragePtr_->draw(renderWindow_.get());
			renderWindow_->display();
		}

		state = State::STOPPED;
		spdlog::get("main")->info("WindowHandler folded correctly.");
		MainController::getInstance().stop();
	}

	void WindowHandler::Stop()
	{
		state = State::STOP;
	}

	State const& WindowHandler::getStatus()
	{
		return state;
	}
}
