cmake_minimum_required(VERSION 3.2)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(ConceptsUsage ConceptsUsage.cpp Concepts.h)

set_target_properties(ConceptsUsage PROPERTIES
                                    CXX_STANDARD 14
                                    CXX_STANDARD_REQUIRED ON
                                    COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)