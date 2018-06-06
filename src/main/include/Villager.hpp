//
// Created by black on 06.06.18.
//

#pragma once


#include <Agent.hpp>

class Villager
		: public eng::Agent
{
protected:
	float foodLevel{100};
	float waterLevel{100};
protected:
	virtual void update() override;
public:

	Villager();
};

