//
// external base 
// project started - 03/01/2019
//

#pragma once

#define FGUI_IMPLEMENTATION
#include "FGUI/FGUI.hpp"

namespace WIDGETS
{
  inline std::shared_ptr<FGUI::CContainer> Container;
  inline std::shared_ptr<FGUI::CTabs> Tabs;
  inline std::shared_ptr<FGUI::CContainer> GroupBox;
} // namespace WIDGETS

namespace WINDOW
{
  inline void OnSetupDevice()
  {
    // builder pattern 
    static FGUI::CBuilder ptrnBuilder;

    WIDGETS::Container = std::make_shared<FGUI::CContainer>();
    ptrnBuilder.Widget(WIDGETS::Container).Title("Container 1").Position(200, 200).Size(735, 435).Key(VK_HOME).Font("Tahoma", 12, true);
    {
      WIDGETS::Tabs = std::make_shared<FGUI::CTabs>();
      ptrnBuilder.Widget(WIDGETS::Tabs).Position(0, 16).Font("Tahoma", 12, true).Tab("Tab 1").Tab("Tab 2").Tab("Tab 3").Tab("Tab 4").Tab("Tab 5").SpawnIn(WIDGETS::Container, false);

      WIDGETS::GroupBox = std::make_shared<FGUI::CContainer>();
      ptrnBuilder.Widget(WIDGETS::GroupBox).Position(15, 55).Size(685, 315).SpawnIn(WIDGETS::Container, false).Medium(WIDGETS::Tabs, 0);

    }
  }

} // namespace WINDOW