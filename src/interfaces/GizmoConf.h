#pragma once

#include <PositionAttitudeConf.h>
#include <nlohmann/json.hpp>

namespace nsConfig
{
struct Gizmo
{
    bool                 enabled;
    std::string          type;    // type of the gizmo (e.g. what is the data source)
    std::string          mapping; // how is the gizmo modified by the value (scale, direction ..)
    std::string          model;
    PositionAttitudeConf pat;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Gizmo, enabled, type, mapping, model, pat)
} // namespace nsConfig