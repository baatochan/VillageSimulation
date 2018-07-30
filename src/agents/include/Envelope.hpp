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
		int                    amount{0};
		std::string            message{};
		std::shared_ptr<Place> target{nullptr};

		Envelope() = default;

		explicit Envelope(std::shared_ptr<Place> const& target, std::string message = "", int amount = 0) //NOLINT
				: target(target), message(std::move(message)), amount(amount)
		{}
	};
}

