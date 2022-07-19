#pragma once
#include "Axis.h"

#include <iostream>
#include <nlohmann/json.hpp>

NLOHMANN_JSON_SERIALIZE_ENUM(Axis,
                             {{Axis::X, "x"},
                              {Axis::Y, "y"},
                              {Axis::Z, "z"}} //
)
