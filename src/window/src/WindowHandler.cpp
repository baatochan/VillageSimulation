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

		if ( windowStoragePtr )
		{
			windowStoragePtr_ = windowStoragePtr;
		}
		else
		{
//			windowStoragePtr_ = std::make_shared<WindowStorage>();
		}
	}
}
