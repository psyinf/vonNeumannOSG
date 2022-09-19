#pragma once

#include <glog/logging.h>

static std::string quote(const std::string& s)
{
    return std::string("'" + s + "'");
}