//
// Created by black on 28.05.18.
//

#include <condition_variable>
#include <Timer.hpp>
#include <fstream>
#include <spdlog/spdlog.h>
#include "include/MainController.hpp"
#include "FeedingTrough.hpp"

namespace spd = spdlog;

void MainController::init()
{
	std::condition_variable      var;
	std::mutex                   mutex;
	std::unique_lock<std::mutex> scopedLock{mutex};

	initialiseLogger();
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
	close();

}

const std::shared_ptr<MainScreenManager::WindowStorage>& MainController::getWindowStorage() const
{
	return windowStoragePtr_;
}

void MainController::loadPlaces()
{
	spd::get("main")->info("Loading places.");
	windowStoragePtr_->registerNewPlace(new FeedingTrough);

}

void MainController::allocateStorage()
{
	spd::get("main")->info("Loading storage.");
	windowStoragePtr_ = std::make_shared<msm::WindowStorage>();
}

void MainController::initialiseLogger()
{
	spd::basic_logger_mt("main", "logs/dump.log");
	spd::get("main")->info("==================================================");
	spd::get("main")->info("=                  Initialized                   =");
	spd::get("main")->info("==================================================");
	spd::get("main")->flush_on(spd::level::warn);
}

void MainController::close()
{
	spd::get("main")->info("==================================================");
	spd::get("main")->info("=                    Finished                    =");
	spd::get("main")->info("==================================================");
}
