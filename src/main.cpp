#include <iostream>
#include "ScreenManager.hpp"

int main(int argc, char const *argv[])
{
	msm::ScreenManager::initialise(sf::VideoMode(600,400),{"Test"}, sf::Style::Default);
}