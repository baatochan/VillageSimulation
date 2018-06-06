//
// Created by black on 02.06.18.
//

#pragma once

#include <utility>
#include <Place.hpp>

namespace Engine
{
	class Place;
	struct Envelope
	{
		int         amount{0};
		Place       *target{nullptr};
		std::string message{};

		Envelope() = default;
		explicit Envelope(Place *target, std::string message = "", int amount = 0)
				: target(target), message(std::move(message)), amount(amount)
		{}
	};
}

