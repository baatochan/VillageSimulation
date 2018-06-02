target_sources(SO2_Project
        PUBLIC agents/include/Agent.hpp
        PUBLIC agents/Agent.cpp
        PUBLIC agents/include/Envelope.hpp
        PUBLIC agents/Envelope.cpp
        )

include_directories(agents/include)
