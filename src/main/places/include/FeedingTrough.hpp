//
// Created by black on 02.06.18.
//

#pragma once


#include <Place.hpp>
#include <Agent.hpp>
#include <Villager.hpp>
#include <list>
#include <condition_variable>

class FeedingTrough : public eng::Place
{
	float foodAmount_{10000.f};
	float waterAmount_{10000.f};

	unsigned availableStools_{10u};
protected:
	std::list<Villager*> stools_;

	std::condition_variable subHolder_;

	std::mutex stoolsMutex_;
	std::mutex foodMutex_;
	std::mutex waterMutex_;
protected:
	FeedingTrough(const sf::Vector2f& size, const sf::Vector2f& position);

	void acceptFood(eng::Agent* agent);
	void acceptWater(eng::Agent* agent);
	void feast(Villager* villager);
	void eat(Villager* villager, int amount);
	void drink(Villager* villager, int amount);

public:
	explicit FeedingTrough();

	void execute(eng::Agent* agent) final;
	std::string getName() const final;
};

