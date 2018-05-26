add_executable(SO2_Project main.cpp
        window/src/ScreenManager.cpp
        window/include/ScreenManager.hpp
        window/src/WindowHandler.cpp
        window/include/WindowHandler.hpp
        window/src/WindowStorage.cpp
        window/include/WindowStorage.hpp
        )

add_dependencies(SO2_Project GTEST SFML)

include_directories(window/include)

target_link_libraries(SO2_Project
        ${SFML_INSTALL_LOCATION}/lib/libsfml-audio.so
        ${SFML_INSTALL_LOCATION}/lib/libsfml-graphics.so
        ${SFML_INSTALL_LOCATION}/lib/libsfml-window.so
        ${SFML_INSTALL_LOCATION}/lib/libsfml-system.so
        ${SFML_INSTALL_LOCATION}/lib/libsfml-network.so
        pthread)
