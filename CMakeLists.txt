cmake_minimum_required( VERSION 3.2.2 )
project( HighSchoolProjects )

find_package (PkgConfig REQUIRED)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_subdirectory(freetype)
add_subdirectory(gltt)
add_subdirectory(CMG2)

add_subdirectory(draw_test)
add_subdirectory(Projectile)

