//
// FGUI - feature rich graphical user interface
//

// library includes
#include "checkbox.hpp"

namespace FGUI
{

  CCheckBox::CCheckBox()
  {
    m_strTitle = "CheckBox";
    m_dmSize = { 16, 16 };
    m_anyFont = 0;
    m_bIsChecked = false;
    m_fnctCallback = nullptr;
    m_nType = static_cast<int>(WIDGET_TYPE::CHECKBOX);
    m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE) | static_cast<int>(WIDGET_FLAG::SAVABLE);
  }

  void CCheckBox::SetState(bool onoff)
  {
    m_bIsChecked = onoff;
  }

  bool CCheckBox::GetState()
  {
    return m_bIsChecked;
  }

  void CCheckBox::AddCallback(std::function<void()> callback)
  {
    m_fnctCallback = callback;
  }

  void CCheckBox::Geometry()
  {
    FGUI::AREA arWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight };

    // checkbox body
    FGUI::RENDER.Outline((arWidgetRegion.m_iLeft - 1), (arWidgetRegion.m_iTop - 1), arWidgetRegion.m_iRight, arWidgetRegion.m_iBottom, { 220, 220, 220 });
    FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, (arWidgetRegion.m_iRight - 2), (arWidgetRegion.m_iBottom - 2), { 255, 255, 255 });

    if (m_bIsChecked)
    {
      if (FGUI::INPUT.IsCursorInArea(arWidgetRegion))
      {
        FGUI::RENDER.Outline((arWidgetRegion.m_iLeft - 1), (arWidgetRegion.m_iTop - 1), arWidgetRegion.m_iRight, arWidgetRegion.m_iBottom, { 180, 25, 25 });
      }

      FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + 3), (arWidgetRegion.m_iTop + 3), (arWidgetRegion.m_iRight - 8), (arWidgetRegion.m_iBottom - 8), { 180, 25, 25 });
    }
    else
    {
      if (FGUI::INPUT.IsCursorInArea(arWidgetRegion))
      {
        FGUI::RENDER.Outline((arWidgetRegion.m_iLeft - 1), (arWidgetRegion.m_iTop - 1), arWidgetRegion.m_iRight, arWidgetRegion.m_iBottom, { 195, 195, 195 });
      }
    }

    // checkbox label
    FGUI::RENDER.Text(arWidgetRegion.m_iLeft + (arWidgetRegion.m_iRight + 5), arWidgetRegion.m_iTop, m_anyFont, { 35, 35, 35 }, m_strTitle);
  }

  void CCheckBox::Update()
  {
    m_dmSize = { 16, 16 }; // this is required to keep the widget from being padded on groupboxes

    if (m_bIsChecked)
    {
      if (m_fnctCallback)
      {
        // call function
        m_fnctCallback();
      }
    }
  }

  void CCheckBox::Input()
  {
    FGUI::AREA arWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight };

    if (FGUI::INPUT.IsCursorInArea(arWidgetRegion))
    {
      m_bIsChecked = !m_bIsChecked;
    }
  }

  void CCheckBox::Save(nlohmann::json& module)
  {
    // remove spaces from widget name
    std::string strFormatedWidgetName = GetTitle();
    std::replace(strFormatedWidgetName.begin(), strFormatedWidgetName.end(), ' ', '_');

    module[strFormatedWidgetName] = m_bIsChecked;
  }

  void CCheckBox::Load(std::string file)
  {
    nlohmann::json jsModule;

    std::ifstream ifsFileToLoad(file, std::ifstream::binary);

    if (ifsFileToLoad.fail())
    {
      return; // TODO: handle this properly
    }

    jsModule = nlohmann::json::parse(ifsFileToLoad);

    // remove spaces from widget name
    std::string strFormatedWidgetName = GetTitle();
    std::replace(strFormatedWidgetName.begin(), strFormatedWidgetName.end(), ' ', '_');

    // change widget state to the one stored on file
    m_bIsChecked = jsModule[strFormatedWidgetName];
  }

} // namespace FGUI