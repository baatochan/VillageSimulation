#include <iostream>
#include <Timer.hpp>
#include "MainController.hpp"

#include "spdlog/spdlog.h"

sf::Clock Timer::clock_;

int main(int argc, char const *argv[])
{
	MainController mainController;
	mainController.init();

	return EXIT_SUCCESS;
}
