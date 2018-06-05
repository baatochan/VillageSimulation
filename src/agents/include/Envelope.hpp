//
// Created by black on 02.06.18.
//

#pragma once


#include <Place.hpp>

namespace Engine
{
	struct Envelope
	{
		int         amount;
		Place       *target;
		std::string message;

		Envelope() = default;
		Envelope(Place *target, std::string const& message = "", int amount = 0);
	};
}

