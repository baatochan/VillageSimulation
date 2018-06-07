//
// Created by black on 05.06.18.
//

#include <Rally.hpp>
#include <MainController.hpp>
#include "Well.hpp"

void Well::execute(Engine::Agent *agent)
{
	if ( agent->getEnvelope()->message == "Well using." )
	{
		useWell(agent);
	}
	else
	{
		transport(agent);
	}
}

Well::Well()
		: Place( { 20, 20 }, { 350, 300 } )
{
	getShape()->setFillColor(sf::Color(64, 164, 223));
	rally_ = dynamic_cast<Rally*>(
			&*MainController::getInstance().getPlaces().find("RL")->second
	);
}

void Well::registerYourself()
{
	rally_->addOffer(
			eng::Envelope{
					MainController::getInstance().getPlaces().find("WL")->second
					, "Well using."
					, 2
			}
	);
	rally_->addOffer(
			eng::Envelope{
					MainController::getInstance().getPlaces().find("WL")->second
					, "Well transport."
					, readyBuckets_ == 0 ? 1 : readyBuckets_
			}
	);
}

std::string Well::getName() const
{
	return {"Well"};
}

void Well::useWell(eng::Agent *agent)
{
	std::unique_lock<std::mutex> uniqueLock(wellerMutex_);

	if ( amountOfWellers_ >= 2 )
		return;

	amountOfWellers_++;
	if ( amountOfWellers_ == 1 )
	{
		wellers_.first = agent;
		partnerHolder_.wait( uniqueLock, [&](){
			return amountOfWellers_==0;
		});
	}
	else
	{
		wellers_.second = agent;

		spdlog::get("main")->info(
				"{} and {} use Well."
				, wellers_.first->getName()
				, wellers_.second->getName()
		);

		while ( readyBuckets_ <= desiredBuckets_ )
		{
			std::lock_guard<std::mutex> lockGuard(bucketMutex_);

			std::this_thread::sleep_for(pullTime);
			readyBuckets_++;
		}
		spdlog::get("main")->info("{} buckets ready.", readyBuckets_);

		amountOfWellers_ = 0;
		registerYourself();
		partnerHolder_.notify_one();
	}

	agent->setOrder(
			eng::Envelope(
					MainController::getInstance().getPlaces().find("RL")->second
			));
}

void Well::transport(eng::Agent* agent)
{
	std::lock_guard<std::mutex> lockGuard(bucketMutex_);

	agent->setOrder(
			eng::Envelope(
					MainController::getInstance().getPlaces().find("FT")->second
					, "Deliv water."
	   				, 1
					));

	readyBuckets_--;
}
