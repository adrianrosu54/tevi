#pragma once

#include "util/data.hpp"
#include "util/pixel.hpp"

void renderImage(const AppData &data, PixelPainter painter,
                 const char *lineStart = "");
