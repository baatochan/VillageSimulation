target_sources(SO2_Project
        PUBLIC main/include/MainController.hpp
        PUBLIC main/MainController.cpp
        PUBLIC main/include/Timer.hpp
        )

include_directories(main/include)
include(main/places/CMakeLists.txt)
