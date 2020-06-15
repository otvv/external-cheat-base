//
// external base 
// project started - 03/01/2019
//

#pragma once

#define FGUI_IMPLEMENTATION
#include "FGUI/FGUI.hpp"

namespace WIDGETS
{
  inline std::unordered_map<std::string, std::shared_ptr<FGUI::CButton>> Button;
  inline std::unordered_map<std::string, std::shared_ptr<FGUI::CCheckBox>> CheckBox;
  inline std::unordered_map<std::string, std::shared_ptr<FGUI::CColorList>> ColorList;
  inline std::unordered_map<std::string, std::shared_ptr<FGUI::CColorPicker>> ColorPicker;
  inline std::unordered_map<std::string, std::shared_ptr<FGUI::CForm>> Form;
  inline std::unordered_map<std::string, std::shared_ptr<FGUI::CGroupBox>> GroupBox;
  inline std::unordered_map<std::string, std::shared_ptr<FGUI::CKeyBinder>> KeyBinder;
  inline std::unordered_map<std::string, std::shared_ptr<FGUI::CLabel>> Label;
  inline std::unordered_map<std::string, std::shared_ptr<FGUI::CListBox>> ListBox;
  inline std::unordered_map<std::string, std::shared_ptr<FGUI::CMultiBox>> MultiBox;
  inline std::unordered_map<std::string, std::shared_ptr<FGUI::CSlider>> Slider;
  inline std::unordered_map<std::string, std::shared_ptr<FGUI::CTabs>> Tab;
  inline std::unordered_map<std::string, std::shared_ptr<FGUI::CTextBox>> TextBox;
} // namespace WIDGETS

namespace WINDOW
{
  inline void OnSetupDevice()
  {
    // builder pattern 
    static FGUI::CBuilder Builder;

    // initialize form
    WIDGETS::Form["#form1"] = std::make_shared<FGUI::CForm>();
    Builder.Widget(WIDGETS::Form["#form1"]).Title("Form 1").Position(200, 200).Size(735, 435).Key(VK_HOME).Font("Tahoma", 12, true, 128);
    {
      WIDGETS::Tab["#tab1"] = std::make_shared<FGUI::CTabs>();
      Builder.Widget(WIDGETS::Tab["#tab1"]).Title("Tab 1").Font("Tahoma", 12, true, 128).Spawn(WIDGETS::Form["#form1"]);
      {
        WIDGETS::GroupBox["#groupbox1"] = std::make_shared<FGUI::CGroupBox>();
        Builder.Widget(WIDGETS::GroupBox["#groupbox1"]).Title("Groupbox 1").Font("Tahoma", 12, true).Scrollbar(true).Position(15, 15).Size(235, 315).Spawn(WIDGETS::Tab["#tab1"]);
        {
          for (std::size_t i = 0; i < 30; i++)
          {
            WIDGETS::CheckBox["#checkbox" + std::to_string(i + 1)] = std::make_shared<FGUI::CCheckBox>();
            Builder.Widget(WIDGETS::CheckBox["#checkbox" + std::to_string(i + 1)]).Title("Checkbox" + std::to_string(i + 1)).Font("Tahoma", 13).Position(15, 15 + (i * 25)).Spawn(WIDGETS::GroupBox["#groupbox1"], WIDGETS::Tab["#tab1"]);
          }
        }

        WIDGETS::GroupBox["#groupbox2"] = std::make_shared<FGUI::CGroupBox>();
        Builder.Widget(WIDGETS::GroupBox["#groupbox2"]).Title("Groupbox 2").Font("Tahoma", 12, true).Position(30 + 235, 15).Size(235, 315).Spawn(WIDGETS::Tab["#tab1"]);
        {
          WIDGETS::ColorPicker["#colorpicker1"] = std::make_shared<FGUI::CColorPicker>();
          Builder.Widget(WIDGETS::ColorPicker["#colorpicker1"]).Title("ColorPicker 1").Font("Tahoma", 13).Position(15, 15).Color(255, 75, 75).Spawn(WIDGETS::GroupBox["#groupbox2"], WIDGETS::Tab["#tab1"]);

          WIDGETS::KeyBinder["#keybinder1"] = std::make_shared<FGUI::CKeyBinder>();
          Builder.Widget(WIDGETS::KeyBinder["#keybinder1"]).Title("KeyBinder 1").Font("Tahoma", 13).Position(15, 15 + 25).Spawn(WIDGETS::GroupBox["#groupbox2"], WIDGETS::Tab["#tab1"]);
        }
      }

      WIDGETS::Tab["#tab2"] = std::make_shared<FGUI::CTabs>();
      Builder.Widget(WIDGETS::Tab["#tab2"]).Title("Tab 2").Font("Tahoma", 12, true, 128).Spawn(WIDGETS::Form["#form1"]);
      {
        WIDGETS::ColorList["#colorlist1"] = std::make_shared<FGUI::CColorList>();
        Builder.Widget(WIDGETS::ColorList["#colorlist1"]).Title("Colors").Font("Tahoma", 13).Position(15, 15).Size(705, 315)
          .Color("Color 1", 255, 75, 75)
          .Color("Color 2", 25, 100, 255).Spawn(WIDGETS::Tab["#tab2"]);
      }
    }
  }
} // namespace WINDOW