//
// external base 
// project started - 03/01/2019
//

#pragma once

#include <iostream>
#include <exception>

#include "utilities.hpp"

#define START try {
#define END(_msg) } catch(...) { std::throw_with_nested(std::runtime_error(_msg)); };
#define THROW(_msg) std::throw_with_nested(std::runtime_error(_msg));
#define PRINT(_msg) std::cout << _msg << std::endl;
#define ENCRYPT(_msg) UTILITIES::Encrypt(_msg);