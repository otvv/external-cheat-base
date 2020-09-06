//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_CURSOR_HH
#define FGUI_CURSOR_HH

// includes
#include <functional>

// library includes
#include "widgets.hpp"

namespace FGUI
{
  using CURSOR_STYLE = enum struct ESCursorStyle : int {
    NONE = 0,
    ARROW,
    HAND,
    IBEAM,
    PIPETTE,
    MOVE
  };

  class CCursor : public FGUI::CWidgets
  {
  public:
    CCursor();

    // @brief: set the cursor style
    // @args: FGUI::CURSOR_STYLE style = cursor style (type)
    void SetStyle(FGUI::CURSOR_STYLE style);

    // @brief: set the cursor color
    // @args: FGUI::COLOR color = cursor custom color
    void SetColor(FGUI::COLOR color);

    // @brief: populate widget geometry (draw widget)
    // @args: FGUI::WIDGET_STATUS status = widget status (HOVERED, etc)
    void Geometry(FGUI::WIDGET_STATUS status) override;

    // @brief: handle update operations on the widget
    void Update() override;

    // @brief: handle input inside the widget
    void Input() override;

    // @brief: save the widget state
    // @args: nlohmann::json module = json module
    void Save(nlohmann::json& module) override;

    // @brief: load the widget state
    // @args: nlohmann::json module = json module
    void Load(nlohmann::json& module) override;

    // @brief: handle widget tooltips
    void Tooltip() override;

  private:
    FGUI::COLOR m_clrCursor;
    int m_nStyle;
  };
} // namespace FGUI

#endif // FGUI_CURSOR_HH