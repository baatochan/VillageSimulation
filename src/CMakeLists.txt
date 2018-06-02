add_executable(SO2_Project
        main.cpp
        ../include/State.hpp
        )

add_dependencies(SO2_Project GTEST SFML)

include(main/CMakeLists.txt)
include(core/CMakeLists.txt)
include(interfaces/CMakeLists.txt)
include(window/CMakeLists.txt)
include(agents/CMakeLists.txt)

target_link_libraries(SO2_Project
        ${SFML_INSTALL_LOCATION}/lib/libsfml-audio.so
        ${SFML_INSTALL_LOCATION}/lib/libsfml-graphics.so
        ${SFML_INSTALL_LOCATION}/lib/libsfml-window.so
        ${SFML_INSTALL_LOCATION}/lib/libsfml-system.so
        ${SFML_INSTALL_LOCATION}/lib/libsfml-network.so
        pthread)
