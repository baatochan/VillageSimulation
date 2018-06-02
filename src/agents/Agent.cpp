//
// Created by black on 02.06.18.
//

#include "include/Agent.hpp"

void Engine::Agent::run()
{
	while(available)
	{
		update();
	}
}

void Engine::Agent::stop()
{
	available = false;
}

void Engine::Agent::setOrder(Engine::Envelope envelope)
{
	envelope_ = envelope;
}

void Engine::Agent::goTo(Engine::Place place)
{
	place.getShape()->getPosition();
}

sf::Shape *Engine::Agent::getShape()
{
	return &circleShape_;
}

Engine::Agent::Agent()
{
	circleShape_ = sf::CircleShape(10.f);
	circleShape_.setFillColor(sf::Color::Black);
}
