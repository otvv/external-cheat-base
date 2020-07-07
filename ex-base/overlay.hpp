//
// external base 
// project started - 03/01/2019
//

#pragma once

#include <windows.h>
#include <thread>
#include <dwmapi.h>
#include <fstream>

#include "menu.hpp"
#include "input.hpp"
#include "utilities.hpp"
#include "render.hpp"
#include "helpers.hpp"

#pragma comment(lib, "dwmapi.lib")

namespace OVERLAY
{
  inline FGUI::DIMENSION m_dmSize;
  inline FGUI::AREA m_arOverlayRegion;
  inline FGUI::AREA m_arTargetRegion;

  inline std::string m_strTargetWindowName;
  inline std::string m_strOverlayWindowName;

  inline HWND m_hwndOverlay;
  inline HWND m_hwndTarget;

  inline void Drawing()
  {
    RENDER::m_pDevice->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
    RENDER::m_pDevice->BeginScene();

    // update device state
    RENDER::UpdateDeviceState();

    if (m_hwndTarget == GetForegroundWindow())
    {
      Container->Render();
    }

    RENDER::m_pDevice->EndScene();
    RENDER::m_pDevice->PresentEx(0, 0, 0, 0, 0);
  }

  inline LRESULT CALLBACK WndProc(HWND _handle, UINT _message, WPARAM _wparam, LPARAM _lparam)
  {
    switch (_message)
    {
    case WM_PAINT:
      Drawing();
      break;
    case WM_CREATE:
      DwmExtendFrameIntoClientArea(m_hwndOverlay, reinterpret_cast<MARGINS*>(&m_arOverlayRegion));
      break;
    case WM_MOUSEWHEEL:
      INPUT_SYSTEM::m_iCursorWheelDelta = -GET_WHEEL_DELTA_WPARAM(_wparam);
      break;
    case WM_DESTROY:
      PostQuitMessage(1);
      return 0;
    default:
      return DefWindowProc(_handle, _message, _wparam, _lparam);
      break;
    }

    return FALSE;
  }

  inline void SetWindowToTarget() {

    START

      // find target window
      m_hwndTarget = FindWindow(0, m_strTargetWindowName.c_str());

    // if we have a valid target window
    if (m_hwndTarget)
    {
      // get the dimensions of the target window
      GetWindowRect(m_hwndTarget, reinterpret_cast<LPRECT>(&m_arTargetRegion));
      m_dmSize.m_iWidth = (m_arTargetRegion.m_iRight - m_arTargetRegion.m_iLeft);
      m_dmSize.m_iHeight = (m_arTargetRegion.m_iBottom - m_arTargetRegion.m_iTop);

      // window style
      unsigned long m_ulWindowStyle = GetWindowLong(m_hwndTarget, GWL_STYLE);

      if (m_ulWindowStyle & WS_BORDER)
      {
        m_arTargetRegion.m_iTop += 23;
        m_dmSize.m_iHeight -= 23;
      }

      // move the overlay alongside with the target window (game)
      MoveWindow(m_hwndOverlay, m_arTargetRegion.m_iLeft, m_arTargetRegion.m_iTop, m_dmSize.m_iWidth, m_dmSize.m_iHeight, true);
    }
    else
    {
      LOG("[external base] - window not found.");
    }

    END("[external base] - generic error!")
  }

  inline bool SetupDevice(HWND _handle)
  {
    START

      // create d3d9 object
      Direct3DCreate9Ex(D3D_SDK_VERSION, &RENDER::m_pObject);

    // d3d9 window parameters
    RENDER::m_parParameters.Windowed = TRUE;
    RENDER::m_parParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    RENDER::m_parParameters.hDeviceWindow = m_hwndOverlay;
    RENDER::m_parParameters.MultiSampleQuality = D3DMULTISAMPLE_NONE;
    RENDER::m_parParameters.BackBufferFormat = D3DFMT_A8R8G8B8;
    RENDER::m_parParameters.BackBufferWidth = m_dmSize.m_iWidth;
    RENDER::m_parParameters.BackBufferHeight = m_dmSize.m_iHeight;
    RENDER::m_parParameters.EnableAutoDepthStencil = TRUE;
    RENDER::m_parParameters.AutoDepthStencilFormat = D3DFMT_D16;

    // create d3d9 device
    if (SUCCEEDED(RENDER::m_pObject->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hwndOverlay, D3DCREATE_HARDWARE_VERTEXPROCESSING, &RENDER::m_parParameters, 0, &RENDER::m_pDevice)))
    {
      // create fonts
      RENDER::CreateFontA(FONTS::Title, "Tahoma", 12, 0x0, true);

      // initialize window
      WINDOW::OnSetupDevice();

      return true;
    }

