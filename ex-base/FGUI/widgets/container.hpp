//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_CONTAINER_HH
#define FGUI_CONTAINER_HH

// includes
#include <vector>

// library includes
#include "widgets.hpp"

namespace FGUI
{
  class CContainer : public FGUI::CWidgets
  {
  public:
    CContainer();

    // @brief: handle container rendering
    void Render();

    // @brief: toggles on or off the container
    // @params: bool state = container state (on/off)
    void SetState(bool state);

    // @brief: gets the state of the container
    bool GetState();

    // @brief: enables/disables groupbox scrollbar
    // @params: bool state = scrollbar state (on/off)
    void SetScrollBarState(bool state);

    // @brief: gets the state of the scrollbar (if it's enabled or not)
    bool GetScrollBarState();

    // @brief: get the widget scroll offset (amount of sorts)
    int GetScrollOffset();

    // @brief: focus on a widget
    // @params: std::shared_ptr<FGUI::CWidgets> widget = widget to focus
    void SetFocusedWidget(std::shared_ptr<FGUI::CWidgets> widget);

    // @brief: returns the widget being focused
    std::shared_ptr<FGUI::CWidgets> GetFocusedWidget();

    // @brief: adds a function callback for the container (it will call the function when the container is visible)
    // @params: std::function<void()> callback = function instance
    void AddCallback(std::function<void()> callback);

    // @brief: save widget state into a file (config)
    // @params: std::string file = config name/location
    void SaveState(std::string file_name);

    // @brief: load widget state from a file (config)
    // @params: std::string file_name = config name/location
    void LoadState(std::string file_name);

    // @brief: sets a custom key to toggle on/off the container, this only works for the main container (window)
    // @params: unsigned int key = toggle key
    void SetKey(unsigned int key);

    // @brief: get the current toggle key of the container
    unsigned int GetKey();

    // @brief: add a new widget inside the groupbox
    // @params: std::shared_ptr<FGUI::CWidgets> widget = widget
    // bool padding = enable/disable padding
    void AddWidget(std::shared_ptr<FGUI::CWidgets> widget, bool padding);

    // @brief: populate widget geometry (draw widget)
    void Geometry() override;

    // @brief: handle update operations on the widget
    void Update() override;

    // @brief: handle input inside the widget
    void Input() override;

  private:
    bool m_bIsOpened;
    bool m_bScrollBarState;
    unsigned int m_uiKey;
    std::shared_ptr<FGUI::CWidgets> m_pFocusedWidget;
    bool m_bIsFocusingOnWidget;
    int m_iWidgetScrollOffset;
    std::vector<std::shared_ptr<FGUI::CWidgets>> m_prgpWidgets;
    std::function<void()> m_fnctCallback;
  };

} // namespace FGUI

#endif // FGUI_CONTAINER_HH