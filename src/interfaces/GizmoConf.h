#pragma once

#include <PositionAttitudeConf.h>
#include <nlohmann/json.hpp>

namespace nsConfig
{
struct Gizmo
{
    bool                 enabled;
    std::string          type;
    std::string          model;
    PositionAttitudeConf pat;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Gizmo, enabled, type, model, pat)
} // namespace nsConfig