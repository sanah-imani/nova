#pragma once

#include <stdint.h>
#include <stdbool.h>

#include <drivers/framebuffer/framebuffer.h>

void renderer_init(void);

void renderer_fill_rect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color);
