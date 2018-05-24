//
// Created by black on 24.05.18.
//

#include "ScreenManager.hpp"

void MainScreenManager::ScreenManager::initialise(
		sf::VideoMode const &videoMode
		, sf::String const &title
		, unsigned const &style
		, std::shared_ptr<MainScreenManager::WindowStorage> windowStorage
)
{
	instance_ = std::make_unique<WindowHandler>(
			videoMode
			, title
			, style
			, windowStorage
	);
}

std::unique_ptr<msm::WindowHandler> msm::ScreenManager::instance_;