//
// FGUI - feature rich graphical user interface
//

// library includes
#include "cursor.hpp"

namespace FGUI
{
  CCursor::CCursor()
  {
    m_clrCursor = { 245, 245, 245 };
    m_nStyle = static_cast<int>(CURSOR_STYLE::ARROW);
    m_nType = static_cast<int>(WIDGET_TYPE::CURSOR);
    m_nFlags = static_cast<int>(WIDGET_FLAG::DRAWABLE);
  }

  void CCursor::SetStyle(FGUI::CURSOR_STYLE style)
  {
    m_nStyle = static_cast<int>(style);
  }

  void CCursor::SetColor(FGUI::COLOR color)
  {
     m_clrCursor = color;
  }

  void CCursor::Geometry(FGUI::WIDGET_STATUS status)
  {
    FGUI::POINT ptCursorPos = FGUI::INPUT.GetCursorPos();

    switch (m_nStyle)
    {
      case static_cast<int>(CURSOR_STYLE::ARROW) :
      {
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 1, ptCursorPos.m_iY, 1, 17, { 1, 1, 1 });

        for (std::size_t i = 0; i < 11; i++)
        {
          FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 2 + i, ptCursorPos.m_iY + 1 + i, 1, 1, { 1, 1, 1 });
        }

        FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 8, ptCursorPos.m_iY + 12, 5, 1, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 8, ptCursorPos.m_iY + 13, 1, 1, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 9, ptCursorPos.m_iY + 14, 1, 2, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 10, ptCursorPos.m_iY + 16, 1, 2, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 8, ptCursorPos.m_iY + 18, 2, 1, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 7, ptCursorPos.m_iY + 16, 1, 2, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 6, ptCursorPos.m_iY + 14, 1, 2, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 5, ptCursorPos.m_iY + 13, 1, 1, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 4, ptCursorPos.m_iY + 14, 1, 1, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 3, ptCursorPos.m_iY + 15, 1, 1, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 2, ptCursorPos.m_iY + 16, 1, 1, { 1, 1, 1 });

