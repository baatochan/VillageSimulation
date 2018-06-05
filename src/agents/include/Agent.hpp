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
		static int counter_;
	protected:
		bool available_;
		sf::CircleShape circleShape_;
		std::unique_ptr<Envelope> envelope_;

		std::string name_;

	protected:
		virtual void update() = 0;
		void execute();
	public:
		Agent();

		void run();
		void stop();

		void setOrder(Envelope const& envelope);
		void clearOrder();

		sf::Shape *getShape() override;
	};
}

