//
// Created by black on 27.05.18.
//

#pragma once


#include <IDrawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>
#include <Agent.hpp>

//class Agent;
namespace Engine
{
	class Agent;
	/**
	 * @brief
	 * 		Base class for any structure in the project.
	 * @details
	 *		You should inherit every structure in the project, from this class.
	 *		It will allow you to make first layer of drawing.
	 */
	class Place : public mo::IDrawable
	{
	protected:
		std::shared_ptr<sf::RectangleShape> drawable_;
	public:
		/**
		 * @brief Initialise new place with known size and map position.
		 * @param size
		 * @param position
		 */
		Place(sf::Vector2f const& size, sf::Vector2f const& position);
		/**
		 * @brief Be worry! You have to allocate shape yourself!
		 */
		Place() = default;

		virtual void execute(Agent const& agent) = 0;
		sf::Shape* getShape() final;
		virtual std::string getName() const;
	};
}

namespace eng = Engine;
