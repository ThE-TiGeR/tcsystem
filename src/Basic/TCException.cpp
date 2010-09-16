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

#include "TCException.h"

#include "TCNewEnable.h"

namespace TC
{

#ifndef TCOS_WINDOWS
   Exception::Exception() :m_what()
   {
   }

   Exception::Exception(const char* what) :m_what(what)
   {
   }

   Exception::Exception(const std::string& what) :m_what(what)
   {
   }

   const char* Exception::what() const throw()
   {
      return m_what.c_str();
   }
#else
   Exception::Exception()
   {
   }

    Exception::Exception(const char* what)
       :std::exception(what)
   {
   }

   Exception::Exception(const std::string& what)
       :std::exception(what.c_str())
   {
   }
#endif

   Exception::~Exception() throw()
   {
   }
}
