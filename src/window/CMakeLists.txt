target_sources(SO2_Project
        PUBLIC window/include/ScreenManager.hpp
        PUBLIC window/include/WindowStorage.hpp
        PUBLIC window/include/WindowHandler.hpp
        PUBLIC window/WindowHandler.cpp
        PUBLIC window/ScreenManager.cpp
        PUBLIC window/WindowStorage.cpp
        )

include_directories(window/include)
