//
// Created by black on 05.06.18.
//

#include <MainController.hpp>
#include <Timer.hpp>
#include "Farm.hpp"

Farm::Farm()
	: Place( { 300, 300 }, { 0, 110 } )
{
	getShape()->setFillColor(sf::Color::Green);
	rally_ = dynamic_cast<Rally*>(&*MainController::getInstance().getPlaces().find("RL")->second);
	growingThread_ = std::thread(std::bind(&Farm::growIt, this));
}

void Farm::execute(Engine::Agent *agent)
{
	if ( agent->getEnvelope()->message == "Farm job." )
	{
		std::unique_lock<std::mutex> uniqueLock(workersMutex_);
		amountOfWorkers_++;
		uniqueLock.unlock();

		collectWheat(agent);
		agent->setOrder(
				eng::Envelope(
						MainController::getInstance().getPlaces().find("RL")->second
						));

		std::lock_guard<std::mutex> lockGuard(bundleAccessMutex_);
		uniqueLock.lock();

		registerYourself();
		amountOfWorkers_--;
		uniqueLock.unlock();
	}
	else if ( agent->getEnvelope()->message == "Bundle pick up." )
	{
		bundlePickup(agent);
	}
}

void Farm::registerYourself()
{
	eng::Envelope const* envelope = nullptr;
	for ( auto const& element : rally_->getOfferList() )
	{
		if ( element.message == "Farm job." )
		{
			envelope = &element;
		}
	}
	if ( !envelope )
	{
		rally_->addOffer(eng::Envelope{MainController::getInstance().getPlaces().find("FR")->second
									   , "Farm job."
									   , bundles_ <= desiredBundles_ ? 30 : 1});
	}

	envelope = nullptr;
	for ( auto const& element : rally_->getOfferList() )
	{
		if ( element.message == "Bundle pick up." )
		{
			envelope = &element;
		}
	}
	if ( !envelope )
	{
		rally_->addOffer(eng::Envelope{MainController::getInstance().getPlaces().find("FR")->second
									   , "Bundle pick up."
									   , bundles_ == 0 ? 1 : bundles_});
	}
}

std::string Farm::getName() const
{
	return {"Farm"};
}

void Farm::growIt()
{
	std::this_thread::sleep_for(std::chrono::seconds(2));
	spdlog::get("main")->info("Wheat started to grow.");
	lastUpdate_=Timer::getClock().getElapsedTime();
	while(msm::ScreenManager::getAppStatus() != State::STOPPED)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
		std::lock_guard<std::mutex> lockGuard(wheatAccessMutex_);

		if ( lastUpdate_ )
		{
			auto current = Timer::getClock().getElapsedTime();
			auto delta = current - *lastUpdate_;
			lastUpdate_ = current;

			wheat_ += delta.asSeconds() * growRate_;
		}
	}
	spdlog::get("main")->info("Wheat have withered under gods fury");
}

void Farm::collectWheat(eng::Agent *agent)
{
	float myBundle{0};
	spdlog::get("main")->info("{} started wheat gathering.", agent->getName());

	spdlog::get("main")->info("Amount of wheat: {}", wheat_);
	while ( myBundle < bundleWheatSize_ )
	{
		std::lock_guard<std::mutex> lockGuard(wheatAccessMutex_);

		if ( collectMax_ > wheat_ )
		{
			myBundle += wheat_;
			wheat_ = 0;
		}
		else
		{
			wheat_ -= collectMax_;
			myBundle += collectMax_;
		}
	}
	std::lock_guard<std::mutex> lockGuard(bundleAccessMutex_);

	bundles_++;
	spdlog::get("main")->info("{} bundles.", bundles_);
	spdlog::get("main")->info("{} finished wheat gathering.", agent->getName());
}

void Farm::bundlePickup(eng::Agent *agent)
{
	std::lock_guard<std::mutex> lockGuard(bundleAccessMutex_);

	if ( bundles_ == 0 )
	{
		agent->setOrder(
				eng::Envelope(
						MainController::getInstance().getPlaces().find("RL")->second
				));
		registerYourself();
		return;
	}

	if ( bundles_ <= desiredBundles_ )
	{
		eng::Envelope const* envelope = nullptr;
		for ( auto const& element : rally_->getOfferList() )
		{
			if ( element.message == "Farm job." )
			{
				envelope = &element;
			}
		}
		if ( !envelope )
		{
			rally_->addOffer(
					eng::Envelope(
							MainController::getInstance().getPlaces().find("FR")->second
							, "Farm job."
							, desiredBundles_ - bundles_
					));
		}

	}
	if ( bundles_ > 10 )
	{
		eng::Envelope const* envelope = nullptr;
		for ( auto const& element : rally_->getOfferList() )
		{
			if ( element.message == "Bundle pick up." )
			{
				envelope = &element;
			}
		}
		if ( !envelope )
		{
			rally_->addOffer(eng::Envelope{MainController::getInstance().getPlaces().find("FR")->second
										   , "Bundle pick up."
										   , bundles_});
		}
	}

	agent->setOrder(
			eng::Envelope(
					MainController::getInstance().getPlaces().find("FT")->second
					, "Deliv Food."
					, 1
			));

	bundles_--;
}
