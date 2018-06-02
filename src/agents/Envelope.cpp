//
// Created by black on 02.06.18.
//

#include "Envelope.hpp"

Engine::Envelope::Envelope(Engine::Place *target, std::string const& message, int amount)
		: target_(target), message_(message), amount(amount)
{}
