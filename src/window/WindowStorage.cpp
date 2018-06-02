//
// Created by black on 24.05.18.
//

#include "WindowStorage.hpp"

void MainScreenManager::WindowStorage::registerNewPlace(eng::Place *placePtr)
{
	std::lock_guard<std::mutex> lockGuard(placeVectorMutex_);

	placeVector_.push_back(placePtr);
}

void MainScreenManager::WindowStorage::draw(sf::RenderWindow *targetWindow)
{
	std::lock_guard<std::mutex> placeLockGuard(placeVectorMutex_);
	std::lock_guard<std::mutex> agentLockGuard(agentMutex_);

	for( auto element : placeVector_ )
	{
		targetWindow->draw(*element->getShape());
	}
	for( auto element : drawableVector_ )
	{
		targetWindow->draw(*element->getShape());
	}
}
