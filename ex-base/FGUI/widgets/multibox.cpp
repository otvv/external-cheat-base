//
// FGUI - feature rich graphical user interface
//

// library includes
#include "multibox.hpp"
#include "container.hpp"

namespace FGUI
{
  CMultiBox::CMultiBox()
  {
    m_strTitle = "MultiBox";
    m_anyFont = 0;
    m_dmSize = { 150, 20 };
    m_dmBackupSize = { m_dmSize };
    m_iEntrySpacing = 20;
    m_ullSelectedEntry = 0;
    m_prgpEntries = {};
    m_bIsOpened = false;
    m_nType = static_cast<int>(WIDGET_TYPE::MULTIBOX);
    m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE) | static_cast<int>(WIDGET_FLAG::FOCUSABLE) | static_cast<int>(WIDGET_FLAG::SAVABLE);
  }

  void CMultiBox::SetState(bool onoff)
  {
    m_bIsOpened = onoff;
  }

  bool CMultiBox::GetState()
  {
    return m_bIsOpened;
  }

  void CMultiBox::SetIndex(std::size_t index)
  {
    m_ullSelectedEntry = index;
  }

  std::size_t CMultiBox::GetIndex()
  {
    return m_ullSelectedEntry;
  }

  void CMultiBox::SetValue(std::size_t index, unsigned int value)
  {
    m_prgpEntries.second[index] = value;
  }

  std::size_t CMultiBox::GetValue(std::size_t index)
  {
    return m_prgpEntries.second[index];
  }

  std::pair<std::vector<std::string>, std::vector<bool>> CMultiBox::GetMultiEntryInfo()
  {
    return m_prgpEntries;
  }

  void CMultiBox::AddEntry(std::string name, bool value)
  {
    m_prgpEntries.first.emplace_back(name);
    m_prgpEntries.second.emplace_back(value);
  }

  void CMultiBox::Geometry()
  {
    FGUI::AREA arWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmBackupSize.m_iHeight };

    FGUI::DIMENSION dmTitleTextSize = FGUI::RENDER.GetTextSize(m_anyFont, m_strTitle);

    // multibox body
    if (FGUI::INPUT.IsCursorInArea(arWidgetRegion) || m_bIsOpened)
    {
      FGUI::RENDER.Outline(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, arWidgetRegion.m_iRight, arWidgetRegion.m_iBottom, { 195, 195, 195 });
      FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + 1), (arWidgetRegion.m_iTop + 1), (arWidgetRegion.m_iRight - 2), (arWidgetRegion.m_iBottom - 2), { 255, 255, 235 });
    }
    else
    {
      FGUI::RENDER.Outline(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, arWidgetRegion.m_iRight, arWidgetRegion.m_iBottom, { 220, 220, 220 });
      FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + 1), (arWidgetRegion.m_iTop + 1), (arWidgetRegion.m_iRight - 2), (arWidgetRegion.m_iBottom - 2), { 255, 255, 255 });
    }

    // multibox label
    FGUI::RENDER.Text((arWidgetRegion.m_iLeft + 10), arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - (dmTitleTextSize.m_iHeight / 2), m_anyFont, { 35, 35, 35 }, m_strTitle + ":");

    // string format
    std::string strMultiString = { };

    for (std::size_t i = 0; i < m_prgpEntries.first.size(); ++i)
    {
      // switches
      bool bHasReachedLength = strMultiString.length() > 15;
      bool bIsFirstItem = strMultiString.length() == 0;

      if (m_prgpEntries.second[i] && !bHasReachedLength)
      {
        if (!m_prgpEntries.first[i].empty())
        {
          if (!bIsFirstItem)
          {
            strMultiString.append(", ");
          }

          strMultiString.append(m_prgpEntries.first[i]);
        }
      }
      else if (bHasReachedLength && !bIsFirstItem)
      {
        strMultiString.append(" ...");

        break;
      }
    }

    if (strMultiString.length() == 0)
    {
      strMultiString.assign("None");
    }

    // draw current selected entry
    FGUI::RENDER.Text(arWidgetRegion.m_iLeft + (dmTitleTextSize.m_iWidth + 20), arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - (dmTitleTextSize.m_iHeight / 2), m_anyFont, { 35, 35, 35 }, strMultiString);

    if (m_bIsOpened)
    {
      // dropdown list body
      FGUI::RENDER.Outline(arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + 21), arWidgetRegion.m_iRight, (m_prgpEntries.first.size() * m_iEntrySpacing), { 121, 180, 209 });
      FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + 1), (arWidgetRegion.m_iTop + 21) + 1, (arWidgetRegion.m_iRight - 2), (m_prgpEntries.first.size() * m_iEntrySpacing) - 2, { 255, 255, 255 });

      for (std::size_t i = 0; i < m_prgpEntries.first.size(); i++)
      {
        FGUI::AREA arEntryRegion = { arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + 21) + (static_cast<int>(i) * m_iEntrySpacing), arWidgetRegion.m_iRight, m_iEntrySpacing };

        // check if the user is hovering/have selected an entry
        if (FGUI::INPUT.IsCursorInArea(arEntryRegion) || m_prgpEntries.second[i])
        {
          FGUI::RENDER.Rectangle(arEntryRegion.m_iLeft + 1, arEntryRegion.m_iTop, arEntryRegion.m_iRight - 2, arEntryRegion.m_iBottom, { 25, 145, 255 });
          FGUI::RENDER.Text(arEntryRegion.m_iLeft + 5, arEntryRegion.m_iTop + 2, m_anyFont, { 255, 255, 255 }, m_prgpEntries.first[i]);
        }
        else
        {
          FGUI::RENDER.Rectangle(arEntryRegion.m_iLeft + 1, (arEntryRegion.m_iTop + arEntryRegion.m_iBottom), arEntryRegion.m_iRight - 1, 1, { 205, 205, 205 });
          FGUI::RENDER.Text(arEntryRegion.m_iLeft + 5, arEntryRegion.m_iTop + 2, m_anyFont, { 35, 35, 35 }, m_prgpEntries.first[i]);
        }
      }
    }

    // multibox dropdown arrow body
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight - 10) - 8, arWidgetRegion.m_iTop + ((arWidgetRegion.m_iBottom / 2) - 3) + 1, 8, 1, { 20, 20, 20 });
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight - 10) - 7, arWidgetRegion.m_iTop + ((arWidgetRegion.m_iBottom / 2) - 3) + 2, 6, 1, { 20, 20, 20 });
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight - 10) - 6, arWidgetRegion.m_iTop + ((arWidgetRegion.m_iBottom / 2) - 3) + 3, 4, 1, { 20, 20, 20 });
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight - 10) - 5, arWidgetRegion.m_iTop + ((arWidgetRegion.m_iBottom / 2) - 3) + 4, 2, 1, { 20, 20, 20 });
  }

  void CMultiBox::Update()
  {
    if (m_bIsOpened)
    {
      FGUI::AREA arOpenedWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight };

      // keep widget focused
      std::reinterpret_pointer_cast<FGUI::CContainer>(GetParentWidget())->SetFocusedWidget(shared_from_this());

      // close dropdown list if the user clicks on something else
      if (!FGUI::INPUT.IsCursorInArea(arOpenedWidgetRegion) && FGUI::INPUT.GetKeyPress(MOUSE_1))
      {
        m_bIsOpened = false;
      }

      m_dmSize.m_iHeight = m_iEntrySpacing + (m_prgpEntries.first.size() * m_iEntrySpacing) + 2;
    }
    else
    {
      // restore widget size
      m_dmSize.m_iHeight = m_dmBackupSize.m_iHeight;
    }
  }

  void CMultiBox::Input()
  {
    FGUI::AREA arWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmBackupSize.m_iHeight };

    // toggle dropdown list on and off
    if (FGUI::INPUT.IsCursorInArea(arWidgetRegion))
    {
      m_bIsOpened = !m_bIsOpened;
    }

    if (m_bIsOpened)
    {
      if (!FGUI::INPUT.IsCursorInArea(arWidgetRegion))
      {
        for (std::size_t i = 0; i < m_prgpEntries.first.size(); i++)
        {
          FGUI::AREA arEntryRegion = { arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + 21) + (static_cast<int>(i) * m_iEntrySpacing), arWidgetRegion.m_iRight, m_iEntrySpacing };

          if (FGUI::INPUT.IsCursorInArea(arEntryRegion))
          {
            // select an entry
            m_prgpEntries.second[i] = !m_prgpEntries.second[i];

            if (m_prgpEntries.second[i])
            {
              // close dropdown list after selecting something
              // NOTE: maybe remove this?
              m_bIsOpened = false;
            }
          } 
        }
      }
    }
  }

} // namespace FGUI