target_sources(SO2_Project
        PUBLIC main/include/MainController.hpp
        PUBLIC main/MainController.cpp
        PUBLIC main/include/Timer.hpp
        PUBLIC main/include/Villager.hpp
        PUBLIC main/Villager.cpp
        PUBLIC main/include/God.hpp
        PUBLIC main/God.cpp
        )

include_directories(main/include)
include(main/places/CMakeLists.txt)
