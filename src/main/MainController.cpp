//
// Created by black on 28.05.18.
//

#include <condition_variable>
#include <Timer.hpp>
#include <fstream>
#include <spdlog/spdlog.h>
#include <Villager.hpp>
#include <God.hpp>
#include "include/MainController.hpp"
#include "FeedingTrough.hpp"

namespace spd = spdlog;

void MainController::init()
{
	instance_ = this;

	initialiseLogger();
	allocateStorage();
	loadPlaces();

	// Create window, and window storage, used by agents.
	msm::ScreenManager::initialise(sf::VideoMode(800, 600), {"Test"}, sf::Style::Default, windowStoragePtr_);
	msm::ScreenManager::start();

	summonGod();

	// Wait for the app to close the window, and clean itself up.
	var.wait(scopedLock, [&]()
	{ return msm::ScreenManager::getAppStatus() == State::STOPPED; } );

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
	places_.insert(std::pair("FT", new FeedingTrough));
	windowStoragePtr_->registerNewPlace(places_["FT"]);
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
	spd::get("main")->flush_on(spd::level::debug);
	spd::get("main")->set_level(spdlog::level::debug);
}

void MainController::close()
{
	spd::get("main")->info("Betraying God.");
	GodThread.join();

	spd::get("main")->info("==================================================");
	spd::get("main")->info("=                    Finished                    =");
	spd::get("main")->info("==================================================");
	spd::get("main")->flush();
}

MainController& MainController::getInstance()
{
	return *instance_;
}

void MainController::stop()
{
	var.notify_all();
}

void MainController::summonGod()
{
	GodThread = std::thread(God::run);
}

std::map<std::string, std::shared_ptr<Engine::Place>> const& MainController::getPlaces() const
{
	return places_;
}

MainController* MainController::instance_;
