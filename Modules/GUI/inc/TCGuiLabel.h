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
//  $Id: TCGuiLabel.h,v c0056a2f47c7 2012/07/03 21:05:30 thomas $
//*******************************************************************************

#ifndef _TCGUI_LABEL_H_
#define _TCGUI_LABEL_H_

#include "TCGuiWidget.h"

namespace tc
{
namespace gui
{

/**
 * @addtogroup TC_GUI
 * @{
 */

/**
 * @brief A Text display class
 * Extents the fox label to allow setting multi language string ids 
 * instead of directly setting the text
 */
class TCGUI_API Label: public FX::FXLabel, public Widget
{
   TCGUIBASE_DECLARE(Label);

public:
   Label(FX::FXComposite* p, const std::string& text, FX::FXIcon* ic=0,
              uint32_t opts=FX::LABEL_NORMAL,
              int32_t x=0,int32_t y=0,int32_t w=0,int32_t h=0,int32_t pl=FX::DEFAULT_PAD,int32_t pr=FX::DEFAULT_PAD,
              int32_t pt=FX::DEFAULT_PAD,int32_t pb=FX::DEFAULT_PAD);
   Label(FX::FXComposite* p, const std::string& text, FX::FXIcon* ic, FX::FXObject* tgt, FX::FXSelector sel,
              uint32_t opts=FX::LABEL_NORMAL,
              int32_t x=0,int32_t y=0,int32_t w=0,int32_t h=0,int32_t pl=FX::DEFAULT_PAD,int32_t pr=FX::DEFAULT_PAD,
              int32_t pt=FX::DEFAULT_PAD,int32_t pb=FX::DEFAULT_PAD);
   virtual ~Label() {};

protected:
   Label() {};
};

/**
 * @}
 */

}
}

#endif // _TCGUI_LABEL_H_
