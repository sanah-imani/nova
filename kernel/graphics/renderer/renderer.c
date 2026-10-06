#include "renderer.h"

void renderer_init(void){

}

void renderer_fill_rect(uint32_t x, uint32_t y,
                        uint32_t w, uint32_t h,
                        uint32_t color)
{
    uint32_t max_x = fb_width();
    uint32_t max_y = fb_height();

    for (uint32_t j = y; j < y + h && j < max_y; j++)
    {
        for (uint32_t i = x; i < x + w && i < max_x; i++)
        {
            fb_put_pixel(i, j, color);
        }
    }
}