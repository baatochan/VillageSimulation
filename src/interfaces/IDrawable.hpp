//
// Created by black on 26.05.18.
//

#pragma once

#include <memory>
#include <SFML/Graphics/Shape.hpp>

namespace ManagedObject
{
	class IDrawable
	{
	public:
		IDrawable() = default;

		virtual ~IDrawable() = default;

		/**
		 * @brief Use this function carefully, as you are working on RAW object!
		 * @return Returns PTR to object.
		 */
		virtual sf::Shape *getShape() = 0;
	};
}

namespace mo = ManagedObject;

