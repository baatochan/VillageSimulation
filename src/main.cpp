#include <iostream>
#include "MainController.hpp"
#include "spdlog/spdlog.h"

int main(int argc, char const *argv[])
{
	MainController mainController;
	mainController.init();

	return EXIT_SUCCESS;
}
