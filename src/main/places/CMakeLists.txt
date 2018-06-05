target_sources(SO2_Project
        PUBLIC main/places/include/FeedingTrough.hpp
        PUBLIC main/places/FeedingTrough.cpp
        PUBLIC main/places/include/Well.hpp
        PUBLIC main/places/Well.cpp
        PUBLIC main/places/include/Mill.hpp
        PUBLIC main/places/Mill.cpp
        PUBLIC main/places/include/Farm.hpp
        PUBLIC main/places/Farm.cpp
        PUBLIC main/places/include/Bakery
        )
include_directories(main/places/include)
