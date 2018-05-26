//
// Created by black on 24.05.18.
//

#include "WindowHandler.hpp"
#include <SFML/Graphics.hpp>

namespace MainScreenManager
{
	WindowHandler::WindowHandler(
			sf::VideoMode const &videoMode
			, sf::String const &title
			, uint32_t style
			, std::shared_ptr<WindowStorage> const &windowStoragePtr
	)
	{
		renderWindow_ = std::make_unique<sf::RenderWindow>(videoMode, title, sf::Style::Default);
		renderWindow_->setActive(false);

		if ( windowStoragePtr )
		{
			windowStoragePtr_ = windowStoragePtr;
		}
		else
		{
//			windowStoragePtr_ = std::make_shared<WindowStorage>();
		}
	}

	WindowHandler::~WindowHandler()
	{}

	void WindowHandler::Run()
	{
		// Switch window possession to current thread
		renderWindow_->setActive(true);
		state = State::RUNNING;

		while( state != State::STOP )
		{
			sf::Event event{};
			while (renderWindow_->pollEvent(event))
			{
				switch (event.type)
				{
					case sf::Event::Closed:
						state = State::STOP;
						renderWindow_->close();
						break;
				}
			}

			renderWindow_->clear(sf::Color::White);
			renderWindow_->display();
		}

		state = State::STOPPED;
	}

	void WindowHandler::Stop()
	{
		state=State::STOP;
	}

	State const& WindowHandler::getStatus()
	{
		return state;
	}
}
