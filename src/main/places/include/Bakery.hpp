//
// Created by black on 05.06.18.
//

#pragma once


#include <Place.hpp>

class Bakery
		: public eng::Place
{
public:
	Bakery();

public:
	virtual void registerYourself() override;
	virtual void execute(Engine::Agent *agent) override;
};

