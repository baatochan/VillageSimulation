//
// Created by black on 24.05.18.
//
#pragma once

#include <thread>
#include <iostream>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/String.hpp>
#include "WindowStorage.hpp"
#include "WindowHandler.hpp"

namespace MainScreenManager
{
	/**
	 * @brief
	 * Handles screen creation and live time, does not control sf::Window itself
	 *
	 * @details
	 * Singleton, which should never be called more than once. This class, does
	 * not handle objects managed by WindowHandler class, it just create window,
	 * and pass args to thread.
	 *
	 * @details
	 * To control window contents, you should use WindowStorage class.
	 */
	class ScreenManager
	{
		static std::thread screenManagerThread_;
		static std::unique_ptr<WindowHandler> instance_;
	public:
		static void initialise(
				sf::VideoMode const& videoMode
				, sf::String const& title
				, unsigned const& style
				, std::shared_ptr<WindowStorage> windowStorage = nullptr
		);
		static void start();
		static void stop();
		static State const& getAppStatus();

		static void cleanUp();
	};
}

namespace msm = MainScreenManager;
