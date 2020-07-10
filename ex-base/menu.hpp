//
// external base 
// project started - 03/01/2019
//

#pragma once

#define FGUI_IMPLEMENTATION
#include "FGUI/FGUI.hpp"

namespace WINDOW
{
  // TODO: multiple container support
  inline void OnSetupDevice()
  {
    FGUI::WIDGET_FONT fontTitle = { "Tahoma", 12, true, 0x0 };
    FGUI::WIDGET_FONT fontDefault = { "Tahoma", 13, false, 0x0 };
  }

} // namespace WINDOW