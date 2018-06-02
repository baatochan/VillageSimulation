//
// Created by black on 28.05.18.
//

#include <condition_variable>
#include <Timer.hpp>
#include "include/MainController.hpp"
#include "FeedingTrough.hpp"

void MainController::init()
{
	std::condition_variable      var;
	std::mutex                   mutex;
	std::unique_lock<std::mutex> scopedLock{mutex};

	allocateStorage();
	loadPlaces();

	// Create window, and window storage, used by agents.
	msm::ScreenManager::initialise(sf::VideoMode(600, 400), {"Test"}, sf::Style::Default, windowStoragePtr_);
	msm::ScreenManager::start();

	// Wait for the app to close the window, and clean itself up.
	var.wait(scopedLock, [&]()
	{ return msm::ScreenManager::getAppStatus() == State::STOPPED; });

	// Join the thread, let him finish first.
	msm::ScreenManager::cleanUp();
}

const std::shared_ptr<MainScreenManager::WindowStorage>& MainController::getWindowStorage() const
{
	return windowStoragePtr_;
}

void MainController::loadPlaces()
{
	windowStoragePtr_->registerNewPlace(new FeedingTrough);
}

void MainController::allocateStorage()
{
	windowStoragePtr_ = std::make_shared<msm::WindowStorage>();
}
