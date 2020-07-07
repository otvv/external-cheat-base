//
// FGUI - feature rich graphical user interface
//

// library includes
#include "button.hpp"

namespace FGUI
{

  CButton::CButton()
  {
    m_strTitle = "Button";
    m_dmSize = { 100, 20 };
    m_anyFont = 0;
    m_fnctCallback = nullptr;
    m_nType = static_cast<int>(WIDGET_TYPE::BUTTON);
    m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE);
  }

  void CButton::AddCallback(std::function<void()> callback)
  {
    m_fnctCallback = callback;
  }

  void CButton::Geometry()
  {
    FGUI::AREA arWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight };

    FGUI::DIMENSION dmTitleTextSize = FGUI::RENDER.GetTextSize(m_anyFont, m_strTitle);

    // button body
    if (FGUI::INPUT.IsCursorInArea(arWidgetRegion))
    {
      FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, arWidgetRegion.m_iRight, arWidgetRegion.m_iBottom, { 50, 50, 50 });
    }
    else
    {
      FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, arWidgetRegion.m_iRight, arWidgetRegion.m_iBottom, { 35, 90, 120 });
    }

    // button label  
    FGUI::RENDER.Text(arWidgetRegion.m_iLeft + (arWidgetRegion.m_iRight / 2) - (dmTitleTextSize.m_iWidth / 2),
      arWidgetRegion.m_iTop + (arWidgetRegion.m_iBottom / 2) - (dmTitleTextSize.m_iHeight / 2), m_anyFont, { 245, 245, 245 }, m_strTitle);
  }

  void CButton::Update()
  {
  }

  void CButton::Input()
  {
    FGUI::AREA arWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight };

    if (FGUI::INPUT.IsCursorInArea(arWidgetRegion))
    {
      if (m_fnctCallback)
      {
        // call function
        m_fnctCallback();
      }
    }
  }

} // namespace FGUI