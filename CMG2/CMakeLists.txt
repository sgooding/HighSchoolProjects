cmake_minimum_required(VERSION 3.2.2)
project(CMG2)

find_package (GLUT REQUIRED)
find_package (OpenGL REQUIRED)


include_directories("${CMAKE_SOURCE_DIR}/CMG2/src"
                    "${CMAKE_SOURCE_DIR}/CMG2/include"
                    "${CMAKE_SOURCE_DIR}"
                    ${OPENGL_INCLUDE_DIR}  
                    ${GLUT_INCLUDE_DIR}
                    "${GLUT_INCLUDE_DIR}/GL"
                    )

add_library(CMG2
             src/Color.cpp
             src/DaemonCommand.cpp
             src/Daemon.cpp
             src/DaemonImp.cpp
             src/Debugging.cpp
             src/EditableImage.cpp
             src/Font.cpp
             src/Globals.cpp
             src/GLUTImp.cpp
             src/Image.cpp
             src/KeyboardEvent.cpp
             src/KeyModifiers.cpp
             src/MouseEvent.cpp
             src/NamedKey.cpp
             src/PortMutex.cpp
             src/Style.cpp
             src/TimerEvent.cpp
             src/Transform.cpp
             src/Window.cpp
             src/WindowManager.cpp
             )

target_link_libraries(CMG2 
                        gltt
                        ${OPENGL_LIBRARIES} 
                        ${GLUT_LIBRARY} 
                        jpeg
                        )

install(TARGETS CMG2
          LIBRARY DESTINATION lib
          ARCHIVE DESTINATION lib)
