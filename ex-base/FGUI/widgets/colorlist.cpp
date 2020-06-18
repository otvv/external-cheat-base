//
// FGUI - feature rich graphical user interface
//

// library includes
#include "colorlist.hpp"

namespace FGUI
{

  SColorInfo_t::SColorInfo_t(std::string identificator, FGUI::COLOR color, bool gradient)
  {
    m_strIdentificator = identificator;
    m_bIsSecondColorAdded = false;
    m_bGradient = gradient;
    m_clrFirst = color;
    m_clrSecond = { 1, 1, 1 };
  }

  CColorList::CColorList()
  {
    m_strTitle = "ColorList";
    m_iEntrySpacing = 20;
    m_iScrollThumbPosition = 0;
    m_uiSelectedEntry = false;
    m_bIsDragging = false;
    m_ulFont = 0;
    m_nType = static_cast<int>(WIDGET_TYPE::COLORLIST);
    m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE) | static_cast<int>(WIDGET_FLAG::CLICKABLE) | static_cast<int>(WIDGET_FLAG::SAVABLE);
  }

  void CColorList::AddColor(std::string identificator, FGUI::COLOR color, bool gradient)
  {
    m_prgpColorInfo.emplace_back(identificator, color, gradient);
  }

  void CColorList::SetColor(std::size_t index, FGUI::COLOR color, bool gradient)
  {
    m_prgpColorInfo[index].m_clrFirst = color;
    m_prgpColorInfo[index].m_bGradient = gradient;
  }

  FGUI::COLOR CColorList::GetColor(std::size_t index)
  {
    if (m_prgpColorInfo[index].m_bGradient)
    {
      static float flFirstTimeFraction = 0.f;

      flFirstTimeFraction = std::fminf(flFirstTimeFraction + 0.0005f, 1.f);

      if (flFirstTimeFraction >= 1.f)
      {
        static float flSecondTimeFraction = 0.f;

        // ghetto way to return back to the first color
        flSecondTimeFraction = std::fminf(flSecondTimeFraction + 0.0005f, 1.f);

        if (flSecondTimeFraction >= 1.f)
        {
          flSecondTimeFraction = 0.f;
          flFirstTimeFraction = 0.f;
        }

        return FGUI::COLOR::Interpolate(m_prgpColorInfo[index].m_clrSecond, m_prgpColorInfo[index].m_clrFirst, flSecondTimeFraction);
      }

      return FGUI::COLOR::Interpolate(m_prgpColorInfo[index].m_clrFirst, m_prgpColorInfo[index].m_clrSecond, flFirstTimeFraction);
    }

    return m_prgpColorInfo[index].m_clrFirst;
  }

  std::vector<FGUI::COLOR_INFO> CColorList::GetColorInfo()
  {
    return m_prgpColorInfo;
  }

  void CColorList::Geometry()
  {
    // color gap
    static constexpr int iColorPickerGap = 250;

    FGUI::AREA arWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, (m_dmSize.m_iWidth - iColorPickerGap), m_dmSize.m_iHeight };
    FGUI::AREA arScrollBarRegion = { (arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight) - 15, (arWidgetRegion.m_iTop + 20), 15, (m_dmSize.m_iHeight - 20) };

    // entries displayed
    int iEntriesDisplayed = 0;

    // calculate the amount of entries (colors) that will be drawn inside the colorlist
    int iCalculatedEntries = ((m_dmSize.m_iHeight - 20) / m_iEntrySpacing);

    // colorlist body
    FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop - 5), arWidgetRegion.m_iRight, 1, { 220, 220, 220 });
    FGUI::RENDER.Rectangle(arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + 17), arWidgetRegion.m_iRight, 1, { 220, 220, 220 });
    FGUI::RENDER.Outline(arWidgetRegion.m_iLeft, (arWidgetRegion.m_iTop + 20) - 1, (arWidgetRegion.m_iRight + 1), (arWidgetRegion.m_iBottom - 20) + 1, { 220, 220, 220 });
    FGUI::RENDER.Rectangle((arWidgetRegion.m_iLeft + 1), (arWidgetRegion.m_iTop + 20) + 1, arWidgetRegion.m_iRight - 2, (arWidgetRegion.m_iBottom - 20) - 2, { 255, 255, 255 });

    // colorlist entries
    for (std::size_t i = m_iScrollThumbPosition; (i < m_prgpColorInfo.size()) && (iEntriesDisplayed < iCalculatedEntries); i++)
    {
      FGUI::AREA arEntryRegion = { arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop + (m_iEntrySpacing * iEntriesDisplayed) + 20, (arWidgetRegion.m_iRight - arScrollBarRegion.m_iRight), m_iEntrySpacing };

      // check if the user is hovers or selects something on the colorlist
      if (FGUI::INPUT.IsCursorInArea(arEntryRegion) || m_uiSelectedEntry == i)
      {
        FGUI::RENDER.Rectangle((arEntryRegion.m_iLeft + 1), arEntryRegion.m_iTop, (arWidgetRegion.m_iRight - 2), arEntryRegion.m_iBottom, { 235, 235, 255 });
      }

      static constexpr FGUI::DIMENSION dmColorButtonSize = { 20, 16 };

      // color button body
      FGUI::RENDER.Outline((arEntryRegion.m_iLeft + 95), (arEntryRegion.m_iTop + 2), dmColorButtonSize.m_iWidth, (dmColorButtonSize.m_iHeight - 2), { 220, 220, 220 });
      FGUI::RENDER.Rectangle((arEntryRegion.m_iLeft + 95) + 1, (arEntryRegion.m_iTop + 3), (dmColorButtonSize.m_iWidth - 2), (dmColorButtonSize.m_iHeight - 4), { 195, 195, 195 });
      FGUI::RENDER.Rectangle((arEntryRegion.m_iLeft + 95) + 1, (arEntryRegion.m_iTop + 3), (dmColorButtonSize.m_iWidth - 2), (dmColorButtonSize.m_iHeight - 4), m_prgpColorInfo[i].m_clrFirst);

      // if the user adds a second color sequence
      if (m_prgpColorInfo[i].m_bIsSecondColorAdded)
      {
        FGUI::RENDER.Outline((arEntryRegion.m_iLeft + 95) + 25, (arEntryRegion.m_iTop + 2), dmColorButtonSize.m_iWidth, (dmColorButtonSize.m_iHeight - 2), { 220, 220, 220 });
        FGUI::RENDER.Rectangle(((arEntryRegion.m_iLeft + 95) + 25) + 1, (arEntryRegion.m_iTop + 3), (dmColorButtonSize.m_iWidth - 2), (dmColorButtonSize.m_iHeight - 4), { 195, 195, 195 });
        FGUI::RENDER.Rectangle(((arEntryRegion.m_iLeft + 95) + 25) + 1, (arEntryRegion.m_iTop + 3), (dmColorButtonSize.m_iWidth - 2), (dmColorButtonSize.m_iHeight - 4), m_prgpColorInfo[i].m_clrSecond);
      }

      // color separator
      FGUI::RENDER.Rectangle(arEntryRegion.m_iLeft, (arEntryRegion.m_iTop + arEntryRegion.m_iBottom) - 1, arWidgetRegion.m_iRight, 1, { 205, 205, 205 });

      // color button label
      FGUI::RENDER.Text((arEntryRegion.m_iLeft + 5), (arEntryRegion.m_iTop + 2), m_ulFont, { 35, 35, 35 }, m_prgpColorInfo[i].m_strIdentificator);

      iEntriesDisplayed++;
    }

    // color picker size
    static constexpr FGUI::DIMENSION dmColorPickerSize = { 150, 150 };

    FGUI::AREA arColorPickerRegion = { (GetAbsolutePosition().m_iX + (m_dmSize.m_iWidth - iColorPickerGap) + 10), (GetAbsolutePosition().m_iY + 20), dmColorPickerSize.m_iWidth, dmColorPickerSize.m_iHeight };

    static constexpr int iPixelation = 3; // TODO: make a function for this

    // color picker body
    FGUI::RENDER.Rectangle(arColorPickerRegion.m_iLeft, arColorPickerRegion.m_iTop, arColorPickerRegion.m_iRight, arColorPickerRegion.m_iBottom, { 100, 100, 100 });

    for (std::size_t i = 0; i < static_cast<float>(arColorPickerRegion.m_iBottom); i += iPixelation)
    {
      // color hue
      FGUI::COLOR clrHue = FGUI::COLOR::HSBToRGB(i / 150.f, 1.f, 1.f);

      FGUI::RENDER.Rectangle((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 10, (arColorPickerRegion.m_iTop + i), 15, iPixelation, clrHue);

      for (std::size_t j = 0; j < static_cast<float>(arColorPickerRegion.m_iRight); j += iPixelation)
      {
        // color hsb
        FGUI::COLOR clrHSB = FGUI::COLOR::HSBToRGB(FGUI::COLOR::GetHue(m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst), j / static_cast<float>(arColorPickerRegion.m_iRight), i / static_cast<float>(arColorPickerRegion.m_iBottom), m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst.m_ucAlpha);

        FGUI::RENDER.Rectangle((arColorPickerRegion.m_iLeft + j), (arColorPickerRegion.m_iTop + i), iPixelation, iPixelation, clrHSB);
      }
    }

    // color hsb body
    FGUI::RENDER.Outline(arColorPickerRegion.m_iLeft - 1, arColorPickerRegion.m_iTop - 1, arColorPickerRegion.m_iRight + 2, arColorPickerRegion.m_iBottom + 2, { 220, 220, 220 });

    // hue bar body
    FGUI::RENDER.Outline(((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 10) - 1, arColorPickerRegion.m_iTop - 1, (15 + 2), arColorPickerRegion.m_iBottom + 2, { 220, 220, 220 });
    FGUI::RENDER.Rectangle(((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 5), arColorPickerRegion.m_iTop + (arColorPickerRegion.m_iBottom * FGUI::COLOR::GetHue(m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst)), 3, 3, { 35, 35, 35 });

    // r, g, b color text size
    FGUI::DIMENSION dmColorRedTextSize = FGUI::RENDER.GetTextSize(m_ulFont, std::to_string(m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst.m_ucRed));
    FGUI::DIMENSION dmColorGreenTextSize = FGUI::RENDER.GetTextSize(m_ulFont, std::to_string(m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst.m_ucGreen));
    FGUI::DIMENSION dmColorBlueTextSize = FGUI::RENDER.GetTextSize(m_ulFont, std::to_string(m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst.m_ucBlue));

    // color preview body
    FGUI::RENDER.Outline(((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 35) - 1, arColorPickerRegion.m_iTop - 1, (45 + 2), (45 + 2), { 220, 220, 220 });
    FGUI::RENDER.Rectangle(((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 35), arColorPickerRegion.m_iTop, 45, 45, m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst);

    // color preview label
    FGUI::RENDER.Text((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 35, (arColorPickerRegion.m_iTop - 20) + (arColorPickerRegion.m_iBottom / 2) - (dmColorRedTextSize.m_iHeight / 2) + 10, m_ulFont, { 35, 35, 35 }, "R: " + std::to_string(m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst.m_ucRed));
    FGUI::RENDER.Text((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 35, (arColorPickerRegion.m_iTop - 20) + (arColorPickerRegion.m_iBottom / 2) - (dmColorGreenTextSize.m_iHeight / 2) + 30, m_ulFont, { 35, 35, 35 }, "G: " + std::to_string(m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst.m_ucGreen));
    FGUI::RENDER.Text((arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 35, (arColorPickerRegion.m_iTop - 20) + (arColorPickerRegion.m_iBottom / 2) - (dmColorBlueTextSize.m_iHeight / 2) + 50, m_ulFont, { 35, 35, 35 }, "B: " + std::to_string(m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst.m_ucBlue));

    // sequence label
    FGUI::RENDER.Text(arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop, m_ulFont, { 35, 35, 35 }, "Sequences");

    //
    // plus sequence button
    //

    FGUI::AREA arPlusButtonRegion = { (GetAbsolutePosition().m_iX + 70), (GetAbsolutePosition().m_iY - 1), 16, 16 };

    FGUI::DIMENSION dmPlusButtonTextSize = FGUI::RENDER.GetTextSize(m_ulFont, "+");

    // plus button body
    if (FGUI::INPUT.IsCursorInArea(arPlusButtonRegion))
    {
      FGUI::RENDER.Rectangle(arPlusButtonRegion.m_iLeft, arPlusButtonRegion.m_iTop, arPlusButtonRegion.m_iRight, arPlusButtonRegion.m_iBottom, { 50, 50, 50 });
    }
    else
    {
      FGUI::RENDER.Rectangle(arPlusButtonRegion.m_iLeft, arPlusButtonRegion.m_iTop, arPlusButtonRegion.m_iRight, arPlusButtonRegion.m_iBottom, { 35, 90, 120 });
    }

    // plus button label
    FGUI::RENDER.Text(arPlusButtonRegion.m_iLeft + (arPlusButtonRegion.m_iRight / 2) - (dmPlusButtonTextSize.m_iWidth / 2),
      arPlusButtonRegion.m_iTop + (arPlusButtonRegion.m_iBottom / 2) - (dmPlusButtonTextSize.m_iHeight / 2), m_ulFont, { 245, 245, 245 }, "+");

    //
    // remove sequence button
    //

    FGUI::AREA arMinusButtonRegion = { (GetAbsolutePosition().m_iX + 90), (GetAbsolutePosition().m_iY - 1), 16, 16 };

    FGUI::DIMENSION dmMinusButtonTextSize = FGUI::RENDER.GetTextSize(m_ulFont, "-");

    // minus button body
    if (FGUI::INPUT.IsCursorInArea(arMinusButtonRegion))
    {
      FGUI::RENDER.Rectangle(arMinusButtonRegion.m_iLeft, arMinusButtonRegion.m_iTop, arMinusButtonRegion.m_iRight, arMinusButtonRegion.m_iBottom, { 50, 50, 50 });
    }
    else
    {
      FGUI::RENDER.Rectangle(arMinusButtonRegion.m_iLeft, arMinusButtonRegion.m_iTop, arMinusButtonRegion.m_iRight, arMinusButtonRegion.m_iBottom, { 35, 90, 120 });
    }

    // minus button label
    FGUI::RENDER.Text(arMinusButtonRegion.m_iLeft + (arMinusButtonRegion.m_iRight / 2) - (dmMinusButtonTextSize.m_iWidth / 2),
      arMinusButtonRegion.m_iTop + (arMinusButtonRegion.m_iBottom / 2) - (dmMinusButtonTextSize.m_iHeight / 2), m_ulFont, { 245, 245, 245 }, "-");

    //
    // gradient checkbox
    //

    FGUI::AREA arCheckboxRegion = { (GetAbsolutePosition().m_iX + 115), (GetAbsolutePosition().m_iY - 1), 16, 16 };

    // checkbox body
    FGUI::RENDER.Outline((arCheckboxRegion.m_iLeft - 1), (arCheckboxRegion.m_iTop - 1), arCheckboxRegion.m_iRight, arCheckboxRegion.m_iBottom, { 220, 220, 220 });
    FGUI::RENDER.Rectangle(arCheckboxRegion.m_iLeft, arCheckboxRegion.m_iTop, (arCheckboxRegion.m_iRight - 2), (arCheckboxRegion.m_iBottom - 2), { 255, 255, 255 });

    if (m_prgpColorInfo[m_uiSelectedEntry].m_bGradient)
    {
      if (FGUI::INPUT.IsCursorInArea(arCheckboxRegion))
      {
        FGUI::RENDER.Outline((arCheckboxRegion.m_iLeft - 1), (arCheckboxRegion.m_iTop - 1), arCheckboxRegion.m_iRight, arCheckboxRegion.m_iBottom, { 180, 25, 25 });
      }

      FGUI::RENDER.Rectangle((arCheckboxRegion.m_iLeft + 3), (arCheckboxRegion.m_iTop + 3), (arCheckboxRegion.m_iRight - 8), (arCheckboxRegion.m_iBottom - 8), { 180, 25, 25 });
    }
    else
    {
      if (FGUI::INPUT.IsCursorInArea(arCheckboxRegion))
      {
        FGUI::RENDER.Outline((arCheckboxRegion.m_iLeft - 1), (arCheckboxRegion.m_iTop - 1), arCheckboxRegion.m_iRight, arCheckboxRegion.m_iBottom, { 195, 195, 195 });
      }
    }

    // checkbox label
    FGUI::RENDER.Text(arCheckboxRegion.m_iLeft + (arCheckboxRegion.m_iRight + 5), arCheckboxRegion.m_iTop, m_ulFont, { 35, 35, 35 }, "Gradient");

    //
    // alpha slider
    //

    // slider picker size 
    static constexpr FGUI::DIMENSION dmSliderThumbSize = { 8, 6 };

    FGUI::AREA arSliderRegion = { arColorPickerRegion.m_iLeft, (arColorPickerRegion.m_iTop + arColorPickerRegion.m_iBottom) + 40, arColorPickerRegion.m_iRight, 2 };

    FGUI::DIMENSION dmSliderTextSize = FGUI::RENDER.GetTextSize(m_ulFont, "alpha");

    // slider body
    FGUI::RENDER.Rectangle(arSliderRegion.m_iLeft, arSliderRegion.m_iTop, arSliderRegion.m_iRight, arSliderRegion.m_iBottom, { 20, 50, 70 });

    // slider label
    FGUI::RENDER.Text(arSliderRegion.m_iLeft, (arSliderRegion.m_iTop - dmSliderTextSize.m_iHeight), m_ulFont, { 35, 35, 35 }, "alpha");

    // slider custom value
    std::string strCustomValue = "";
    float flValueToPercentage = (m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst.m_ucAlpha / 2.55f);

    // custom range text
    if (m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst.m_ucAlpha == 0)
    {
      strCustomValue = "Transparent";
    }
    else if (m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst.m_ucAlpha == 255)
    {
      strCustomValue = "Opaque";
    }
    else
    {
      strCustomValue = std::to_string(static_cast<int>(flValueToPercentage)) + "%";
    }

    FGUI::DIMENSION dmSliderValueTextSize = FGUI::RENDER.GetTextSize(m_ulFont, strCustomValue);

    // slider value
    FGUI::RENDER.Text((arSliderRegion.m_iLeft + arSliderRegion.m_iRight) - dmSliderValueTextSize.m_iWidth, (arSliderRegion.m_iTop - dmSliderTextSize.m_iHeight) - 2, m_ulFont, { 35, 35, 35 }, strCustomValue);

    // slider position ratio
    float flRatio = (m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst.m_ucAlpha - 0.f) / (255.f - 0.f);
    float flLocation = (flRatio * arColorPickerRegion.m_iRight);

    // slider thumb
    FGUI::RENDER.Rectangle((arSliderRegion.m_iLeft + flLocation), (arSliderRegion.m_iTop - 2), dmSliderThumbSize.m_iWidth, dmSliderThumbSize.m_iHeight, { 180, 25, 25 });

    static constexpr FGUI::DIMENSION dmScrollBarThumbWidth = { 8, 5 };

    // calculate thumb position
    float flCalculatedPosition = static_cast<float>(m_iScrollThumbPosition) / static_cast<float>(m_prgpColorInfo.size());

    if (flCalculatedPosition >= 1.f)
    {
      flCalculatedPosition = 1.f;
    }

    flCalculatedPosition *= ((m_dmSize.m_iHeight - 20) - m_iEntrySpacing) - 10;

    // calculate thumb size
    float flCalculatedSize = static_cast<float>(iCalculatedEntries) / static_cast<float>(m_prgpColorInfo.size());

    if (flCalculatedSize > 1.f)
    {
      flCalculatedSize = 1.f;
    }

    flCalculatedSize *= ((m_dmSize.m_iHeight - 20) - m_iEntrySpacing);

    // scrollbar body
    FGUI::RENDER.Rectangle(arScrollBarRegion.m_iLeft, arScrollBarRegion.m_iTop, arScrollBarRegion.m_iRight, arScrollBarRegion.m_iBottom, { 235, 235, 235 });

    if (m_prgpColorInfo.size() > 50)
    {
      FGUI::RENDER.Rectangle((arScrollBarRegion.m_iLeft + 4), (arScrollBarRegion.m_iTop + flCalculatedPosition) + 5, dmScrollBarThumbWidth.m_iWidth, dmScrollBarThumbWidth.m_iHeight, { 220, 223, 231 });
    }
    else
    {
      FGUI::RENDER.Rectangle((arScrollBarRegion.m_iLeft + 4), (arScrollBarRegion.m_iTop + flCalculatedPosition) + 5, dmScrollBarThumbWidth.m_iWidth, flCalculatedSize, { 220, 223, 231 });
    }
  }

  void CColorList::Update()
  {
    if (m_bIsDragging)
    {
      // calculate the amount of entries that will be drawn on the colorlist
      int iCalculatedEntries = ((m_dmSize.m_iHeight - 20) / m_iEntrySpacing);

      FGUI::POINT ptCursorPos = FGUI::INPUT.GetCursorPos();

      if (FGUI::INPUT.GetKeyState(MOUSE_1))
      {
        // move thumb vertically
        ptCursorPos.m_iY -= (GetAbsolutePosition().m_iY + 20);

        // ratio of how many visible to how many are hidden
        float flVisibleRatio = static_cast<float>(iCalculatedEntries) / static_cast<float>(m_prgpColorInfo.size());
        flVisibleRatio *= ((m_dmSize.m_iHeight - 20) - m_iEntrySpacing);

        // calculate height delta
        float flHeightDelta = static_cast<float>(ptCursorPos.m_iY + flVisibleRatio) - static_cast<float>((m_dmSize.m_iHeight - 20));

        if (flHeightDelta >= 0.f)
        {
          ptCursorPos.m_iY -= flHeightDelta;
        }

        // new vertical position ratio
        float flNewYRatio = static_cast<float>(ptCursorPos.m_iY) / static_cast<float>(m_dmSize.m_iHeight - 20);
        m_iScrollThumbPosition = (flNewYRatio * m_prgpColorInfo.size());

        // clamp position (don't let the user drag the scrollthumb if it reaches the "start" of the scrollbar area)
        if (m_iScrollThumbPosition <= 0)
        {
          m_iScrollThumbPosition = 0;
        }
      }
      else
      {
        m_bIsDragging = false;
      }
    }

    // color gap
    static constexpr int iColorPickerGap = 250;

    static constexpr FGUI::DIMENSION dmColorPickerSize = { 150, 150 };

    FGUI::AREA arColorPickerRegion = { (GetAbsolutePosition().m_iX + (m_dmSize.m_iWidth - iColorPickerGap) + 10), (GetAbsolutePosition().m_iY + 20), dmColorPickerSize.m_iWidth, dmColorPickerSize.m_iHeight };

    FGUI::AREA arColorHSBRegion = { arColorPickerRegion.m_iLeft, arColorPickerRegion.m_iTop, arColorPickerRegion.m_iRight, arColorPickerRegion.m_iBottom };

    FGUI::AREA arColorHueRegion = { (arColorPickerRegion.m_iLeft + arColorPickerRegion.m_iRight) + 10, arColorPickerRegion.m_iTop, 15, arColorPickerRegion.m_iBottom };
    
    FGUI::AREA arAlphaSliderRegion = { arColorPickerRegion.m_iLeft, (arColorPickerRegion.m_iTop + arColorPickerRegion.m_iBottom) + 40, arColorPickerRegion.m_iRight, 10 };

    // switches
    static bool bColorHSBSelected = false;
    static bool bColorHueSelected = false;
    static bool bAlphaSliderSelected = false;

    FGUI::POINT ptCursorPos = FGUI::INPUT.GetCursorPos();

    if (FGUI::INPUT.GetKeyPress(MOUSE_1))
    {
      bColorHSBSelected = FGUI::INPUT.IsCursorInArea(arColorHSBRegion);
      bColorHueSelected = FGUI::INPUT.IsCursorInArea(arColorHueRegion);
      bAlphaSliderSelected = FGUI::INPUT.IsCursorInArea(arAlphaSliderRegion);
    }
    else if (FGUI::INPUT.GetKeyRelease(MOUSE_1))
    {
      bColorHSBSelected = false;
      bColorHueSelected = false;
      bAlphaSliderSelected = false;
    }

    if (bColorHSBSelected)
    {
      FGUI::PRECISION prRelativePos = { ptCursorPos.m_iX - static_cast<float>(arColorHSBRegion.m_iLeft), ptCursorPos.m_iY - static_cast<float>(arColorHSBRegion.m_iTop) };

      m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst = FGUI::COLOR::HSBToRGB(FGUI::COLOR::GetHue(m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst), (prRelativePos.m_flX /
        arColorPickerRegion.m_iRight), (prRelativePos.m_flY / arColorPickerRegion.m_iBottom), m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst.m_ucAlpha);
    }
    else if (bColorHueSelected)
    {
      float flHue = (ptCursorPos.m_iY - arColorHueRegion.m_iTop) / 150.f;

      m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst = FGUI::COLOR::HSBToRGB(std::clamp(flHue, 0.f, 1.f), 1.f, 1.f);
    }
    else if (bAlphaSliderSelected)
    {
      float flXPosDelta = 0.f;
      float flRatio = 0.f;

      // change slider value based on mouse movement
      flXPosDelta = (ptCursorPos.m_iX - arColorPickerRegion.m_iLeft);

      // clamp values
      if (flXPosDelta <= 0.f)
      {
        flXPosDelta = 0.f;
      }

      else if (flXPosDelta >= arColorPickerRegion.m_iRight)
      {
        flXPosDelta = arColorPickerRegion.m_iRight;
      }

      // calculate slider ratio
      flRatio = flXPosDelta / static_cast<float>(arColorPickerRegion.m_iRight);

      // change slider value
      m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst.m_ucAlpha = 0.f + (255.f - 0.f) * flRatio;
    }
  }

  void CColorList::Input()
  {
    // color gap
    static constexpr int iColorPickerGap = 250;

    FGUI::AREA arWidgetRegion = { GetAbsolutePosition().m_iX, GetAbsolutePosition().m_iY, (m_dmSize.m_iWidth - iColorPickerGap), m_dmSize.m_iHeight };

    FGUI::AREA arScrollBarRegion = { (arWidgetRegion.m_iLeft + arWidgetRegion.m_iRight) - 15, (arWidgetRegion.m_iTop + 20), 15, (m_dmSize.m_iHeight - 20) };

    if (FGUI::INPUT.IsCursorInArea(arScrollBarRegion))
    {
      m_bIsDragging = true;
    }

    // entries displayed
    int iEntriesDisplayed = 0;

    // calculate the amount of entries that will be drawn on the colorlist
    int iCalculatedEntries = ((m_dmSize.m_iHeight - 20) / m_iEntrySpacing);

    // colorlist entries
    for (std::size_t i = m_iScrollThumbPosition; (i < m_prgpColorInfo.size()) && (iEntriesDisplayed < iCalculatedEntries); i++)
    {
      FGUI::AREA arEntryRegion = { arWidgetRegion.m_iLeft, arWidgetRegion.m_iTop + (m_iEntrySpacing * iEntriesDisplayed) + 20, (arWidgetRegion.m_iRight - 15), m_iEntrySpacing };

      // select an entry
      if (FGUI::INPUT.IsCursorInArea(arEntryRegion))
      {
        m_uiSelectedEntry = i;
      }

      iEntriesDisplayed++;
    }

    FGUI::AREA arPlusButtonRegion = { (GetAbsolutePosition().m_iX + 70), (GetAbsolutePosition().m_iY - 1), 16, 16 };

    FGUI::AREA arMinusButtonRegion = { (GetAbsolutePosition().m_iX + 90), (GetAbsolutePosition().m_iY - 1), 16, 16 };

    if (FGUI::INPUT.IsCursorInArea(arPlusButtonRegion))
    {
      if (!m_prgpColorInfo[m_uiSelectedEntry].m_bIsSecondColorAdded)
      {
        // make the first color be the secondary color
        m_prgpColorInfo[m_uiSelectedEntry].m_clrSecond = m_prgpColorInfo[m_uiSelectedEntry].m_clrFirst;

        // add a new color into the sequence
        m_prgpColorInfo[m_uiSelectedEntry].m_bIsSecondColorAdded = true;
      }
    }

    else if (FGUI::INPUT.IsCursorInArea(arMinusButtonRegion))
    {
      if (m_prgpColorInfo[m_uiSelectedEntry].m_bIsSecondColorAdded)
      {
        // remeve color from sequence
        m_prgpColorInfo[m_uiSelectedEntry].m_bIsSecondColorAdded = false;
      }
    }

    FGUI::AREA arCheckboxRegion = { (GetAbsolutePosition().m_iX + 115), (GetAbsolutePosition().m_iY - 1), 16, 16 };

    if (FGUI::INPUT.IsCursorInArea(arCheckboxRegion))
    {
      m_prgpColorInfo[m_uiSelectedEntry].m_bGradient = !m_prgpColorInfo[m_uiSelectedEntry].m_bGradient;
    }
  }

} // namespace FGUI