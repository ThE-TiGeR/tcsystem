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
// Copyright (C) 2003 - 2012 Thomas Goessler. All Rights Reserved. 
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
//  $Id: TCOpenGLTypes.h,v a33a555a5a40 2012/02/01 22:48:18 Thomas $
//*******************************************************************************

#ifndef _TC_OPENGL_TYPES_H_
#define _TC_OPENGL_TYPES_H_

#include "TCMathBox.h"
#include "TCMathCoordN.h"
#include "TCOpenGLColor.h"

#include <vector>

namespace tc
{
   namespace open_gl
   {
      typedef math::CoordN<float,3>  Vertex3D;
      typedef std::vector<Vertex3D>  Vertex3DVector;
      typedef math::Box< Vertex3D >  BoundingBox3D;

      typedef math::CoordN<float,2>  Vertex2D;
      typedef std::vector<Vertex2D>  Vertex2DVector;
      typedef math::Box< Vertex2D >  BoundingBox2D;

      typedef Vertex3D   Normal3D;
      typedef std::vector<Vertex3D>  Normal3DVector;

      typedef math::CoordN<float,2>          TextureCoordinate;
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
