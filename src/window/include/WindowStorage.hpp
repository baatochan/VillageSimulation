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
#include <Agent.hpp>

namespace MainScreenManager
{
	namespace spd = spdlog;

	class WindowStorage
	{
	protected:
		std::mutex placeVectorMutex_;
		std::mutex agentMutex_;

		std::vector<mo::IDrawable*> drawableVector_;
		std::vector<std::weak_ptr<eng::Agent>> agentVector_;
		std::vector<std::weak_ptr<eng::Place>> placeVector_;
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
		void registerNewPlace(std::shared_ptr<eng::Place> const& placePtr);
		void registerNewAgent(std::shared_ptr<eng::Agent> const& agentPtr);
		/**
		 * @return All registered places.
		 */
		std::vector<std::weak_ptr<eng::Place>> const& getPlaces();
	};
}
