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
//  $Id: TCGuiButton.h,v c0056a2f47c7 2012/07/03 21:05:30 thomas $
//*******************************************************************************

#ifndef _TC_GUI_BUTTON_H_
#define _TC_GUI_BUTTON_H_

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
 * @brief A button class
 * Extents the fox button to allow setting multi language string ids 
 * instead of directly setting the text
 */
class TCGUI_API Button: public FX::FXButton, public Widget
{
   TCGUIBASE_DECLARE(Button);

public:
   Button(FX::FXComposite* p, const std::string& text, FX::FXIcon* ic=0, 
               FX::FXObject* tgt=0, FX::FXSelector sel=0, uint32_t opts=FX::BUTTON_NORMAL,
               int32_t x=0,int32_t y=0,int32_t w=0,int32_t h=0,
               int32_t pl=FX::DEFAULT_PAD,int32_t pr=FX::DEFAULT_PAD,
               int32_t pt=FX::DEFAULT_PAD,int32_t pb=FX::DEFAULT_PAD);
   virtual ~Button() {};

protected:
   Button() {};
};

/**
 * @brief A Help button class
 * Adds automatic the help icon, no text is displayed
 */
class TCGUI_API HelpButton: public Button
{
   TCGUIBASE_DECLARE(HelpButton);

public:
   HelpButton(FX::FXComposite* p, 
                   FX::FXObject* tgt=0, FX::FXSelector sel=0, uint32_t opts=0,
                   int32_t x=0,int32_t y=0,int32_t w=26,int32_t h=26,
                   int32_t pl=0,int32_t pr=2,int32_t pt=0,int32_t pb=0);
   
protected:
   HelpButton() {};
};

/**
 * @brief A Apply button class
 * Adds automatic the apply icon and displays the apply text
 */
class TCGUI_API ApplyButton: public Button
{
   TCGUIBASE_DECLARE(ApplyButton);

public:
   ApplyButton(FX::FXComposite* p,
                    FX::FXObject* tgt=0, FX::FXSelector sel=0, uint32_t opts=0,
                    int32_t x=0, int32_t y=0, int32_t w=85, int32_t h=26,
                    int32_t pl=0, int32_t pr=2, int32_t pt=0, int32_t pb=0);

protected:
   ApplyButton() {};
};

/**
 * @brief A Cancel button class
 * Adds automatic the cancel icon and displays the cancel text
 */
class TCGUI_API CancelButton: public Button
{
   TCGUIBASE_DECLARE(CancelButton);

public:
   CancelButton(FX::FXComposite* p,
                     FX::FXObject* tgt=0, FX::FXSelector sel=0, uint32_t opts=0,
                     int32_t x=0, int32_t y=0, int32_t w=85, int32_t h=26,
                     int32_t pl=0, int32_t pr=2, int32_t pt=0, int32_t pb=0);

protected:
   CancelButton() {};
};

/**
 * @brief A Yes button class
 * Adds automatic the yes icon and displays the yes text
 */
class TCGUI_API YesButton: public Button
{
   TCGUIBASE_DECLARE(YesButton);

public:
   YesButton(FX::FXComposite* p,
                  FX::FXObject* tgt=0, FX::FXSelector sel=0, uint32_t opts=0,
                  int32_t x=0, int32_t y=0, int32_t w=85, int32_t h=26,
                  int32_t pl=0, int32_t pr=2, int32_t pt=0, int32_t pb=0);

protected:
   YesButton() {};
};

/**
 * @brief A No button class
 * Adds automatic the no icon and displays the no text
 */
class TCGUI_API NoButton: public Button
{
   TCGUIBASE_DECLARE(NoButton);

public:
   NoButton(FX::FXComposite* p,
                 FX::FXObject* tgt=0, FX::FXSelector sel=0, uint32_t opts=0,
                 int32_t x=0, int32_t y=0, int32_t w=85, int32_t h=26,
                 int32_t pl=0, int32_t pr=2, int32_t pt=0, int32_t pb=0);


protected:
   NoButton() {};
};

/**
 * @brief A Ok button class
 * Adds automatic the ok icon and displays the ok text
 */
class TCGUI_API OkButton: public Button
{
   TCGUIBASE_DECLARE(OkButton);

public:
   OkButton(FX::FXComposite* p,
                 FX::FXObject* tgt=0, FX::FXSelector sel=0, uint32_t opts=0,
                 int32_t x=0, int32_t y=0, int32_t w=85, int32_t h=26,
                 int32_t pl=0, int32_t pr=2, int32_t pt=0, int32_t pb=0);

protected:
   OkButton() {};
};

/**
 * @}
 */

}
}

#endif
