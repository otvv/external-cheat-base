//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_BUTTON_HH
#define FGUI_BUTTON_HH

// includes
#include <functional>

// library includes
#include "widgets.hpp"

namespace FGUI
{

  class CButton : public FGUI::CWidgets
  {
  public:
    CButton();

    // @brief: adds a function callback for the button (it will call the function whenever the user clicks the button)
    // @params: std::function<void()> callback = function instance
    void AddCallback(std::function<void()> callback);

    // @brief: populate widget geometry (draw widget)
    void Geometry() override;

    // @brief: handle update operations on the widget
    void Update() override;

    // @brief: handle input inside the widget
    void Input() override;
  private:
    std::function<void()> m_fnctCallback;
  };

} // namespace FGUI

#endif // FGUI_BUTTON_HH