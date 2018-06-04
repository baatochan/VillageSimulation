//
// Created by black on 24.05.18.
//

#pragma once


#include <vector>
#include <SFML/Graphics/RectangleShape.hpp>
#include <Place.hpp>
#include <mutex>
#include <SFML/Graphics/RenderWindow.hpp>
#include "IDrawable.hpp"
#include <spdlog/spdlog.h>

namespace MainScreenManager
{
	namespace spd = spdlog;

	class WindowStorage
	{
	protected:
		std::mutex placeVectorMutex_;
		std::mutex agentMutex_;

		std::vector<mo::IDrawable*> drawableVector_;
		std::vector<eng::Place*> placeVector_;
	public:
		WindowStorage() = default;
		~WindowStorage() = default;

		/**
		 * @brief draws all stored elements onto the screen
		 * @details
		 * 		It first draws registered places, and then agents positions.
		 * @param targetWindow
		 * 		window which would get force drawn on.
		 */
		void draw(sf::RenderWindow* targetWindow);

		/**
		 * @brief adds new place to known places
		 * @details
		 * 		Locks the mutex for the time of the operation
		 * @param placePtr
		 * 		Element to be added to the vector
		 */
		void registerNewPlace(eng::Place* placePtr);
		void registerNewAgent(eng::Place* placePtr);
		/**
		 * @return All registered places.
		 */
		std::vector<eng::Place*> const& getPlaces();
	};
}
