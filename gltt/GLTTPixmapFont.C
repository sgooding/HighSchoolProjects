/*
 * gltt graphics library
 * Copyright (C) 1998-1999 Stephane Rehel
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "GLTTPixmapFont.h"

#include "FTPixmapFont.h"
#include "FTInstance.h"
#include "FTGlyph.h"
#include "FTGlyphPixmap.h"

#ifdef WIN32
#include <windows.h>
#endif

#ifdef LOCAL_GL_HEADER
  #include "local_gl.h"
#else
  #include <GL/gl.h>
#endif

/////////////////////////////////////////////////////////////////////////////

GLTTPixmapFont::GLTTPixmapFont( FTFace* _face )
{
  face= _face;

  instance= 0;

  pixmaps= 0;
  pixmaps= 0;
}

/////////////////////////////////////////////////////////////////////////////

GLTTPixmapFont::~GLTTPixmapFont()
{
  destroy();

  face= 0;
}

/////////////////////////////////////////////////////////////////////////////

void GLTTPixmapFont::destroy()
{
  delete pixmaps;
  pixmaps= 0;

  delete pixmaps;
  pixmaps= 0;

  delete instance;
  instance= 0;
}

/////////////////////////////////////////////////////////////////////////////

GLTTboolean GLTTPixmapFont::create( int point_size )
{
  destroy();

  if( point_size < 1 )
    point_size= 1;

  instance= new FTInstance(face);

  if( ! instance->create() )
    return GLTT_FALSE;

  if( ! instance->setResolutions(96,96) )
    return GLTT_FALSE;

  if( ! instance->setPointSize(point_size) )
    return GLTT_FALSE;

  pixmaps= new FTPixmapFont(instance);

  if( ! pixmaps->create() )
    return GLTT_FALSE;

  return GLTT_TRUE;
}

/////////////////////////////////////////////////////////////////////////////

void GLTTPixmapFont::output( int x, int y, const char* text )
{
  if( text == 0 || pixmaps == 0 )
    return;

  glRasterPos2i( x, y );

  GLboolean position_valid;
  glGetBooleanv(GL_CURRENT_RASTER_POSITION_VALID, &position_valid);
  if( !position_valid )
    {
    glRasterPos2i(0,0);

    glGetBooleanv(GL_CURRENT_RASTER_POSITION_VALID, &position_valid);
    if( !position_valid )
      return;

    glBitmap(0, 0, 0, 0, x, y, (const GLubyte *)0);
    }

  output(text);
}

/////////////////////////////////////////////////////////////////////////////

void GLTTPixmapFont::output( const char* text )
{
  if( text == 0 || pixmaps == 0 )
    return;

  GLfloat color[4];
  glGetFloatv( GL_CURRENT_COLOR, color );
  unsigned char r= (unsigned char)(color[0] * 255.);
  unsigned char g= (unsigned char)(color[1] * 255.);
  unsigned char b= (unsigned char)(color[2] * 255.);
  unsigned char a= (unsigned char)(color[3] * 255.);

  GLint swapbytes, lsbfirst, rowlength;
  GLint skiprows, skippixels, alignment;

  // Save the current packing mode for bitmaps.
  glGetIntegerv( GL_UNPACK_SWAP_BYTES, &swapbytes );
  glGetIntegerv( GL_UNPACK_LSB_FIRST, &lsbfirst );
  glGetIntegerv( GL_UNPACK_ROW_LENGTH, &rowlength );
  glGetIntegerv( GL_UNPACK_SKIP_ROWS, &skiprows );
  glGetIntegerv( GL_UNPACK_SKIP_PIXELS, &skippixels );
  glGetIntegerv( GL_UNPACK_ALIGNMENT, &alignment );

  // Enforce a standard packing mode
  glPixelStorei( GL_UNPACK_SWAP_BYTES, GL_FALSE );
  glPixelStorei( GL_UNPACK_LSB_FIRST, GL_FALSE );
  glPixelStorei( GL_UNPACK_SKIP_ROWS, 0 );
  glPixelStorei( GL_UNPACK_SKIP_PIXELS, 0 );

  glPushAttrib(GL_ENABLE_BIT);
  glPushAttrib(GL_PIXEL_MODE_BIT);

  glPixelZoom(1.,1.);
  glPixelTransferf( GL_RED_SCALE,   1. );
  glPixelTransferf( GL_GREEN_SCALE, 1. );
  glPixelTransferf( GL_BLUE_SCALE,  1. );
  glPixelTransferf( GL_ALPHA_SCALE, 1. );
  glPixelTransferf( GL_RED_BIAS,    0. );
  glPixelTransferf( GL_GREEN_BIAS,  0. );
  glPixelTransferf( GL_BLUE_BIAS,   0. );
  glPixelTransferf( GL_ALPHA_BIAS,  0. );

//  glPushAttrib(GL_COLOR_BUFFER_BIT); // for glEnable(GL_ALPHA_TEST)
//  glEnable(GL_ALPHA_TEST);
//  glAlphaFunc( GL_GEQUAL, 0.1 );
  glPixelStorei( GL_UNPACK_ALIGNMENT, 4 );

  for(;;)
    {
    int ch= (unsigned char)*text;
    if( ch == 0 )
      break;
    ++text;

    FTGlyphPixmap* gpixmap= pixmaps->getPixmap(ch);
    if( gpixmap == 0 )
      continue;

    unsigned char* data= gpixmap->getPixmap(r,g,b,a);
    glBitmap( 0, 0,
              0.0, 0.0,
              GLfloat(gpixmap->getDeltaX())/64.0,
              GLfloat(gpixmap->getDeltaY())/64.0,
              (const GLubyte *)0 );
    if( data != 0 )
      {
      glPixelStorei( GL_UNPACK_ROW_LENGTH,
                     gpixmap->getPixmapAllocatedWidth() );

      glDrawPixels( gpixmap->getPixmapWidth(),
                    gpixmap->getPixmapHeight(),
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    (const GLvoid*) data );
      }

    glBitmap( 0, 0,
              0.0, 0.0,
              GLfloat(gpixmap->getAdvance()-gpixmap->getDeltaX())/64.0,
              GLfloat(gpixmap->getDeltaY())/-64.0,
              (const GLubyte *)0 );
    }

//  glPopAttrib(); // GL_COLOR_BUFFER_BIT
  glPopAttrib(); // GL_PIXEL_MODE_BIT
  glPopAttrib(); // GL_ENABLE_BIT

  // Restore saved packing modes.
  glPixelStorei( GL_UNPACK_SWAP_BYTES, swapbytes );
  glPixelStorei( GL_UNPACK_LSB_FIRST, lsbfirst );
  glPixelStorei( GL_UNPACK_ROW_LENGTH, rowlength );
  glPixelStorei( GL_UNPACK_SKIP_ROWS, skiprows );
  glPixelStorei( GL_UNPACK_SKIP_PIXELS, skippixels );
  glPixelStorei( GL_UNPACK_ALIGNMENT, alignment );
}

/////////////////////////////////////////////////////////////////////////////

int GLTTPixmapFont::getWidth( const char* text )
{
  if( pixmaps == 0 )
    return 0;

  return pixmaps->getWidth(text);
}

/////////////////////////////////////////////////////////////////////////////

int GLTTPixmapFont::getHeight() const
{
  if( instance == 0 )
    return 0;

  return instance->getHeight();
}

/////////////////////////////////////////////////////////////////////////////

int GLTTPixmapFont::getDescender() const
{
  if( instance == 0 )
    return 0;

  return instance->getDescender();
}

/////////////////////////////////////////////////////////////////////////////
