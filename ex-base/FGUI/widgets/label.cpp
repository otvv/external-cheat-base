//
// FGUI - feature rich graphical user interface
//

// library includes
#include "label.hpp"

namespace FGUI
{

  CLabel::CLabel()
  {
    m_strTitle = "Label";
    m_anyFont = 0;
    m_fnctCallback = nullptr;
    m_clrLabel = { 180, 25, 25 };
    m_nStyle = static_cast<int>(LABEL_STYLE::NORMAL);
    m_nType = static_cast<int>(WIDGET_TYPE::LABEL);
    m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE);
  }

  void CLabel::AddCallback(std::function<void()> callback)
  {
    m_fnctCallback = callback;
  }

  void CLabel::SetStyle(FGUI::LABEL_STYLE style)
  {
    m_nStyle = static_cast<int>(style);
  }

  void CLabel::SetColor(FGUI::COLOR color)
  {
    if (m_nStyle == static_cast<int>(LABEL_STYLE::COLORED))
    {
      m_clrLabel = color;
    }
  }

  FGUI::COLOR CLabel::GetColor()
  {
    return m_clrLabel;
  }

  int CLabel::GetStyle()
  {
    return m_nStyle;
  }

  void CLabel::Geometry()
  {
    FGUI::DIMENSION dmTitleTextSize = FGUI::RENDER.GetTextSize(m_anyFont, m_strTitle);

    FGUI::AREA arWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, dmTitleTextSize.m_iWidth, dmTitleTextSize.m_iHeight };

    // label body
    if (m_nStyle == static_cast<int>(LABEL_STYLE::NORMAL))
    {
      FGUI::RENDER.Text(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, m_anyFont, { 35, 35, 35 }, m_strTitle);
    }
    else if (m_nStyle == static_cast<int>(LABEL_STYLE::COLORED))
    {
      FGUI::RENDER.Text(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, m_anyFont, m_clrLabel, m_strTitle);
    }
    else if (m_nStyle == static_cast<int>(LABEL_STYLE::LINK))
    {
      FGUI::RENDER.Text(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, m_anyFont, { 25, 25, 195 }, m_strTitle);
      FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + arWidgetRegion.m_iBottom) + 1, arWidgetRegion.m_iRight, 1, { 25, 25, 195 });
    }
  }

  void CLabel::Update()
  {
    FGUI::DIMENSION dmTitleTextSize = FGUI::RENDER.GetTextSize(m_anyFont, m_strTitle);

    FGUI::AREA arWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, dmTitleTextSize.m_iWidth, dmTitleTextSize.m_iHeight };

    // check if the label is a link
    if (m_nStyle == static_cast<int>(LABEL_STYLE::LINK))
    {
      if (FGUI::INPUT.IsCursorInArea(arWidgetRegion))
      {
        if (FGUI::INPUT.GetKeyPress(MOUSE_1))
        {
          if (m_fnctCallback)
          {
            // call function
            m_fnctCallback();
          }
        }
      }
    }
  }

  void CLabel::Input()
  {
  }

} // namespace FGUI