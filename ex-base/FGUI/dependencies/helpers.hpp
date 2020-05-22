//
// FGUI - feature rich graphical user interface
//

#ifndef FGUI_HELPERS_HH
#define FGUI_HELPERS_HH

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
// These keys defaults to virtual key-codes from WindowsAPI (GetAsyncKeyState)
#define MOUSE_1 1
#define KEY_ESCAPE 27
#define KEY_ENTER 13
#define KEY_BACKSPACE 8
#define KEY_LSHIFT 160
#define KEY_RSHIFT 161
#define KEY_DELETE 46
#define KEY_LEFT 37
#define KEY_RIGHT 39

#ifdef FGUI_USE_D3D9

#include <d3d9.h>
#include <d3dx9.h>
#include <dwmapi.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")

namespace FGUI
{
	using FONT = ID3DXFont*;
}
#elif FGUI_USE_OPENGL

// TODO: OpenGL support

#else

namespace FGUI
{
	using FONT = unsigned long;
}
#endif

#else
// These keys defaults to virtual key-codes from Source Engine (IInputSystem) 
#define MOUSE_1 107
#define KEY_ESCAPE 70
#define KEY_ENTER 64
#define KEY_BACKSPACE 66
#define KEY_LSHIFT 79
#define KEY_RSHIFT 80
#define KEY_DELETE 73
#define KEY_LEFT 89
#define KEY_RIGHT 91
#endif

#endif // FGUI_HELPERS_HH