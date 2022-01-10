
#pragma once

#include <string>

#include "Logger/Logger.h"

#define THROW_LOGGED_ERROR(message) \
    LOG(ERROR, message);            \
    throw std::runtime_error(message);
