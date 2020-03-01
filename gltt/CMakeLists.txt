cmake_minimum_required(VERSION 3.2.2)
project(gltt)

find_package (GLUT REQUIRED)
find_package (OpenGL REQUIRED)


include_directories( ${OPENGL_INCLUDE_DIR}  
                     ${GLUT_INCLUDE_DIR}
                     ${CMAKE_SOURCE_DIR}
                    )

add_library( gltt
             FTBitmapFont.C
             FTEngine.C
             FTFace.C
             FTFont.C
             FTGlyphBitmap.C
             FTGlyph.C
             FTGlyphPixmap.C
             FTGlyphVectorizer.C
             FTInstance.C
             FTPixmapFont.C
             GLTTBitmapFont.C
             GLTTFont.C
             GLTTGlyphPolygonizer.C
             GLTTGlyphPolygonizerHandler.C
             GLTTGlyphTriangulator.C
             GLTTOutlineFont.C
             GLTTPixmapFont.C
             )

target_link_libraries( gltt
                        freetype
                        ${OPENGL_LIBRARIES} 
                        ${GLUT_LIBRARY} 
                        )

install(TARGETS gltt
          LIBRARY DESTINATION lib
          ARCHIVE DESTINATION lib)
