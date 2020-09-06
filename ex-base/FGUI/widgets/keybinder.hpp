//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_KEYBINDER_HH
#define FGUI_KEYBINDER_HH

// library includes
#include "widgets.hpp"

namespace FGUI
{

  using INPUT_STATE = enum struct ESInputState_t : int
  {
    ON_CLICK = 0,
    ON_HOLD = 1,
    ON_TOGGLE = 2
  };

  class CKeyBinder : public FGUI::CWidgets
  {
  public:
    CKeyBinder();

    // @brief: set a custom key for the keybinder
    // @args: unsigned int key = custom key code
    void SetKey(unsigned int key_code);

    // @brief: get the current key set on the keybinder
    bool GetKey();

    // @brief: set the keybinder input state (ON_CLICK, ON_HOLD, ON_TOGGLE)
    // @args: FGUI::INPUT_STATE state = key state
    void SetState(FGUI::INPUT_STATE state);

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
    int m_nState;
    unsigned int m_uiKey;
    std::string m_strStatus;
    bool m_bIsGettingKey;
    FGUI::KEY_CODES m_kcCodes;
  };

} // namespace FGUI

#endif // FGUI_KEYBINDER_HH