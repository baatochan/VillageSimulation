//
// Created by black on 02.06.18.
//

#include <ScreenManager.hpp>
#include <spdlog/spdlog.h>
#include "include/Agent.hpp"

void Engine::Agent::run()
{
	while ( available_ && msm::ScreenManager::getAppStatus() != State::STOPPED )
	{
		update();
		if ( !envelope_ )
			execute();
	}
}

void Engine::Agent::execute()
{

}

void Engine::Agent::setOrder(Envelope const& envelope)
{
	spdlog::get("main")->debug(
			"New order for {}, from {}. Order: {}."
			, name_
			, envelope.target->getName()
			, envelope.message
	);
	envelope_ = std::make_unique<Envelope>(envelope);
}

Engine::Agent::Agent()
	: name_("agent_"+std::to_string(++counter_))
{
	spdlog::get("main")->debug("Created new agent: {}.", name_);
	circleShape_ = sf::CircleShape(10.f);
	circleShape_.setFillColor(sf::Color::Black);
}

void Engine::Agent::clearOrder()
{
	spdlog::get("main")->debug(
			"Removing order for {}, from {}. Order: {}."
			, name_
			, envelope_->target->getName()
			, envelope_->message
			);
	envelope_ = nullptr;
}

void Engine::Agent::stop() { available_ = false; }
sf::Shape *Engine::Agent::getShape() { return &circleShape_; }


int eng::Agent::counter_=0;
