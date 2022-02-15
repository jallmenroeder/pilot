
#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "Logger/Logger.h"

static void VK_ASSERT(bool check) {
    if (!check) exit(EXIT_FAILURE);
}

#define LOGGED_EXIT(message) \
    LOG(ERROR, message);            \
    VK_ASSERT(false);

#define VK_CHECK(value, message) \
    if ((value) != VK_SUCCESS) \
        { LOG(ERROR, (message)); VK_ASSERT(false); }

#define VK_CHECK_RET(value, message) \
    if ((value) != VK_SUCCESS)\
        { LOG(ERROR, (message)); VK_ASSERT(false); return (value); }


