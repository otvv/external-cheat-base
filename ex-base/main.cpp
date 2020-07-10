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
  // initialize input system
  INPUT::OnEntryPoint();

  // initialize render manager
  RENDER::OnEntryPoint();

  // initialize the overlay
  OVERLAY::OnEntryPoint(_instance);

  return 0;
}
