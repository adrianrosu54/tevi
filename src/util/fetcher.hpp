#pragma once

#include <functional>

#include "args.hpp"
#include "util/data.hpp"

using SourceFetcher = std::function<cv::Mat()>;

SourceFetcher setSourceFetcher(const Config &config, AppData &data);
