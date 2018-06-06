//
// Created by black on 02.06.18.
//

#pragma once

#include <utility>
#include <Place.hpp>

namespace Engine
{
	struct Envelope
	{
		int         amount;
		Place       *target;
		std::string message;

		Envelope() = default;
		explicit Envelope(Place *target, std::string message = "", int amount = 0)
				: target(target), message(std::move(message)), amount(amount)
		{}
	};
}