        for (std::size_t i = 0; i < 4; i++)
        {
          FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 2 + i, ptCursorPos.m_iY + 2 + i, 1, 14 - (i * 2), m_clrCursor);
        }

        FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 6, ptCursorPos.m_iY + 6, 1, 8, m_clrCursor);
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 7, ptCursorPos.m_iY + 7, 1, 9, m_clrCursor);

        for (std::size_t i = 0; i < 4; i++)
        {
          FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 8 + i, ptCursorPos.m_iY + 8 + i, 1, 4 - i, m_clrCursor);
        }

        FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 8, ptCursorPos.m_iY + 14, 1, 4, m_clrCursor);
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 9, ptCursorPos.m_iY + 16, 1, 2, m_clrCursor);

        break;
      }
      case static_cast<int>(CURSOR_STYLE::IBEAM) :
      {

        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 1, ptCursorPos.m_iY - 1, 6 + 3, 1 + 2, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX, ptCursorPos.m_iY, 7, 1, m_clrCursor);

        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 1, ptCursorPos.m_iY - 1 + 9, 6 + 3, 1 + 2, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX, ptCursorPos.m_iY + 9, 7, 1, m_clrCursor);

        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 1 + 3, ptCursorPos.m_iY - 1, 1 + 2, 9 + 2, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 3, ptCursorPos.m_iY, 1, 9 + 1, m_clrCursor);
        break;
      }
      case static_cast<int>(CURSOR_STYLE::HAND) :
      {
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 6, ptCursorPos.m_iY + 5 + 5 + -5, 7, 9, m_clrCursor);
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5, ptCursorPos.m_iY + 5 + 7 + -5, 1, 2, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 1, ptCursorPos.m_iY + 5 + 6 + -5, 1, 1, { 1, 1, 1 });

        for (std::size_t i = 0; i < 3; ++i)
        {
          FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 2 + i, ptCursorPos.m_iY + 5 + 6 + i + -5, 1, 1, { 1, 1, 1 });
        }

        for (std::size_t i = 0; i < 4; ++i)
        {
          FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 1 + i, ptCursorPos.m_iY + 5 + 9 + i + -5, 1, 1, { 1, 1, 1 });
          FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 1 + i, ptCursorPos.m_iY + 5 + 7 + i + -5, 1, 1, m_clrCursor);
          FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 2 + i, ptCursorPos.m_iY + 5 + 7 + i + -5, 1, 1, m_clrCursor);
          FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 1 + i, ptCursorPos.m_iY + 5 + 8 + i + -5, 1, 1, m_clrCursor);
          FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 3 + i, ptCursorPos.m_iY + 5 + 11 + i + -5, 1, 1, m_clrCursor);
        }

        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 4, ptCursorPos.m_iY + 5 + 1 + -5, 1, 7, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 5, ptCursorPos.m_iY + 5 + 0 + -5, 2, 1, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 5, ptCursorPos.m_iY + 5 + 15 + -5, 5, 1, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 7, ptCursorPos.m_iY + 5 + 1 + -5, 1, 6, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 8, ptCursorPos.m_iY + 5 + 4 + -5, 4, 1, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 10, ptCursorPos.m_iY + 5 + 5 + -5, 1, 2, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 12, ptCursorPos.m_iY + 5 + 5 + -5, 1, 2, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 13, ptCursorPos.m_iY + 5 + 5 + -5, 1, 1, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 14, ptCursorPos.m_iY + 5 + 6 + -5, 1, 5, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 13, ptCursorPos.m_iY + 5 + 11 + -5, 1, 2, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 12, ptCursorPos.m_iY + 5 + 13 + -5, 1, 3, { 1, 1, 1 });

        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 5, ptCursorPos.m_iY + 5 + 1 + -5, 2, 13, m_clrCursor);
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 7, ptCursorPos.m_iY + 5 + 14 + -5, 3, 1, m_clrCursor);
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 13, ptCursorPos.m_iY + 5 + 6 + -5, 1, 5, m_clrCursor);
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 11, ptCursorPos.m_iY + 5 + 14 + -5, 1, 1, m_clrCursor);

        for (std::size_t i = 0; i < 2; ++i)
        {
          FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 10 + i, ptCursorPos.m_iY + 5 + 14 + i + -5, 1, 1, { 1, 1, 1 });
          FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 4 + i, ptCursorPos.m_iY + 5 + 13 + i + -5, 1, 1, { 1, 1, 1 });
        }

        break;
      }
      case static_cast<int>(CURSOR_STYLE::PIPETTE) :
      {
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX, ptCursorPos.m_iY + 14 + -15, 1, 1, { 1, 1, 1 });

        for (std::size_t i = 0; i < 2; ++i)
        {
          FGUI::RENDER.Rectangle(ptCursorPos.m_iX + i, ptCursorPos.m_iY + 13 - i + -15, 1, 1, { 1, 1, 1 });
          FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 1 + i, ptCursorPos.m_iY + 14 - i + -15, 1, 1, { 1, 1, 1 });
        }

        for (std::size_t i = 0; i < 6; ++i)
        {
          FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 1 + i, ptCursorPos.m_iY + 11 - i + -15, 1, 1, { 1, 1, 1 });
          FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 3 + i, ptCursorPos.m_iY + 13 - i + -15, 1, 1, { 1, 1, 1 });

          FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 2 + i, ptCursorPos.m_iY + 11 - i + -15, 1, 1, m_clrCursor);
          FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 3 + i, ptCursorPos.m_iY + 12 - i + -15, 1, 1, m_clrCursor);
          FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 2 + i, ptCursorPos.m_iY + 12 - i + -15, 1, 1, m_clrCursor);
        }

        FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 8, ptCursorPos.m_iY + 6 + -15, 1, 1, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 7, ptCursorPos.m_iY + 3 + -15, 6, 3, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 9, ptCursorPos.m_iY + 2 + -15, 3, 6, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 11, ptCursorPos.m_iY + -15, 3, 5, { 1, 1, 1 });
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX + 10, ptCursorPos.m_iY + 1 + -15, 5, 3, { 1, 1, 1 });

        break;
      }
      case static_cast<int>(CURSOR_STYLE::MOVE) :
      {
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5, ptCursorPos.m_iY - 1, 5, 1, m_clrCursor);
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 4, ptCursorPos.m_iY - 2, 3, 1, m_clrCursor);
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 3, ptCursorPos.m_iY - 3, 1, 1, m_clrCursor);

        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 3 - 7, ptCursorPos.m_iY + 11 - 7, 1, 5, m_clrCursor);
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 4 - 7, ptCursorPos.m_iY + 12 - 7, 1, 3, m_clrCursor);
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 - 7, ptCursorPos.m_iY + 13 - 7, 1, 1, m_clrCursor);

        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 3 - (12 / 2), ptCursorPos.m_iY + (12 / 2), 12, 1, m_clrCursor);
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 3, ptCursorPos.m_iY, 1, 12, m_clrCursor);

        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5, ptCursorPos.m_iY + 12, 5, 1, m_clrCursor);
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 4, ptCursorPos.m_iY + 13, 3, 1, m_clrCursor);
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 3, ptCursorPos.m_iY + 14, 1, 1, m_clrCursor);

        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 5 + 8, ptCursorPos.m_iY + 11 - 7, 1, 5, m_clrCursor);
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 4 + 8, ptCursorPos.m_iY + 12 - 7, 1, 3, m_clrCursor);
        FGUI::RENDER.Rectangle(ptCursorPos.m_iX - 3 + 8, ptCursorPos.m_iY + 13 - 7, 1, 1, m_clrCursor);

        break;
      }
      default:
        return;
    }

    IGNORE_ARGS(status);
  }

  void CCursor::Update()
  {
  }

  void CCursor::Input()
  {
  }

  void CCursor::Save(nlohmann::json& module)
  {
    IGNORE_ARGS(module);
  }

  void CCursor::Load(nlohmann::json& module)
  {
    IGNORE_ARGS(module);
  }

  void CCursor::Tooltip()
  {
  }

} // namespace FGUI