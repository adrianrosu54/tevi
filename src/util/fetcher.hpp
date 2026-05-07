#pragma once

#include <functional>

#include "args.hpp"
#include "util/data.hpp"

using SourceFetcher = std::function<void()>;

SourceFetcher setSourceFetcher(const Config &config, AppData &data);
