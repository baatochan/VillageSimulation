//
// Created by black on 24.05.18.
//

#include "ScreenManager.hpp"
#include <functional>

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

void MainScreenManager::ScreenManager::start()
{
	screenManagerThread_ = std::thread{&msm::WindowHandler::Run, instance_.get()};
}

void MainScreenManager::ScreenManager::stop()
{
	instance_->Stop();
}

State const &MainScreenManager::ScreenManager::getAppStatus()
{
	return instance_->getStatus();
}

void MainScreenManager::ScreenManager::cleanUp()
{
	screenManagerThread_.join();
}


std::unique_ptr<msm::WindowHandler> msm::ScreenManager::instance_;
std::thread msm::ScreenManager::screenManagerThread_;