//
// external base 
// project started - 03/01/2019
//

#pragma once

#define FGUI_IMPLEMENTATION
#include "FGUI/FGUI.hpp"

namespace WIDGETS
{
  std::unordered_map<std::string, std::shared_ptr<FGUI::CContainer>> Container;
  std::unordered_map<std::string, std::shared_ptr<FGUI::CTabs>> Tabs;
  std::unordered_map<std::string, std::shared_ptr<FGUI::CCheckBox>> CheckBox;
} // namespace WIDGETS

namespace WINDOW
{
  inline void OnSetupDevice()
  {
    // builder pattern 
    static FGUI::CBuilder ptrnBuilder;

    WIDGETS::Container["$main"] = std::make_shared<FGUI::CContainer>();
    ptrnBuilder.Widget(WIDGETS::Container["$main"]).Title("Container 1").Position(200, 200).Size(735, 435).Key(VK_HOME).Font("Tahoma", 12, true);
    {
      WIDGETS::Tabs["$tabs"] = std::make_shared<FGUI::CTabs>();
      ptrnBuilder.Widget(WIDGETS::Tabs["$tabs"]).Position(0, 16).Font("Tahoma", 12, true).Tab("Tab 1").Tab("Tab 2").Tab("Tab 3").Tab("Tab 4").Tab("Tab 5").SpawnIn(WIDGETS::Container["$main"], false);

      WIDGETS::Container["$panel"] = std::make_shared<FGUI::CContainer>();
      ptrnBuilder.Widget(WIDGETS::Container["$panel"]).Position(0, 41).Size(715, 350).SpawnIn(WIDGETS::Container["$main"], false).Medium(WIDGETS::Tabs["$tabs"], 0);

      WIDGETS::Container["$groupbox"] = std::make_shared<FGUI::CContainer>();
      ptrnBuilder.Widget(WIDGETS::Container["$groupbox"]).Title("GroupBox 1").Font("Tahoma", 12, true).Position(15, 65).Size(230, 275).ScrollBar(true).SpawnIn(WIDGETS::Container["$main"], false).Medium(WIDGETS::Tabs["$tabs"], 0);

      for (std::size_t i = 0; i < 20; i++)
      {
        WIDGETS::CheckBox["$checkbox" + std::to_string(i)] = std::make_shared<FGUI::CCheckBox>();
        ptrnBuilder.Widget(WIDGETS::CheckBox["$checkbox" + std::to_string(i)]).Font("Tahoma", 13).Position(15, 15 + (25 * i)).Title("CheckBox " + std::to_string(i))
          .SpawnIn(WIDGETS::Container["$groupbox"], false).Medium(WIDGETS::Tabs["$tabs"], 0);
      }
    }
  }

} // namespace WINDOW