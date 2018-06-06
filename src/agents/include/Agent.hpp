//
// Created by black on 02.06.18.
//

#pragma once


#include <SFML/Graphics/CircleShape.hpp>
#include <optional>
#include <SFML/System/Time.hpp>
#include <SFML/System.hpp>
#include "Envelope.hpp"

namespace Engine
{
	class Agent
			: public mo::IDrawable
	{
	protected:
		static int counter_;
		std::unique_ptr<Envelope>   envelope_;
		std::optional<sf::Vector3f> knownLine_;

		bool  available_{true};
		bool  moving_{false};
		float speed_{50};

		sf::Time        lastUpdate_;
		sf::CircleShape circleShape_;

		std::string name_;

	protected:
		virtual void update() = 0;

		void execute();
		void move();
		void calculateLine();

	public:
		Agent();

		void run();
		void stop();
		void setOrder(Envelope const& envelope);
		void clearOrder();

		bool isAvailable() const;
		virtual std::string const& getName() const;
		sf::Shape *getShape() override;
	};
}

