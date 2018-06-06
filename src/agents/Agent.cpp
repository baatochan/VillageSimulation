//
// Created by black on 02.06.18.
//

#include <ScreenManager.hpp>
#include <spdlog/spdlog.h>
#include <Timer.hpp>
#include "include/Agent.hpp"

void Engine::Agent::run()
{
	while ( available_ && msm::ScreenManager::getAppStatus() != State::STOPPED )
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
//		update();
		if ( envelope_ )
			execute();
	}
}

void Engine::Agent::execute()
{
	if ( envelope_->target )
	{
		move();
	}
	else
	{
		spdlog::get("main")->debug(
				"Envelope target is not set for {}."
				, name_
		);
	}
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

	speed_ = 25.f;
	moving_ = false;

	lastUpdate_ = Timer::getClock().getElapsedTime();
	knownLine_ = {};

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

void Engine::Agent::move()
{
	if ( !moving_ )
	{
		lastUpdate_ = Timer::getClock().getElapsedTime();
		moving_ = true;
	}
	if ( !knownLine_ ) calculateLine();

	auto currentTime = Timer::getClock().getElapsedTime();
	auto delta = currentTime - lastUpdate_;
	lastUpdate_ = currentTime;

	auto distance = delta.asSeconds() * speed_;

	auto distanceX = static_cast<float>(sin(knownLine_->z) * distance);
	auto distanceY = static_cast<float>(cos(knownLine_->z) * distance);

	sf::Vector2f lastPosition = getShape()->getPosition();
	getShape()->move({distanceX,distanceY});

	float const& targetX = envelope_->target->getShape()->getPosition().x;
	float const& targetY = envelope_->target->getShape()->getPosition().y;
	float const& positionX = circleShape_.getPosition().x;
	float const& positionY = circleShape_.getPosition().y;

	if ( (positionX > targetX && lastPosition.x < targetX) || (positionX < targetX && lastPosition.x > targetX) )
	{
		spdlog::get("main")->debug("{} arrived at the destination.", name_);
		spdlog::get("main")->flush();
		envelope_ = {};
		moving_ = false;
	}
}

void Engine::Agent::calculateLine()
{
	auto ledgeX = circleShape_.getPosition().x - envelope_->target->getShape()->getPosition().x;
	auto ledgeY = circleShape_.getPosition().y - envelope_->target->getShape()->getPosition().y;

	auto a = std::abs( ledgeX / ledgeY );
	auto b = circleShape_.getPosition().y - ( circleShape_.getPosition().x * a );
	auto angle =std::atan2( std::abs( ledgeX ), std::abs( ledgeY ) );

	knownLine_ = sf::Vector3f{ a, b, angle };
	spdlog::get("main")->debug(
			"Found a: {}, b: {}, angle: {}"
   			, a
			, b
			, angle);
	spdlog::get("main")->flush();
}

std::string const& Engine::Agent::getName() const
{
	return name_;
}
