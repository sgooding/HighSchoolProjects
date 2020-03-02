cmake_minimum_required( VERSION 3.1 )

## Sources and headers
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} 
                     ${CMAKE_SOURCE_DIR}/CMG2 
                     ${CMAKE_SOURCE_DIR}/CMG2/src
                     ${CMAKE_SOURCE_DIR}/AP
                     )

## 1. Compile...
add_executable( Projectile
                main.cpp
                Projectile.cpp
                ImageMap.cpp )

find_package (PkgConfig REQUIRED)

## 2. Link...
target_link_libraries( Projectile 
                       CMG2 )

## 3. Install...
install( TARGETS Projectile
         RUNTIME DESTINATION bin )

