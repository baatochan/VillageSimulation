//
// Created by black on 06.06.18.
//

#include <ScreenManager.hpp>
#include "God.hpp"

std::list<std::shared_ptr<Villager>> God::creations_;
std::list<std::thread> God::souls_;
std::mutex God::villagerMutex_;
std::chrono::milliseconds God::refresh_{250};

void God::run()
{
	spdlog::get("main")->info("God started to reign.");
	while( msm::ScreenManager::getAppStatus() != State::STOPPED )
	{
		std::this_thread::sleep_for(refresh_);
		std::lock_guard<std::mutex> lockGuard(villagerMutex_);
		for ( auto const& emet : creations_ )
		{
			emet->consume();
		}
		clear();
	}
	end();
	spdlog::get("main")->info("God have forsaken this village.");
}

std::weak_ptr<Villager> God::createVillager()
{
	std::lock_guard<std::mutex> lockGuard(villagerMutex_);

	spdlog::get("main")->debug("And God said: \"Let it be\"");

	creations_.emplace_back(new Villager);
	souls_.emplace_back(&Villager::run, creations_.back());

	return creations_.back();
}

void God::end()
{
	std::lock_guard<std::mutex> lockGuard(villagerMutex_);

	spdlog::get("main")->info("The man has now become like one of us.");
	for ( auto& met : souls_ )
	{
		met.join();
	}
}

std::list<std::shared_ptr<Villager>> const& God::getCreations()
{
	return creations_;
}

void God::clear()
{
	for ( auto i = creations_.begin(); i != creations_.end(); i++)
	{
		if ( (*i)->isAvailable() ) continue;
		creations_.remove(*i);
		i--;
	}
}
