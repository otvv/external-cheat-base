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
  inline std::unordered_map<std::string, std::shared_ptr<FGUI::CComboBox>> ComboBox;
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

void test()
{
  std::system("notepad");
}

void savetest()
{
   WIDGETS::Form["#form1"]->SaveState("config.xml");
}

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
      Builder.Widget(WIDGETS::Tab["#tab1"]).Title("Aimbot").Font("Tahoma", 12, true, 128).Spawn(WIDGETS::Form["#form1"]);
      {
        WIDGETS::GroupBox["#groupbox1"] = std::make_shared<FGUI::CGroupBox>();
        Builder.Widget(WIDGETS::GroupBox["#groupbox1"]).Title("Groupbox 1").Font("Tahoma", 12, true).Scrollbar(true).Position(15, 15).Size(235, 315).Spawn(WIDGETS::Tab["#tab1"]);
        {
          for (std::size_t i = 0; i < 30; i++)
          {
            WIDGETS::CheckBox["#checkbox" + std::to_string(i + 1)] = std::make_shared<FGUI::CCheckBox>();
            Builder.Widget(WIDGETS::CheckBox["#checkbox" + std::to_string(i + 1)]).Title("Checkbox" + std::to_string(i + 1)).Identificator("vars.checkbox" + std::to_string(i + 1)).Font("Tahoma", 13).Position(15, 15 + (i * 25)).Spawn(WIDGETS::GroupBox["#groupbox1"], WIDGETS::Tab["#tab1"]);
          }
        }

        WIDGETS::GroupBox["#groupbox2"] = std::make_shared<FGUI::CGroupBox>();
        Builder.Widget(WIDGETS::GroupBox["#groupbox2"]).Title("Groupbox 2").Font("Tahoma", 12, true).Position(30 + 235, 15).Size(235, 315).Spawn(WIDGETS::Tab["#tab1"]);
        {
          WIDGETS::ColorPicker["#colorpicker1"] = std::make_shared<FGUI::CColorPicker>();
          Builder.Widget(WIDGETS::ColorPicker["#colorpicker1"]).Identificator("vars.colorpicker1").Font("Tahoma", 13).Position(15, 15).Color(255, 75, 75).Spawn(WIDGETS::GroupBox["#groupbox2"], WIDGETS::Tab["#tab1"]);

          WIDGETS::Label["#label1"] = std::make_shared<FGUI::CLabel>();
          Builder.Widget(WIDGETS::Label["#label1"]).Title("ColorPicker 1").Color(35, 35, 35).Callback(test).Style(static_cast<int>(FGUI::LABEL_STYLE::LINK)).Position(45, 15).Font("Tahoma", 13).Spawn(WIDGETS::GroupBox["#groupbox2"], WIDGETS::Tab["#tab1"]);

          WIDGETS::KeyBinder["#keybinder1"] = std::make_shared<FGUI::CKeyBinder>();
          Builder.Widget(WIDGETS::KeyBinder["#keybinder1"]).Title("KeyBinder 1").Identificator("vars.keybinder1").Font("Tahoma", 13).Position(15, 15 + 25).Spawn(WIDGETS::GroupBox["#groupbox2"], WIDGETS::Tab["#tab1"]);

          WIDGETS::Slider["#slider1"] = std::make_shared<FGUI::CSlider>();
          Builder.Widget(WIDGETS::Slider["#slider1"]).Title("Slider 1").Font("Tahoma", 13).Identificator("vars.slider1").Position(15, 40 + 40).Range(0.f, 100.f).Spawn(WIDGETS::GroupBox["#groupbox2"], WIDGETS::Tab["#tab1"]);

          WIDGETS::MultiBox["#multibox1"] = std::make_shared<FGUI::CMultiBox>();
          Builder.Widget(WIDGETS::MultiBox["#multibox1"]).Title("MultiBox 1").Font("Tahoma", 13).Identificator("vars.multibox1").Position(15, 80 + 15).Entry("Entry 1").Entry("Entry 2").Entry("Entry 3").Entry("Entry 4").Entry("Entry 5").Spawn(WIDGETS::GroupBox["#groupbox2"], WIDGETS::Tab["#tab1"]);
          
          WIDGETS::ComboBox["#combobox1"] = std::make_shared<FGUI::CComboBox>();
          Builder.Widget(WIDGETS::ComboBox["#combobox1"]).Title("ComboBox 1").Font("Tahoma", 13).Identificator("vars.combobox1").Position(15, 105 + 20).Entry("Entry 1").Entry("Entry 2").Entry("Entry 3").Entry("Entry 4").Entry("Entry 5").Spawn(WIDGETS::GroupBox["#groupbox2"], WIDGETS::Tab["#tab1"]);

          WIDGETS::Button["#button1"] = std::make_shared<FGUI::CButton>();
          Builder.Widget(WIDGETS::Button["#button1"]).Title("Button 1").Font("Tahoma", 12, true).Position(15, 125 + 20).Callback(savetest).Spawn(WIDGETS::GroupBox["#groupbox2"], WIDGETS::Tab["#tab1"]);
        }
      }

      WIDGETS::Tab["#tab2"] = std::make_shared<FGUI::CTabs>();
      Builder.Widget(WIDGETS::Tab["#tab2"]).Title("Configs").Font("Tahoma", 12, true, 128).Spawn(WIDGETS::Form["#form1"]);
      {
        WIDGETS::ColorList["#colorlist1"] = std::make_shared<FGUI::CColorList>();
        Builder.Widget(WIDGETS::ColorList["#colorlist1"]).Identificator("vars.colorlist1").Title("ColorList").Font("Tahoma", 13).Position(15, 15).Size(705, 315)
          .Color("Color 1", 255, 75, 75)
          .Color("Color 2", 25, 100, 255).Spawn(WIDGETS::Tab["#tab2"]);
      }
    }
  }
} // namespace WINDOW