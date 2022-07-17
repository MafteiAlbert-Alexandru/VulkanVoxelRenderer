#pragma once
#include <cstdint>

struct Config {
    const uint32_t window_width;
    const uint32_t window_height;
    const std::string window_title;
    const std::vector<const char*> validation_layers;
};