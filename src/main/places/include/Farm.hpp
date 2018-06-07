//
// Created by black on 05.06.18.
//

#pragma once


#include <Place.hpp>
#include <thread>
#include "Rally.hpp"

class Farm
		: public eng::Place
{
	Rally* rally_;
	std::thread growingThread_;

	std::optional<sf::Time> lastUpdate_{};
	const float growRate_{25.f};
	const float collectMax_{0.1f};
	float wheat_{0.f};

	int amountOfWorkers_{0};

	const int desiredBundles_{50};
	const float bundleWheatSize_{25.f};
	int bundles_{0};

	std::mutex workersMutex_;
	std::mutex wheatAccessMutex_;
	std::mutex bundleAccessMutex_;

public:
	Farm();

	void bundlePickup(eng::Agent* agent);
	void collectWheat(eng::Agent* agent);

	void growIt();
	void execute(Engine::Agent *agent) override;
	std::string getName() const override;
	void registerYourself() override;
};

