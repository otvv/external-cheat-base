//
// FGUI - feature rich graphical user interface
//

// library includes
#include "tabs.hpp"

namespace FGUI
{

  CTabs::CTabs()
  {
    m_strTitle = "Tabs";
    m_anyFont = 0;
    m_ullSelectedEntry = 0;
    m_dmSize = { 110, 25 };
    m_prgpTabs = {};
    m_strTooltip = "";
    m_nStyle = static_cast<int>(TAB_STYLE::HORIZONTAL);
    m_nType = static_cast<int>(WIDGET_TYPE::TABS);
    m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE);
  }

  void CTabs::AddTab(std::string title)
  {
    m_prgpTabs.emplace_back(title);
  }

  void CTabs::SetIndex(std::size_t index)
  {
    m_ullSelectedEntry = index;
  }

  std::size_t CTabs::GetIndex()
  {
    return m_ullSelectedEntry;
  }

  void CTabs::SetStyle(FGUI::TAB_STYLE style)
  {
    m_nStyle = static_cast<int>(style);
  }

  int CTabs::GetStyle()
  {
    return m_nStyle;
  }

  void CTabs::Geometry()
  {
    // don't proceed if the tab container is empty
    if (m_prgpTabs.empty())
    {
      return;
    }

    FGUI::AREA arWidgetRegion = { 0, 0, 0 };

    for (std::size_t i = 0; i < m_prgpTabs.size(); i++)
    {
      if (m_nStyle == static_cast<int>(TAB_STYLE::HORIZONTAL))
      {
        m_iEntrySpacing = 113;

        arWidgetRegion = { GetAbsolutePosition().m_iX + (static_cast<int>(i) * m_iEntrySpacing), GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight };

        if (m_ullSelectedEntry == i)
        {
          FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop - 5), arWidgetRegion.m_iRight, (arWidgetRegion.m_iBottom + 5), { 45, 45, 45 });
          FGUI::RENDER.Text((arWidgetRegion.m_iLeft + 20), (arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - 5), m_anyFont, { 255, 255, 255 }, m_prgpTabs[i]);
        }
        else
        {
          FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, arWidgetRegion.m_iRight, arWidgetRegion.m_iBottom, { 45, 45, 45 });
          FGUI::RENDER.Text((arWidgetRegion.m_iLeft + 20), (arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - 5), m_anyFont, { 255, 255, 255 }, m_prgpTabs[i]);
        }
      }
      else if (m_nStyle == static_cast<int>(TAB_STYLE::VERTICAL))
      {
        m_iEntrySpacing = 33;

        arWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY + (static_cast<int>(i) * m_iEntrySpacing), m_dmSize.m_iWidth, m_dmSize.m_iHeight };

        if (m_ullSelectedEntry == i)
        {
          FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, (arWidgetRegion.m_iRight + 5), arWidgetRegion.m_iBottom, { 45, 45, 45 });
          FGUI::RENDER.Text((arWidgetRegion.m_iLeft + 20), (arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - 5), m_anyFont, { 255, 255, 255 }, m_prgpTabs[i]);
        }
        else
        {
          FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, arWidgetRegion.m_iRight, arWidgetRegion.m_iBottom, { 45, 45, 45 });
          FGUI::RENDER.Text((arWidgetRegion.m_iLeft + 20), (arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - 5), m_anyFont, { 255, 255, 255 }, m_prgpTabs[i]);
        }
      }
    }
  }

  void CTabs::Update()
  {
    FGUI::AREA arWidgetRegion = { 0, 0, 0 };

    for (std::size_t i = 0; i < m_prgpTabs.size(); i++)
    {
      if (m_nStyle == static_cast<int>(TAB_STYLE::HORIZONTAL))
      {
        m_iEntrySpacing = 113;

        arWidgetRegion = { GetAbsolutePosition().m_iX + (static_cast<int>(i) * m_iEntrySpacing), GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight };
      }
      else if (m_nStyle == static_cast<int>(TAB_STYLE::VERTICAL))
      {
        m_iEntrySpacing = 33;

        arWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY + (static_cast<int>(i) * m_iEntrySpacing), m_dmSize.m_iWidth, m_dmSize.m_iHeight };
      }

      if (FGUI::INPUT.IsCursorInArea(arWidgetRegion))
      {
        if (FGUI::INPUT.IsKeyPressed(MOUSE_1))
        {
          m_ullSelectedEntry = i;
        }
      }
    }
  }

  void CTabs::Input()
  {
  }

  void CTabs::Save(nlohmann::json& module)
  {
    IGNORE_ARG(module);
  }

  void CTabs::Load(nlohmann::json& module)
  {
    IGNORE_ARG(module);
  }

  void CTabs::Tooltip()
  {
  }

} // namespace FGUI