//
// external base 
// project started - 03/01/2019
//

#pragma once

#include <string>

namespace UTILITIES
{
  inline std::string Encrypt(const std::string& _string)
  {
    // encryption "key"
    constexpr char cKey = '½'; // This can be any char/number

    // encrypted output
    static std::string strOutput = _string;

    for (std::size_t i = 0; i < _string.size(); i++)
    {
      strOutput[i] = (_string[i] ^ cKey);
    }

    return strOutput;
  }

  inline void MouseMove(long _to_x, long _to_y)
  {
    // select which "type" of input we want
    INPUT tagInput = { INPUT_MOUSE };

    // set the type of event that will be triggered (movement)
    tagInput.mi = { _to_x, _to_y, 0, MOUSEEVENTF_MOVE, 0, NULL };

    SendInput(1, &tagInput, sizeof(INPUT));
  }

  inline void MouseClick()
  {
    // select which "type" of input we want
    INPUT tagInput = { INPUT_MOUSE };

    // get mouse position
    POINT prgpiPos = { 0, 0 };
    GetCursorPos(&prgpiPos);

    // set the type of event that will be triggered (left click)
    tagInput.mi = { prgpiPos.x, prgpiPos.y, 0, (MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP), 0, NULL };

    SendInput(1, &tagInput, sizeof(INPUT));
  }
}