    END("[extern base] - device creation failed.")


      return false;
  }

  inline int SetupOverlay(HINSTANCE _instance)
  {
    START

      CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(SetWindowToTarget), 0, 0, 0);

    WNDCLASSEX wcsexWindow; // top kek name

    // settings
    wcsexWindow.cbSize = sizeof(WNDCLASSEX);
    wcsexWindow.hInstance = _instance;
    wcsexWindow.cbWndExtra = 0;
    wcsexWindow.cbClsExtra = 0;

    // window cursor
    wcsexWindow.hCursor = LoadCursor(NULL, IDC_ARROW);

    // window background (background)
    wcsexWindow.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(NULL_BRUSH));

    // window icon
    wcsexWindow.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcsexWindow.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    // handle window input
    wcsexWindow.lpfnWndProc = reinterpret_cast<WNDPROC>(WndProc);

    // class and window name
    wcsexWindow.lpszClassName = m_strOverlayWindowName.c_str();
    wcsexWindow.lpszMenuName = NULL;

    // tell the window to re-draw when resized
    wcsexWindow.style = (CS_VREDRAW | CS_HREDRAW);

    RegisterClassEx(&wcsexWindow);

    // find target window (game)
    if (m_hwndTarget = FindWindow(NULL, m_strTargetWindowName.c_str()))
    {
      // grab the dimensions of the target window (game)
      GetWindowRect(m_hwndTarget, reinterpret_cast<LPRECT>(&m_arTargetRegion));

      // set the overlay size according to the target window size
      m_dmSize.m_iWidth = (m_arTargetRegion.m_iRight - m_arTargetRegion.m_iLeft);
      m_dmSize.m_iHeight = (m_arTargetRegion.m_iBottom - m_arTargetRegion.m_iTop);

      // create window
      m_hwndOverlay = CreateWindowEx((WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_OVERLAPPED | WS_EX_LAYERED), m_strOverlayWindowName.c_str(), m_strOverlayWindowName.c_str(), WS_POPUP, 0, 0, m_dmSize.m_iWidth, m_dmSize.m_iHeight, NULL, NULL, NULL, NULL);

      SetLayeredWindowAttributes(m_hwndOverlay, 0, RGB(0, 0, 0), LWA_COLORKEY);

      // show window
      ShowWindow(m_hwndOverlay, SW_SHOW);
    }

    // create d3d9 device
    SetupDevice(m_hwndOverlay);

    // main message loop
    static MSG msgOverlay = { NULL };
    while (WM_QUIT != msgOverlay.message)
    {
      if (PeekMessage(&msgOverlay, NULL, 0, 0, PM_REMOVE))
      {
        DispatchMessage(&msgOverlay);
        TranslateMessage(&msgOverlay);
      }
    }

    return static_cast<int>(msgOverlay.wParam);

    END("[external base] - failed to create overlay.")
  }

  inline void OnEntryPoint(HINSTANCE _instance)
  {
    // overlay settings
    m_dmSize = { RENDER::GetScreenSize() };
    m_strOverlayWindowName = "[external base] - External Overlay";
    m_strTargetWindowName = "ex-base (Running) - Microsoft Visual Studio";
    m_arOverlayRegion = { 0, 0, m_dmSize.m_iWidth, m_dmSize.m_iWidth };

    // setup overlay
    SetupOverlay(_instance);
  }
}