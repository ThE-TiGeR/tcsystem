//*******************************************************************************
//
// *******   ***   ***               *
//    *     *     *                  *
//    *    *      *                *****
//    *    *       ***  *   *   **   *    **    ***
//    *    *          *  * *   *     *   ****  * * *
//    *     *         *   *      *   * * *     * * *
//    *      ***   ***    *     **   **   **   *   *
//                        *
//*******************************************************************************
// see http://sourceforge.net/projects/tcsystem/ for details.
// Copyright (C) 2003 - 2010 Thomas Goessler. All Rights Reserved. 
//*******************************************************************************
//
// TCSystem is the legal property of its developers.
// Please refer to the COPYRIGHT file distributed with this source distribution.
// 
// This library is free software; you can redistribute it and/or             
// modify it under the terms of the GNU Lesser General Public                
// License as published by the Free Software Foundation; either              
// version 2.1 of the License, or (at your option) any later version.        
//                                                                           
// This library is distributed in the hope that it will be useful,           
// but WITHOUT ANY WARRANTY; without even the implied warranty of            
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         
// Lesser General Public License for more details.                           
//                                                                           
// You should have received a copy of the GNU Lesser General Public          
// License along with this library; if not, write to the Free Software       
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA.
//*******************************************************************************
//  $Id$
//*******************************************************************************

#ifndef _TC_OPENGL_TYPES_H_
#define _TC_OPENGL_TYPES_H_

#include "TCMathBox.h"
#include "TCMathCoord3D.h"
#include "TCMathCoord2D.h"
#include "TCOpenGLColor.h"

#include <vector>

namespace TC
{
   namespace OpenGL
   {
      typedef Math::Coord3D<float>   Vertex3D;
      typedef std::vector<Vertex3D>  Vertex3DVector;
      typedef Math::Box< Vertex3D >  BoundingBox3D;

      typedef Math::Coord2D<float>   Vertex2D;
      typedef std::vector<Vertex2D>  Vertex2DVector;
      typedef Math::Box< Vertex2D >  BoundingBox2D;

      typedef Vertex3D   Normal3D;
      typedef std::vector<Vertex3D>  Normal3DVector;

      typedef Math::Coord2D<float>           TextureCoordinate;
      typedef std::vector<TextureCoordinate> TextureCoordinateVector;

      enum Sizes
      {
         VERTEX3D_SIZE = sizeof(Vertex3D),
         NORMAL3D_SIZE = sizeof(Normal3D),
         COLOR_SIZE    = sizeof(Color),
         TEXTURE_COORDINATE_SIZE = sizeof(TextureCoordinate)
      };
   }
}

#endif // _TC_OPENGL_OBJECT_H_
