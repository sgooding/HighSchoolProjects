cmake_minimum_required(VERSION 3.2)
project(AP C CXX)

set(INC_FILES
    apmatrix.h
    apqueue.h
    apstack.h
    apstring.h
    apvector.h
    apmatrix.cxx
    apqueue.cxx
    apstack.cxx
    apstring.cxx
    apvector.cxx
    )

#add_library(AP SHARED STATIC ${SOURCE_FILES})

#install(TARGETS AP DESTINATION ${AP_INSTALL_LIB_DIR})
install(FILES ${INC_FILES} DESTINATION ${AP_INSTALL_INCLUDE_DIR})

