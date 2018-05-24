//
// Created by black on 24.05.18.
//
#pragma once

#include <thread>

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
	public:
		static void initialise();
		static void cleanUp();
		static void start();
		static void stop();
	};
}

namespace msm = MainScreenManager;
