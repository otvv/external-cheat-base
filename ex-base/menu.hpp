//
// external base 
// project started - 03/01/2019
//

#pragma once

#define FGUI_IMPLEMENTATION
#include "FGUI/FGUI.hpp"

namespace Widgets
{
  inline std::shared_ptr<FGUI::CContainer> Container;
  inline std::shared_ptr<FGUI::CContainer> GroupBox;
  inline std::shared_ptr<FGUI::CCheckBox> CheckBox;
  inline std::shared_ptr<FGUI::CComboBox> ComboBox;
  inline std::shared_ptr<FGUI::CButton> Button;
  inline std::shared_ptr<FGUI::CTextBox> TextBox;
  inline std::shared_ptr<FGUI::CItemSelector> ItemSelector;
  inline std::shared_ptr<FGUI::CColorPicker> ColorPicker;
  inline std::shared_ptr<FGUI::CTabPanel> TabPanel;
  inline std::shared_ptr<FGUI::CLabel> Label;
  inline std::shared_ptr<FGUI::CSlider> Slider;
  inline std::shared_ptr<FGUI::CSlider> Slider2;
} // namespace Widgets

namespace WINDOW
{
  inline void OnSetupDevice()
  {
    FGUI::CBuilder builder;

    Widgets::Container = std::make_shared<FGUI::CContainer>();
    builder.Widget(Widgets::Container).Title("Container 1").Position(200, 200).Flag(FGUI::WIDGET_FLAG::LIMIT).Size(735, 435).Key(VK_HOME).Font("Tahoma", 12, true);
    {
      Widgets::TabPanel = std::make_shared<FGUI::CTabPanel>();
      builder.Widget(Widgets::TabPanel).Position(0, 16).Font("Tahoma", 12, true).Tabs({ "Tab 1", "Tab 2", "Tab 3", "Tab 4", "Tab 5" }).SpawnIn(Widgets::Container, false);
      {
        Widgets::CheckBox = std::make_shared<FGUI::CCheckBox>();
        builder.Widget(Widgets::CheckBox).Title("CheckBox 1").Position(15, 65).Font("Tahoma", 13).Medium(Widgets::TabPanel, 1).SpawnIn(Widgets::Container, false);

        Widgets::ColorPicker = std::make_shared<FGUI::CColorPicker>();
        builder.Widget(Widgets::ColorPicker).Title("ColorPicker 1").Position(246, 65).Color({ 255, 11, 124 }).Font("Tahoma", 13).Medium(Widgets::TabPanel, 1).SpawnIn(Widgets::Container, false);

        Widgets::ComboBox = std::make_shared<FGUI::CComboBox>();
        builder.Widget(Widgets::ComboBox).Title("ComboBox 1").Position(15, (65 + 25)).Size(250, 25).Entries({ "Entry 1", "Entry 2", "Entry 3", "Entry 4", "Entry 5" }).Font("Tahoma", 13).Medium(Widgets::TabPanel, 1).SpawnIn(Widgets::Container, false);

        Widgets::Button = std::make_shared<FGUI::CButton>();
        builder.Widget(Widgets::Button).Title("Button 1").Position(15, (90 + 25)).Size(250, 20).Font("Tahoma", 12, true).Medium(Widgets::TabPanel, 1).SpawnIn(Widgets::Container, false);

        Widgets::TextBox = std::make_shared<FGUI::CTextBox>();
        builder.Widget(Widgets::TextBox).Title("TextBox 1").Position(15, (115 + 25)).Size(250, 20).Font("Tahoma", 13).Medium(Widgets::TabPanel, 1).SpawnIn(Widgets::Container, false);

        Widgets::Slider = std::make_shared<FGUI::CSlider>();
        builder.Widget(Widgets::Slider).Title("Slider 1").Position(15, (150 + 35)).Size(250, 2).Range(0, 1000).Prefix("(ms)").Font("Tahoma", 13).Medium(Widgets::TabPanel, 1).SpawnIn(Widgets::Container, false);

        Widgets::Slider2 = std::make_shared<FGUI::CSlider>();
        builder.Widget(Widgets::Slider2).Title("Slider 2").Position(15, (185 + 35)).Size(250, 2).Range(0, 255).Font("Tahoma", 13).Medium(Widgets::TabPanel, 1).SpawnIn(Widgets::Container, false);

        Widgets::Label = std::make_shared<FGUI::CLabel>();
        builder.Widget(Widgets::Label).Title("Separator 1").Position(15, 65).Style(FGUI::LABEL_STYLE::LINK).Font("Tahoma", 13).Medium(Widgets::TabPanel, 3).SpawnIn(Widgets::Container, false);

        Widgets::GroupBox = std::make_shared<FGUI::CContainer>();
        builder.Widget(Widgets::GroupBox).Title("GroupBox 1").Position(15, 55).Size(290, 325).Font("Tahoma", 12, true).Medium(Widgets::TabPanel, 2).SpawnIn(Widgets::Container, false);
        {
          Widgets::ItemSelector = std::make_shared<FGUI::CItemSelector>();
          builder.Widget(Widgets::ItemSelector).Title("ItemSelector 1").Position(15, 30).Entries({ "Entry 1", "Entry 2", "Entry 3", "Entry 4", "Entry 5" }).Font("Tahoma", 13).SpawnIn(Widgets::GroupBox);
        }
      }
    }
  }

} // namespace WINDOW