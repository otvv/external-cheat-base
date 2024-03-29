//
// external base 
// project started - 03/01/2019
//

#include <thread>
#include <iostream>

#include "overlay.hpp"
#include "render.hpp"
#include "input.hpp"

int main(HINSTANCE _instance)
{
  // initialize FGUI's input system
  INPUT_SYSTEM::OnEntryPoint();

  // initialize FGUI's render manager
  RENDER::OnEntryPoint();

  // initialize the overlay
  OVERLAY::OnEntryPoint(_instance);

  return 0;
}
