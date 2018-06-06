//
// Created by black on 02.06.18.
//

#pragma once


#include <Place.hpp>
#include <Agent.hpp>

class FeedingTrough : public eng::Place
{
protected:
	FeedingTrough(const sf::Vector2f& size, const sf::Vector2f& position);
public:
	explicit FeedingTrough();

	std::string getName() const final;

	void execute(eng::Agent const& agent) final;
};

