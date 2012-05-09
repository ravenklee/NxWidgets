/****************************************************************************
 * NxWidgets/nxwm/include/capplicationwindow.hxx
 *
 *   Copyright (C) 2012 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX, NxWidgets, nor the names of its contributors
 *    me be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#ifndef __INCLUDE_CAPPLICATIONWINDOW_NXX
#define __INCLUDE_CAPPLICATIONWINDOW_NXX

/****************************************************************************
 * Included Files
 ****************************************************************************/
 
#include <nuttx/config.h>

#include "cnxtkwindow.hxx"
#include "cnxtoolbar.hxx"
#include "cwidgeteventargs.hxx"
#include "cwidgeteventhandler.hxx"
#include "cimage.hxx"
#include "clabel.hxx"
#include "crlepalettebitmap.hxx"
#include "cwindoweventhandler.hxx"

#include "iapplicationwindow.hxx"

/****************************************************************************
 * Pre-Processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Implementation Classes
 ****************************************************************************/

#if defined(__cplusplus)

namespace NxWM
{
  /**
   * This class represents that application window.  This class contains that the
   * framed window and its toolbar.  It manages callbacks from the toolbar minimize
   * and close buttions and passes these to the application via callbacks.
   */

  class CApplicationWindow : public IApplicationWindow,
                             private NXWidgets::CWidgetEventHandler,
                             private NXWidgets::CWindowEventHandler
  {
  protected:
    NXWidgets::CNxTkWindow       *m_window;         /**< The framed window used by the application */
    NXWidgets::CNxToolbar        *m_toolbar;        /**< The toolbar */
    NXWidgets::CImage            *m_minimizeImage;  /**< The minimize icon */
    NXWidgets::CImage            *m_stopImage;      /**< The close icon */
    NXWidgets::CLabel            *m_windowLabel;    /**< The window title */
    NXWidgets::CRlePaletteBitmap *m_minimizeBitmap; /**< The minimize icon bitmap */
    NXWidgets::CRlePaletteBitmap *m_stopBitmap;     /**< The stop icon bitmap */
    NXWidgets::CNxFont           *m_windowFont;     /**< The font used to rend the window label */
    IApplicationCallback         *m_callback;       /**< Toolbar action callbacks */

    /**
     * Handle an NX window mouse input event.
     *
     * @param e The event data.
     */

#ifdef CONFIG_NX_MOUSE
    void handleMouseEvent(void);
#endif

    /**
     * Handle a NX window keyboard input event.
     */

#ifdef CONFIG_NX_KBD
    void handleKeyboardEvent(void);
#endif

    /**
     * Handle a mouse button click event.
     *
     * @param e The event data.
     */

    void handleClickEvent(const NXWidgets::CWidgetEventArgs &e);

  public:

    /**
     * CApplicationWindow Constructor
     *
     * @param window.  The window to be used by this application.
     */

    CApplicationWindow(NXWidgets::CNxTkWindow *window);

    /**
     * CApplicationWindow Destructor
     */

    ~CApplicationWindow(void);

    /**
     * Initialize window.  Window initialization is separate from
     * object instantiation so that failures can be reported.
     *
     * @return True if the window was successfully initialized.
     */

    bool open(void);

    /**
     * Re-draw the application window
     */

    void redraw(void);

    /**
     * The application window is hidden (either it is minimized or it is
     * maximized, but not at the top of the hierarchy)
     */

    void hide(void);

    /**
     * Recover the contained NXTK window instance
     *
     * @return.  The window used by this application
     */

    NXWidgets::INxWindow *getWindow(void) const;

    /**
     * Set the window label
     *
     * @param appname.  The name of the application to place on the window
     */

    void setWindowLabel(NXWidgets::CNxString &appname);

    /**
     * Register to receive callbacks when toolbar icons are selected
     */

    void registerCallbacks(IApplicationCallback *callback);

    /**
     * Simulate a mouse click on the minimize icon.  This inline method is only
     * used during automated testing of NxWM.
     */

#if defined(CONFIG_NXWM_UNITTEST) && !defined(CONFIG_NXWM_TOUCHSCREEN)
    void clickMinimizeIcon(int index);
#endif

    /**
     * Simulate a mouse click on the stop applicaiton icon.  This inline method is only
     * used during automated testing of NxWM.
     */

#if defined(CONFIG_NXWM_UNITTEST) && !defined(CONFIG_NXWM_TOUCHSCREEN)
    void clickStopIcon(int index);
#endif
  };
}

#endif // __cplusplus

#endif // __INCLUDE_CAPPLICATIONWINDOW_NXX
