#pragma once

#include <nlohmann/json.hpp>
namespace nsConfig
{
struct Gizmo
{
    std::string type;
    std::string model;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Gizmo, type, model)
} // namespace nsConfig