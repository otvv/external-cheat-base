//
// external base 
// project started - 03/01/2019
//

#pragma once

#include <unordered_map>

#define FGUI_IMPLEMENTATION
#include "FGUI/FGUI.hpp"

namespace WIDGETS
{
 std::shared_ptr<FGUI::CForm> Form;
 std::shared_ptr<FGUI::CTabs> Tab;
 std::shared_ptr<FGUI::CCheckBox> CheckBox;
}

namespace WINDOW
{
	inline void OnSetupDevice()
	{
		// builder pattern 
		FGUI::CBuilder builderPattern;

		WIDGETS::Form = std::make_shared<FGUI::CForm>();
		builderPattern.Widget(WIDGETS::Form).Font("Tahoma", 12, true).Key(VK_HOME).Title("External Form").Size(725, 435).Position(100, 100);
		
		WIDGETS::Tab = std::make_shared<FGUI::CTabs>();
		builderPattern.Widget(WIDGETS::Tab).Font("Tahoma", 12, true).Title("Tab 1").Spawn(WIDGETS::Form);

		WIDGETS::CheckBox = std::make_shared<FGUI::CCheckBox>();
		builderPattern.Widget(WIDGETS::CheckBox).Font("Tahoma", 13).Title("CheckBox").Position(15, 15).Spawn(WIDGETS::Tab);
	}
}