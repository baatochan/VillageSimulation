//
// Created by black on 02.06.18.
//

#pragma once


#include <Place.hpp>

namespace Engine
{
	class Envelope
	{
	protected:
		int         amount;
		Place       *target_;
		std::string message_;

	public:
		Envelope() = default;

		Envelope(Place *target, std::string const& message = "", int amount = 0);
	};
}

