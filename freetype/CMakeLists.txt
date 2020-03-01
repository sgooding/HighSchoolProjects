cmake_minimum_required(VERSION 3.2.2)
project(freetype)

add_library( freetype
    ttapi.c
    ttcache.c
    ttcalc.c
    ttcmap.c
    ttdebug.c
    ttextend.c
    ttfile.c
    ttgload.c
    ttinterp.c
    ttload.c
    ttmemory.c
    ttmutex.c
    ttobjs.c
    ttraster.c
            )

#target_link_libraries(
#                        ${OPENGL_LIBRARIES} 
#                        ${GLUT_LIBRARY} 
#                        )

install(TARGETS freetype
          LIBRARY DESTINATION lib
          ARCHIVE DESTINATION lib)
