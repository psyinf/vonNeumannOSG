#pragma once

#include <nlohmann/json.hpp>

namespace nsConfig
{
struct BehaviorConf
{
    bool           enabled = true;
    std::string    type;
    nlohmann::json conf;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(BehaviorConf, enabled, type, conf)

} // namespace nsConfig
