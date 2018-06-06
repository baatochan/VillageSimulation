//
// Created by black on 07.06.18.
//

#include <MainController.hpp>
#include <Rally.hpp>
#include "Quarry.hpp"
#include <string>

Quarry::Quarry()
		: Place( { 400, 400 }, { 500, 0 } )
{
	getShape()->setFillColor(sf::Color::Red);
	rally_ = dynamic_cast<Rally*>(&*MainController::getInstance().getPlaces().find("RL")->second);

	toolsQueue_.push(nullptr);
	toolsQueue_.push(nullptr);
	toolsQueue_.push(nullptr);
	toolsQueue_.push(nullptr);
}

void Quarry::execute(Engine::Agent *agent)
{
	std::unique_lock<std::mutex> uniqueLock(toolsMutex_);

	if ( toolsQueue_.empty() )
	{
		toolsSubscription_.wait_for(
				uniqueLock, std::chrono::seconds(30), [&](){
					return 	!toolsQueue_.empty();
				});
		if ( toolsQueue_.empty() )
		{
			agent->setOrder(
					eng::Envelope(
							MainController::getInstance().getPlaces().find("RL")->second
							));
			return;
		}
	}

	spdlog::get("main")->debug("{} started mining!");
	auto tool = toolsQueue_.front();
	toolsQueue_.pop();
	uniqueLock.unlock();

	std::this_thread::sleep_for(std::chrono::seconds(10));

	spdlog::get("main")->info("{} got a lot of ore!");
	uniqueLock.lock();
	toolsQueue_.push(tool);
	toolsSubscription_.notify_one();

	agent->setOrder(
			eng::Envelope(
					MainController::getInstance().getPlaces().find("RL")->second
			));
	if ( toolsQueue_.size() == 4 )
		registerYourself();
}

void Quarry::registerYourself()
{
	rally_->addOffer(
			eng::Envelope{
					MainController::getInstance().getPlaces().find("QR")->second
					, "Quarry job."
					, 10
			}
			);
}
