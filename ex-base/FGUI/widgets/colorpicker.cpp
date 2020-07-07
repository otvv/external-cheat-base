//
// FGUI - feature rich graphical user interface
//

// library includes
#include "colorpicker.hpp"
#include "container.hpp"

namespace FGUI
{
  CColorPicker::CColorPicker()
  {
    m_strTitle = "ColorPicker";
    m_bIsOpened = false;
    m_dmSize = { 20, 16 };
    m_prRelativePos = { 5.f, 5.f };
    m_clrDefault = { 1, 1, 1 };
    m_anyFont = 0;
    m_nType = static_cast<int>(WIDGET_TYPE::COLORPICKER);
    m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE) | static_cast<int>(WIDGET_FLAG::FOCUSABLE) | static_cast<int>(WIDGET_FLAG::SAVABLE);
  }

  void CColorPicker::SetColor(FGUI::COLOR color)
  {
    m_clrDefault = color;
  }

  FGUI::COLOR CColorPicker::GetColor()
  {
    return m_clrDefault;
  }

  void CColorPicker::Geometry()
  {
    FGUI::AREA arWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight };

    // color picker button body
    FGUI::RENDER.Outline((arWidgetRegion.m_iLeft), (arWidgetRegion.m_iTop + 2), m_dmSize.m_iWidth, (m_dmSize.m_iHeight - 2), { 220, 220, 220 });
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft) + 1, (arWidgetRegion.m_iTop + 3), (m_dmSize.m_iWidth - 2), (m_dmSize.m_iHeight - 4), { 195, 195, 195 });
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft) + 1, (arWidgetRegion.m_iTop + 3), (m_dmSize.m_iWidth - 2), (m_dmSize.m_iHeight - 4), m_clrDefault);

    if (m_bIsOpened)
    {
      static constexpr FGUI::DIMENSION dmColorPickerSize = { 135, 135 };

      FGUI::AREA arColorPickerRegion = { (GetAbsolutePosition().m_iX + 25), GetAbsolutePosition().m_iY, dmColorPickerSize.m_iWidth, dmColorPickerSize.m_iHeight };

      static constexpr int iPixelation = 2; // TODO: make a function for this

      // color picker body
      FGUI::RENDER.Rectangle(arColorPickerRegion.m_iLeft, arColorPickerRegion.m_iTop, arColorPickerRegion.m_iRight, arColorPickerRegion.m_iBottom, { 100, 100, 100 });
      FGUI::RENDER.Outline(arColorPickerRegion.m_iLeft - 1, arColorPickerRegion.m_iTop - 1, (arColorPickerRegion.m_iRight + 3), (arColorPickerRegion.m_iBottom + 3), { 220, 220, 220 });
      FGUI::RENDER.Rectangle(arColorPickerRegion.m_iLeft, arColorPickerRegion.m_iTop, (arColorPickerRegion.m_iRight + 40), arColorPickerRegion.m_iBottom, { 245, 245, 245 });

      for (std::size_t i = 0; i < arColorPickerRegion.m_iBottom; i += iPixelation)
      {
        // color hue
        FGUI::COLOR clrHue = FGUI::COLOR::HSBToRGB((i / 150.f), 1.f, 1.f);

        FGUI::RENDER.Rectangle((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 10, (arColorPickerRegion.m_iTop + i), 10, iPixelation, clrHue);

        // color alpha
        FGUI::COLOR clrAlpha = FGUI::COLOR(m_clrDefault.m_ucRed, m_clrDefault.m_ucGreen, m_clrDefault.m_ucBlue, i / static_cast<float>(arColorPickerRegion.m_iBottom) * 255);

        FGUI::RENDER.Rectangle((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 30, (arColorPickerRegion.m_iTop + i), 10, iPixelation, clrAlpha);

        for (std::size_t j = 0; j < arColorPickerRegion.m_iRight; j += iPixelation)
        {
          // color hsb
          FGUI::COLOR clrHSB = FGUI::COLOR::HSBToRGB(FGUI::COLOR::GetHue(m_clrDefault), j / static_cast<float>(arColorPickerRegion.m_iRight), i / static_cast<float>(arColorPickerRegion.m_iBottom), m_clrDefault.m_ucAlpha);

          FGUI::RENDER.Rectangle((arColorPickerRegion.m_iLeft + j), (arColorPickerRegion.m_iTop + i), iPixelation, iPixelation, clrHSB);
        }
      }

      const int iClampedRelativePosX = std::clamp(static_cast<int>(m_prRelativePos.m_flX), 0, std::max(10, arColorPickerRegion.m_iRight));
      const int iClampedRelativePosY = std::clamp(static_cast<int>(m_prRelativePos.m_flY), 0, std::max(10, arColorPickerRegion.m_iBottom));

      // color hsb body
      FGUI::RENDER.Outline((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 1, (arColorPickerRegion.m_iTop + 1), 1, arColorPickerRegion.m_iBottom + 2, { 220, 220, 220 });
      FGUI::RENDER.Rectangle((arColorPickerRegion.m_iLeft + iClampedRelativePosX) - 6, (arColorPickerRegion.m_iTop + iClampedRelativePosY) - 6, 10, 10, { 35, 35, 35 });

      // hue bar body
      FGUI::RENDER.Outline(((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 10) - 1, arColorPickerRegion.m_iTop - 1, (10 + 2), arColorPickerRegion.m_iBottom + 2, { 220, 220, 220 });
      FGUI::RENDER.Rectangle(((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 5), arColorPickerRegion.m_iTop + (arColorPickerRegion.m_iBottom * FGUI::COLOR::GetHue(m_clrDefault)), 3, 3, { 35, 35, 35 });

      // alpha bar body
      FGUI::RENDER.Outline(((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 30) - 1, arColorPickerRegion.m_iTop - 1, (10 + 2), arColorPickerRegion.m_iBottom + 2, { 220, 220, 220 });
      FGUI::RENDER.Rectangle(((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 25), arColorPickerRegion.m_iTop + (arColorPickerRegion.m_iBottom * (m_clrDefault.m_ucAlpha / 255.f)), 3, 3, { 35, 35, 35 });
    }
  }

  void CColorPicker::Update()
  {
    m_dmSize = { 20, 15 }; // this is required to keep the widget from being padded on groupboxes

    static constexpr FGUI::DIMENSION dmColorPickerSize = { 135, 135 };

    if (m_bIsOpened)
    {
      // keep widget focused
      std::reinterpret_pointer_cast<FGUI::CContainer>(GetParentWidget())->SetFocusedWidget(shared_from_this());

      FGUI::AREA arColorPickerRegion = { (GetAbsolutePosition().m_iX + 25), GetAbsolutePosition().m_iY, dmColorPickerSize.m_iWidth, dmColorPickerSize.m_iHeight };
      FGUI::AREA arColorHSBRegion = { arColorPickerRegion.m_iLeft, arColorPickerRegion.m_iTop, arColorPickerRegion.m_iRight, arColorPickerRegion.m_iBottom };
      FGUI::AREA arColorHueRegion = { (arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 10, arColorPickerRegion.m_iTop, 10, arColorPickerRegion.m_iBottom };
      FGUI::AREA arColorAlphaRegion = { (arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 30, arColorPickerRegion.m_iTop, 10, arColorPickerRegion.m_iBottom };

      // switches
      static bool bColorHSBSelected = false;
      static bool bColorHueSelected = false;
      static bool bColorAlphaSelected = false;

      FGUI::POINT ptCursorPos = FGUI::INPUT.GetCursorPos();

      if (FGUI::INPUT.GetKeyPress(MOUSE_1))
      {
        bColorHSBSelected = FGUI::INPUT.IsCursorInArea(arColorHSBRegion);
        bColorHueSelected = FGUI::INPUT.IsCursorInArea(arColorHueRegion);
        bColorAlphaSelected = FGUI::INPUT.IsCursorInArea(arColorAlphaRegion);
      }
      else if (FGUI::INPUT.GetKeyRelease(MOUSE_1))
      {
        bColorHSBSelected = false;
        bColorHueSelected = false;
        bColorAlphaSelected = false;
      }

      if (bColorHSBSelected)
      {
        m_prRelativePos = { static_cast<float>(ptCursorPos.m_iX) - static_cast<float>(arColorHSBRegion.m_iLeft), static_cast<float>(ptCursorPos.m_iY) - static_cast<float>(arColorHSBRegion.m_iTop) };

        m_clrDefault = FGUI::COLOR::HSBToRGB(FGUI::COLOR::GetHue(m_clrDefault), (m_prRelativePos.m_flX / arColorHSBRegion.m_iRight), (m_prRelativePos.m_flY / arColorHSBRegion.m_iBottom), m_clrDefault.m_ucAlpha);
      }
      else if (bColorHueSelected)
      {
        float flHue = (ptCursorPos.m_iY - arColorHueRegion.m_iTop) / 150.f;

        m_clrDefault = FGUI::COLOR::HSBToRGB(std::clamp(flHue, 0.f, 0.999f), 1.f, 1.f);
      }
      else if (bColorAlphaSelected)
      {
        float flAlpha = (static_cast<float>(ptCursorPos.m_iY - arColorAlphaRegion.m_iTop) / 150.f) * 255.f;

        m_clrDefault.m_ucAlpha = std::clamp(flAlpha, 0.f, 255.f);
      }
    }
  }

  void CColorPicker::Input()
  {
    FGUI::AREA arWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight };

    // toggle colorpicker
    if (FGUI::INPUT.IsCursorInArea(arWidgetRegion))
    {
      m_bIsOpened = !m_bIsOpened;
    }
  }

} // namespace FGUI