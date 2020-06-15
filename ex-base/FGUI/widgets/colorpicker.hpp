//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_COLORPICKER_HH
#define FGUI_COLORPICKER_HH

// library includes
#include "widgets.hpp"

namespace FGUI
{
  class CColorPicker : public FGUI::CWidgets
  {
  public:
    CColorPicker();

    // @brief: sets the default color 
    // @args: FGUI::COLOR color = default color
    void SetColor(FGUI::COLOR color);

    // @brief: returns the current color
    FGUI::COLOR GetColor();

    // @brief: populate widget geometry (draw widget)
    void Geometry() override;

    // @brief: handle update operations on the widget
    void Update() override;

    // @brief: handle input inside the widget
    void Input() override;
  private:
    FGUI::COLOR m_clrDefault;
    bool m_bOpened;
    FGUI::PRECISION m_prRelativePos;
  };

} // namespace FGUI

#endif // FGUI_COLORPICKER_HH