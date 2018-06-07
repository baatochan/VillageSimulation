//
// Created by black on 24.05.18.
//

#include <God.hpp>
#include "WindowStorage.hpp"

void MainScreenManager::WindowStorage::registerNewPlace(std::shared_ptr<eng::Place> const& placePtr)
{
	spd::get("main")->info("Detected new place registration for: {}.", placePtr->getName());
	if(!placePtr)
		spd::get("main")->critical("Detected null registration!");

	std::lock_guard<std::mutex> lockGuard(placeVectorMutex_);

	placeVector_.push_back(placePtr);
}

void MainScreenManager::WindowStorage::registerNewAgent(std::shared_ptr<eng::Agent> const& agentPtr)
{
	spd::get("main")->info("Detected new Agent registration.");
	if(!agentPtr)
		spd::get("main")->critical("Detected null registration!");

	std::lock_guard<std::mutex> lockGuard(agentMutex_);

	agentVector_.push_back(agentPtr);
}

void MainScreenManager::WindowStorage::draw(sf::RenderWindow *targetWindow)
{
	std::lock_guard<std::mutex> placeLockGuard(placeVectorMutex_);
	std::lock_guard<std::mutex> agentLockGuard(agentMutex_);

	for( auto const& elementWPtr : placeVector_ )
	{
		auto element = elementWPtr.lock();
		if ( element )
		{
			targetWindow->draw(*element->getShape());
		}
	}
	for( auto const& element : God::getCreations() )
	{
		targetWindow->draw(*element->getShape());
	}
}

std::vector<std::weak_ptr<eng::Place>> const& MainScreenManager::WindowStorage::getPlaces()
{
	std::lock_guard<std::mutex> lockGuard(agentMutex_);

	return placeVector_;
}
