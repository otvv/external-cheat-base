//
// external base 
// project started - 03/01/2019
//

#pragma once

#define NOMINMAX

#include <vector>
#include <string>
#include <windows.h>
#include <psapi.h>
#include <iostream>
#include <tlhelp32.h>
#include <stdlib.h>
#include <stdexcept>

class Memory
{
public:

  // gets the module base address using the process id
  std::uintptr_t GetModule(const std::string& _module_name, unsigned long _process_id)
  {
    HANDLE moduleHandle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, _process_id);

    m_tagModuleEntry.dwSize = sizeof(MODULEENTRY32);

    do {

      if (!strcmp(m_tagModuleEntry.szModule, _module_name.c_str()))
      {
        // close handle
        CloseHandle(moduleHandle);

        return reinterpret_cast<std::uintptr_t>(m_tagModuleEntry.modBaseAddr);
      }
    }

    while (Module32Next(moduleHandle, &m_tagModuleEntry));

    CloseHandle(moduleHandle);

    return 0;
  }

  // get the module base address
  std::uintptr_t GetBaseAddress()
  {
    // get the module base address by its process id
    m_ullBaseAddress = GetModule("process.exe", m_ulProcessID);

    // give us full access to our process
    m_pProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, 0, m_ulProcessID);

    return m_ullBaseAddress;
  }

  // get process id
  unsigned long GetProcessID()
  {
    m_hWindowHandle = FindWindow(nullptr, "TARGET_WINDOW_NAME_HERE");

    // get the process id of the window handle 
    GetWindowThreadProcessId(m_hWindowHandle, &m_ulProcessID);

    return m_ulProcessID;
  }

  // write memory
  template <class t>
  inline void Write(std::uint64_t _address, t _value)
  {
    VirtualProtectEx(m_pProcessHandle, reinterpret_cast<void*>(_address), sizeof(t), PAGE_EXECUTE_READWRITE, &m_ulProtect);
    WriteProcessMemory(m_pProcessHandle, reinterpret_cast<void*>(_address), &_value, sizeof(t), nullptr);
    VirtualProtectEx(m_pProcessHandle, reinterpret_cast<void*>(_address), sizeof(t), m_ulProtect, &m_ulProtect2);
  }

  // read memory
  template <class t>
  inline t Read(std::uint64_t address)
  {
    t buffer;

    VirtualProtectEx(m_pProcessHandle, reinterpret_cast<void*>(_address), sizeof(t), PAGE_EXECUTE_READWRITE, &m_ulProtect);
    ReadProcessMemory(m_pProcessHandle, reinterpret_cast<void*>(_address), &buffer, sizeof(buffer), nullptr);
    VirtualProtectEx(m_pProcessHandle, reinterpret_cast<void*>(_address), sizeof(t), m_ulProtect, &m_ulProtect2);

    return buffer;
  }

public:
  void* m_pProcessHandle;
private:

  HWND m_hWindowHandle;
  unsigned long m_ulProtect;
  unsigned long m_ulProtect2;
  unsigned long m_ulProcessID;
  MODULEENTRY32 m_tagModuleEntry;
  unsigned long long m_ullBaseAddress;
};

inline Memory g_Memory;