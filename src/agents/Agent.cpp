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
		update();
		if ( envelope_ )
			execute();
	}
	spdlog::get("main")->debug("{} is no more.", name_);
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
	knownLine_={};
	envelope_={};

	spdlog::get("main")->debug(
			"New order for {}. Target: {}."
			, name_
			, envelope.target->getName()
	);
	envelope_ = std::make_unique<Envelope>(envelope);
}

Engine::Agent::Agent()
	: name_("agent_"+std::to_string(++counter_))
{
	spdlog::get("main")->debug("Created new agent: {}.", name_);

	lastUpdate_ = Timer::getClock().getElapsedTime();

	circleShape_ = sf::CircleShape(10.f);
	circleShape_.setFillColor(sf::Color::Black);
}

void Engine::Agent::clearOrder()
{
	spdlog::get("main")->debug(
			"Removing order for {}, from {}."
			, name_
			, envelope_->target->getName()
			);
	envelope_ = nullptr;
}

void Engine::Agent::stop() { available_ = false; }
sf::Shape *Engine::Agent::getShape() { return &circleShape_; }

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



	if ( envelope_->target->getShape()->getPosition().y < circleShape_.getPosition().y )
	{
		if ( speed_ > 0 )
		{
			speed_ *= -1;
		}
	} else
	{
		if ( speed_ < 0)
		{
			speed_ *= -1;
		}
	}

	auto distance = delta.asSeconds() * speed_;

	auto distanceX = static_cast<float>(sin(knownLine_->z) * distance);
	auto distanceY = static_cast<float>(cos(knownLine_->z) * distance);

	sf::Vector2f lastPosition = getShape()->getPosition();
	getShape()->move({distanceX,distanceY});

	float const& targetX = envelope_->target->getShape()->getPosition().x;
	float const& targetY = envelope_->target->getShape()->getPosition().y;
	float const& positionX = circleShape_.getPosition().x;
	float const& positionY = circleShape_.getPosition().y;

	if ( (positionX > targetX && lastPosition.x < targetX) || (positionX < targetX && lastPosition.x > targetX)
			|| (positionY > targetY && lastPosition.y < targetY) || (positionY < targetY && lastPosition.y > targetY))
	{
		envelope_->target->execute(this);
		if ( circleShape_.getPosition() == envelope_->target->getShape()->getPosition() )
		{
			spdlog::get("main")->debug("No new orders for {}.", getName());
			envelope_ = {};
			knownLine_={};
		}
		knownLine_={};
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
}

std::string const& Engine::Agent::getName() const
{
	return name_;
}

int eng::Agent::counter_=0;

bool Engine::Agent::isAvailable() const
{
	return available_;
}

std::unique_ptr<Engine::Envelope> const& Engine::Agent::getEnvelope() const
{
	return envelope_;
}
