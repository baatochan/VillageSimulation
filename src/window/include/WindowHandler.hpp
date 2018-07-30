//
// Created by black on 24.05.18.
//

#pragma once
#include <memory>
#include <mutex>

#include "SFML/Graphics.hpp"
#include "WindowStorage.hpp"
#include "State.hpp"

namespace MainScreenManager
{
	/**
	 * @name
	 * 		Handles drawing, and window events.
	 * @details
	 * 		As name suggests this class will attempt to control OpenGL
	 * 		and it's behaviours, for application, so we will not need to worry
	 * 		about it.
	*/
	class WindowHandler
	{
	protected:
		std::mutex windowHandlerMutex_;
		State state=State::STARTING;

		std::unique_ptr<sf::RenderWindow> renderWindow_;
		std::shared_ptr<WindowStorage> windowStoragePtr_;

	public:
		/**
		 * @brief
		 * 		Creates window.
		 * @param videoMode
		 * 		Size, and color depth.
		 * @param title
		 * 		Title showed at the top of the window
		 * @param style
		 * 		Style of the window:
		 * 			- Default: With [o][-][x] buttons
		 * 			- Close: Only [x]
		 * 			- None: none
		 * 			- Fullscreen
		 * 			- Resize
		 * 			- Titlebar
		 * @param windowStoragePtr
		 * 		Storage of items to be drawn on screen.
		 * 		Uses interface of IScreenStorage
		 */
		WindowHandler(sf::VideoMode const& videoMode
				, sf::String const& title
				, uint32_t style
				, std::shared_ptr<WindowStorage> const& windowStoragePtr
		);

		~WindowHandler() = default;

		void Run();
		void Stop();

		State const& getStatus();
	};
}

