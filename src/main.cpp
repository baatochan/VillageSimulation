#include <iostream>
#include <condition_variable>

#include "ScreenManager.hpp"

int main(int argc, char const *argv[])
{
	std::condition_variable var;
	std::mutex mutex;
	std::unique_lock<std::mutex> scopedLock{mutex};

	// Create window, and window storage, used by agents.
	msm::ScreenManager::initialise(sf::VideoMode(600,400),{"Test"}, sf::Style::Default);
	msm::ScreenManager::start();
	// Wait for the app to close the window, and clean itself up.
	var.wait(
			scopedLock,
			[&](){return msm::ScreenManager::getAppStatus() == State::STOPPED; }
		);
	// Join the thread, let him finish first.
	msm::ScreenManager::cleanUp();

	return EXIT_SUCCESS;
}
