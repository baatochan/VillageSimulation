//
// Created by black on 07.06.18.
//

#pragma once


#include <Place.hpp>
#include <queue>
#include "Rally.hpp"

class Quarry
		: public eng::Place
{
protected:
	Rally* rally_;

	std::mutex toolsMutex_;
	std::queue<void*> toolsQueue_;
	std::condition_variable toolsSubscription_;
public:
	Quarry();

	void registerYourself() override;
	void execute(Engine::Agent *agent) override;
};

