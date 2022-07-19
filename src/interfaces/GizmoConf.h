#pragma once

#include <PositionAttitudeConf.h>
#include <nlohmann/json.hpp>

namespace nsConfig
{
struct Gizmo
{
    std::string          type;
    std::string          model;
    PositionAttitudeConf pat;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Gizmo, type, model, pat)
} // namespace nsConfig