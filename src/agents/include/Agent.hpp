//
// Created by black on 02.06.18.
//

#pragma once


#include <SFML/Graphics/CircleShape.hpp>
#include "Envelope.hpp"

namespace Engine
{
	class Agent : public mo::IDrawable
	{
	protected:
		Envelope envelope_;

		sf::CircleShape circleShape_;
		bool available = true;

		virtual void update() = 0;
	public:
		Agent();

		void run();
		void stop();

		void setOrder(Envelope envelope);
		void goTo(Place place);

		virtual sf::Shape *getShape() override;
	};
}

