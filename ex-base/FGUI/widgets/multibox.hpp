//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_MULTIBOX_HH
#define FGUI_MULTIBOX_HH

// includes
#include <string>
#include <utility>
#include <vector>

// library includes
#include "widgets.hpp"

namespace FGUI
{
  class CMultiBox : public FGUI::CWidgets
  {
  public:
    CMultiBox();

    // @brief: set the multibox state (toggle dropdown list on/off)
    // @params: bool onoff = dropdown state
    void SetState(bool onoff);

    // @brief: get the multibox state (dropdown list enabled or not)
    bool GetState();

    // @brief: set the multibox selected index
    // @params: std::size_t index = selected index (starting with 0)
    void SetIndex(std::size_t index);

    // @brief: get the multibox selected index (entry)
    std::size_t GetIndex();

    // @brief: sets a custom value to a specific entry on the dropdown
    // @params: std::size_t index = entry index, unsigned int value = custom value
    void SetValue(std::size_t index, unsigned int value);

    // @brief: get the multibox selected entry custom value or state
    // @params: std::size_t index = index of the entry that you want to get the value
    std::size_t GetValue(std::size_t index = 0);

    // @brief: get info about the multibox entries (name, value/state)
    std::pair<std::vector<std::string>, std::vector<bool>> GetMultiEntryInfo();

    // @brief: adds a new entry inside the multibox
    // @params: std::string name = entry title, unsigned int value = entry custom value (use true or false if you are using the 'MULTI' style)
    void AddEntry(std::string name, bool value = false);

    // @brief: populate widget geometry (draw widget)
    void Geometry() override;

    // @brief: handle update operations on the widget
    void Update() override;

    // @brief: handle input inside the widget
    void Input() override;

  private:
    bool m_bIsOpened;
    std::size_t m_uiSelectedEntry;
    int m_iEntrySpacing;
    std::pair<std::vector<std::string>, std::vector<bool>> m_prgpEntries;
    FGUI::DIMENSION m_dmBackupSize;
  };
} // namespace FGUI

#endif // FGUI_MULTIBOX_HH