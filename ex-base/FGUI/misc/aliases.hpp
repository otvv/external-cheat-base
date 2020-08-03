//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_ALIASES_HH
#define FGUI_ALIASES_HH

// includes
#include <functional>

// library includes
#include "definitions.hpp"

#define FGUI_USE_D3D9 // tell FGUI to use D3D9
#include "helpers.hpp"

namespace FGUI
{
  namespace DETAIL
  {
    // drawing functions pointers
    using pCreateFont = std::add_pointer_t<void(FGUI::FONT&, std::string, int, int, bool)>;
    using pGetScreenSize = std::add_pointer_t<FGUI::DIMENSION()>;
    using pGetTextSize = std::add_pointer_t<FGUI::DIMENSION(FGUI::FONT, std::string)>;
    using pLimitArea = std::add_pointer_t<void(FGUI::AREA)>;
    using pResetLimit = std::add_pointer_t<void()>;
    using pDrawRectangle = std::add_pointer_t<void(int, int, int, int, FGUI::COLOR)>;
    using pDrawOutline = std::add_pointer_t<void(int, int, int, int, FGUI::COLOR)>;
    using pDrawGradient = std::add_pointer_t<void(int, int, int, int, FGUI::COLOR, FGUI::COLOR, bool)>;
    using pDrawLine = std::add_pointer_t<void(int, int, int, int, FGUI::COLOR)>;
    using pDrawText = std::add_pointer_t<void(int, int, FGUI::FONT, FGUI::COLOR, std::string)>;

    // input functions pointers
    using pPullInput = std::add_pointer_t<void()>;
    using pIsKeyHeld = std::add_pointer_t<bool(unsigned int)>;
    using pIsKeyReleased = std::add_pointer_t<bool(unsigned int)>;
    using pIsKeyPressed = std::add_pointer_t<bool(unsigned int)>;
    using pGetCursorPos = std::add_pointer_t<FGUI::POINT()>;
    using pGetCursorPosDelta = std::add_pointer_t<FGUI::POINT()>;
    using pIsCursorInArea = std::add_pointer_t<bool(FGUI::AREA)>;

  } // namespace DETAIL

  using INPUT_TYPE = enum struct ESInputType_t : int
  {
    NONE = 0,
    WIN_32 = 1,
    INPUT_SYSTEM = 2,
    CUSTOM = 3
  };

  using RENDER_MANAGER = struct SRenderManager_t
  {
    DETAIL::pCreateFont CreateFont;
    DETAIL::pGetScreenSize GetScreenSize;
    DETAIL::pGetTextSize GetTextSize;
    DETAIL::pLimitArea LimitArea;
    DETAIL::pResetLimit ResetLimit;
    DETAIL::pDrawRectangle Rectangle;
    DETAIL::pDrawOutline Outline;
    DETAIL::pDrawGradient Gradient;
    DETAIL::pDrawLine Line;
    DETAIL::pDrawText Text;
  };

  using INPUT_SYTEM = struct SInputSystem_t
  {
    DETAIL::pPullInput PullInput;
    DETAIL::pIsKeyHeld IsKeyHeld;
    DETAIL::pIsKeyReleased IsKeyReleased;
    DETAIL::pIsKeyPressed IsKeyPressed;
    DETAIL::pGetCursorPos GetCursorPos;
    DETAIL::pGetCursorPosDelta GetCursorPosDelta;
    DETAIL::pIsCursorInArea IsCursorInArea;

    // @brief: set the input type
    // @params: FGUI::INPUT_TYPE::WIN_32 = input type (NONE, WIN_32, INPUT_SYSTEM or CUSTOM)
    // @note: make sure to set this when you initialize your widgets
    void SetInputType(FGUI::INPUT_TYPE type)
    {
      m_nInputType = static_cast<int>(type);
    }

    // @brief: get the current input type
    int GetInputType()
    {
      return m_nInputType;
    }

  private:
    int m_nInputType;
  };

  inline RENDER_MANAGER RENDER;
  inline INPUT_SYTEM INPUT;

} // namespace FGUI

#endif // FGUI_ALIASES_HH