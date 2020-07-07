//
// external base 
// project started - 03/01/2019
//

#pragma once

#define FGUI_IMPLEMENTATION
#include "FGUI/FGUI.hpp"

std::shared_ptr<FGUI::CContainer> Container;
std::shared_ptr<FGUI::CContainer> GroupBox;
std::shared_ptr<FGUI::CContainer> GroupBox2;
std::shared_ptr<FGUI::CTabs> Tabs;
std::shared_ptr<FGUI::CComboBox> ComboBox;
std::shared_ptr<FGUI::CComboBox> ComboBox2;
std::shared_ptr<FGUI::CColorPicker> ColorPicker;
std::shared_ptr<FGUI::CColorPicker> ColorPicker2;
std::shared_ptr<FGUI::CMultiBox> MultiBox;
std::shared_ptr<FGUI::CButton> Button;
std::shared_ptr<FGUI::CColorList> ColorList;

namespace WINDOW
{
  // TODO: multiple container support
  inline void OnSetupDevice()
  {
    FGUI::WIDGET_FONT fontTitle = { "Tahoma", 12, true, 0x0 };
    FGUI::WIDGET_FONT fontDefault = { "Tahoma", 13, false, 0x0 };

    Container = std::make_shared<FGUI::CContainer>();
    Container->SetSize(735, 435);
    Container->SetPosition(200, 200);
    Container->SetFont(fontTitle);
    Container->SetTitle("Container 1");
    Container->SetKey(VK_HOME);

    Tabs = std::make_shared<FGUI::CTabs>();
    Tabs->SetPosition(0, 16);
    Tabs->SetFont(fontTitle);
    Tabs->AddTab("Tab 1");
    Tabs->AddTab("Tab 2");
    Tabs->AddTab("Tab 3");
    Tabs->AddTab("Tab 4");
    Tabs->AddTab("Tab 5");
    Container->AddWidget(Tabs, false);

    ColorList = std::make_shared<FGUI::CColorList>();
    ColorList->SetSize(695, 305);
    ColorList->SetPosition(15, 55);
    ColorList->SetFont(fontDefault);
    ColorList->SetTitle("ColorList 1");
    ColorList->AddColor("Color 1", { 255, 0, 0 }, false);
    ColorList->AddColor("Color 2", { 0, 255, 0 }, false);
    ColorList->AddColor("Color 3", { 0, 0, 255 }, false);
    ColorList->AddColor("Color 4", { 0, 0, 255 }, false);
    ColorList->AddColor("Color 5", { 0, 255, 0 }, false);
    ColorList->AddColor("Color 6", { 255, 0, 0 }, false);
    ColorList->SetMedium(Tabs, 1);
    Container->AddWidget(ColorList, false);

    GroupBox = std::make_shared<FGUI::CContainer>();
    GroupBox->SetSize(280, 305);
    GroupBox->SetPosition(15, 55);
    GroupBox->SetFont(fontTitle);
    GroupBox->SetTitle("GroupBox");
    GroupBox->SetMedium(Tabs, 2);
    Container->AddWidget(GroupBox, false);

    ComboBox = std::make_shared<FGUI::CComboBox>();
    ComboBox->SetPosition(15, 15);
    ComboBox->SetFont(fontDefault);
    ComboBox->SetTitle("ComboBox");
    ComboBox->AddEntry("Entry 1");
    ComboBox->AddEntry("Entry 2");
    ComboBox->AddEntry("Entry 3");
    ComboBox->AddEntry("Entry 4");
    ComboBox->AddEntry("Entry 5");
    GroupBox->AddWidget(ComboBox, false);

    ColorPicker = std::make_shared<FGUI::CColorPicker>();
    ColorPicker->SetPosition(200, 15);
    ColorPicker->SetFont(fontDefault);
    ColorPicker->SetTitle("ColorPicker");
    ColorPicker->SetColor({ 255, 75, 75 });
    GroupBox->AddWidget(ColorPicker, false);

    MultiBox = std::make_shared<FGUI::CMultiBox>();
    MultiBox->SetPosition(15, 15 + 25);
    MultiBox->SetFont(fontDefault);
    MultiBox->SetTitle("MultiBox");
    MultiBox->AddEntry("Entry 1");
    MultiBox->AddEntry("Entry 2");
    MultiBox->AddEntry("Entry 3");
    MultiBox->AddEntry("Entry 4");
    MultiBox->AddEntry("Entry 5");
    GroupBox->AddWidget(MultiBox, true);

    Button = std::make_shared<FGUI::CButton>();
    Button->SetPosition(15, 40 + 25);
    Button->SetFont(fontTitle);
    Button->SetTitle("Button");
    GroupBox->AddWidget(Button, true);

    //
    //

    GroupBox2 = std::make_shared<FGUI::CContainer>();
    GroupBox2->SetSize(280, 305);
    GroupBox2->SetPosition(15, 55);
    GroupBox2->SetFont(fontTitle);
    GroupBox2->SetTitle("GroupBox 2");
    GroupBox2->SetMedium(Tabs, 3);
    Container->AddWidget(GroupBox2, false);

    ComboBox2 = std::make_shared<FGUI::CComboBox>();
    ComboBox2->SetPosition(15, 15);
    ComboBox2->SetFont(fontDefault);
    ComboBox2->SetTitle("ComboBox");
    ComboBox2->AddEntry("Entry 1");
    ComboBox2->AddEntry("Entry 2");
    ComboBox2->AddEntry("Entry 3");
    ComboBox2->AddEntry("Entry 4");
    ComboBox2->AddEntry("Entry 5");
    GroupBox2->AddWidget(ComboBox2, false);

    ColorPicker2 = std::make_shared<FGUI::CColorPicker>();
    ColorPicker2->SetPosition(200, 15);
    ColorPicker2->SetFont(fontDefault);
    ColorPicker2->SetTitle("ColorPicker");
    ColorPicker2->SetColor({ 255, 75, 75 });
    GroupBox2->AddWidget(ColorPicker2, false);
  }

} // namespace WINDOW