#include <fmt/format.h>
#include <string>

#ifndef GRAPHICS_FRAMEWORKS_CPP_RESOURCE_H
#define GRAPHICS_FRAMEWORKS_CPP_RESOURCE_H

std::string resourcePath(const std::string& resource)
{
    return fmt::format("../../resources/{}", resource);
}

#endif // GRAPHICS_FRAMEWORKS_CPP_RESOURCE_H
