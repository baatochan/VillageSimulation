//
// Created by black on 24.05.18.
//

#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "WindowStorage.hpp"

namespace MainScreenManager
{
	class WindowHandler
	{
		std::unique_ptr<sf::RenderWindow> renderWindow_;
		std::shared_ptr<WindowStorage> windowStoragePtr_;

	public:
		WindowHandler(sf::VideoMode const& videoMode
				, sf::String const& title
				, uint32_t style
				, std::shared_ptr<WindowStorage> const& windowStoragePtr
		);

	};
}

