//
// FGUI - feature rich graphical user interface
//

// library includes
#include "colorpicker.hpp"

namespace FGUI
{
  CColorPicker::CColorPicker()
  {
    m_strTitle = "ColorPicker";
    m_bOpened = false;
    m_dmSize = { 20, 16 };
    m_clrDefault = { 1, 1, 1 };
    m_prRelativePos = { 0.f, 0.f };
    m_ulFont = 0;
    m_nType = static_cast<int>(WIDGET_TYPE::COLORPICKER);
    m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE) | static_cast<int>(WIDGET_FLAG::FOCUSABLE);
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
    // widget's area
    FGUI::AREA arWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight };

    // color picker button body
    FGUI::RENDER.Outline((arWidgetRegion.m_iLeft), (arWidgetRegion.m_iTop + 2), m_dmSize.m_iWidth, (m_dmSize.m_iHeight - 2), { 220, 220, 220 });
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft) + 1, (arWidgetRegion.m_iTop + 3), (m_dmSize.m_iWidth - 2), (m_dmSize.m_iHeight - 4), { 195, 195, 195 });
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft) + 1, (arWidgetRegion.m_iTop + 3), (m_dmSize.m_iWidth - 2), (m_dmSize.m_iHeight - 4), m_clrDefault);

    if (m_bOpened)
    {
      // color picker size
      static constexpr FGUI::DIMENSION dmColorPickerSize = { 135, 135 };

      // color picker's area
      FGUI::AREA arColorPickerRegion = { (GetAbsolutePosition().m_iX + 25), GetAbsolutePosition().m_iY, dmColorPickerSize.m_iWidth, dmColorPickerSize.m_iHeight };

      // color picker's pixelation (ghetto optimization)
      static constexpr int iPixelation = 3; // TODO: make a function for this

      // color picker body
      FGUI::RENDER.Rectangle(arColorPickerRegion.m_iLeft, arColorPickerRegion.m_iTop, arColorPickerRegion.m_iRight, arColorPickerRegion.m_iBottom, { 100, 100, 100 });
      FGUI::RENDER.Outline(arColorPickerRegion.m_iLeft - 1, arColorPickerRegion.m_iTop - 1, (arColorPickerRegion.m_iRight + 2), (arColorPickerRegion.m_iBottom + 2), { 220, 220, 220 });
      FGUI::RENDER.Rectangle(arColorPickerRegion.m_iLeft, arColorPickerRegion.m_iTop, (arColorPickerRegion.m_iRight + 40), arColorPickerRegion.m_iBottom, { 245, 245, 245 });

      for (std::size_t i = 0; i < static_cast<float>(arColorPickerRegion.m_iBottom); i += iPixelation)
      {
        // color hue
        FGUI::COLOR clrHue = FGUI::COLOR::HSBToRGB(i / 150.f, 1.f, 1.f);

        FGUI::RENDER.Rectangle((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 10, (arColorPickerRegion.m_iTop + i), 10, iPixelation, clrHue);

        // color alpha
        FGUI::COLOR clrAlpha = FGUI::COLOR(m_clrDefault.m_ucRed, m_clrDefault.m_ucGreen, m_clrDefault.m_ucBlue, (i / static_cast<float>(arColorPickerRegion.m_iBottom) * 255));

        FGUI::RENDER.Rectangle((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 30, (arColorPickerRegion.m_iTop + i), 10, iPixelation, clrAlpha);

        for (std::size_t j = 0; j < static_cast<float>(arColorPickerRegion.m_iRight); j += iPixelation)
        {
          // color hsb
          FGUI::COLOR clrHSB = FGUI::COLOR::HSBToRGB(FGUI::COLOR::GetHue(m_clrDefault), j / static_cast<float>(arColorPickerRegion.m_iRight), i / static_cast<float>(arColorPickerRegion.m_iBottom), m_clrDefault.m_ucAlpha);

          FGUI::RENDER.Rectangle((arColorPickerRegion.m_iLeft + j), (arColorPickerRegion.m_iTop + i), iPixelation, iPixelation, clrHSB);
        }
      }

      // TODO: move this to another place
      const int clampedRelativePosX = std::clamp(static_cast<int>(m_prRelativePos.m_flX), 5, std::max(5, arColorPickerRegion.m_iRight));
      const int clampedRelativePosY = std::clamp(static_cast<int>(m_prRelativePos.m_flY), 5, std::max(5, arColorPickerRegion.m_iBottom));

      // color hsb body
      FGUI::RENDER.Outline((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) - 1, arColorPickerRegion.m_iTop - 1, 1, arColorPickerRegion.m_iBottom + 2, { 220, 220, 220 });
      FGUI::RENDER.Rectangle((arColorPickerRegion.m_iLeft + clampedRelativePosX) - 5, (arColorPickerRegion.m_iTop + clampedRelativePosY) - 5, 5, 5, { 35, 35, 35 });

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

    if (m_bOpened)
    {
      // color picker size
      static constexpr FGUI::DIMENSION dmColorPickerSize = { 135, 135 };

      // color picker's area
      FGUI::AREA arColorPickerRegion = { (GetAbsolutePosition().m_iX + 25), GetAbsolutePosition().m_iY, dmColorPickerSize.m_iWidth, dmColorPickerSize.m_iHeight };

      // color hsb area
      FGUI::AREA arColorHSBRegion = { arColorPickerRegion.m_iLeft, arColorPickerRegion.m_iTop, arColorPickerRegion.m_iRight, arColorPickerRegion.m_iBottom };

      // color hue area
      FGUI::AREA arColorHueRegion = { (arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 10, arColorPickerRegion.m_iTop, 10, arColorPickerRegion.m_iBottom };

      // color alpha area
      FGUI::AREA arColorAlphaRegion = { (arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 30, arColorPickerRegion.m_iTop, 10, arColorPickerRegion.m_iBottom };

      // switches
      static bool bColorHSBSelected = false;
      static bool bColorHueSelected = false;
      static bool bColorAlphaSelected = false;

      // get cursor position
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

        m_clrDefault = FGUI::COLOR::HSBToRGB(std::clamp(flHue, 0.f, 1.f), 1.f, 1.f);
      }
      else if (bColorAlphaSelected)
      {
        std::uint8_t ucAlpha = (ptCursorPos.m_iY - arColorAlphaRegion.m_iTop) / 150.f * 255;

        m_clrDefault.m_ucAlpha = ucAlpha;
      }

      // keep widget focused
      m_pParentForm->SetFocusedWidget(shared_from_this());
    }
    else
    {
      // stop focusing
      m_pParentForm->SetFocusedWidget(nullptr);
    }
  }

  void CColorPicker::Input()
  {
    // widget's area
    FGUI::AREA arWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, m_dmSize.m_iWidth, m_dmSize.m_iHeight };

    // open colorpicker
    if (FGUI::INPUT.IsCursorInArea(arWidgetRegion))
    {
      m_bOpened = !m_bOpened;
    }
  }

} // namespace FGUI