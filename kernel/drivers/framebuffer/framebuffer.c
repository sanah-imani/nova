#include "framebuffer.h"

#include <limine.h>
#include <stdint.h>
#include <stddef.h>

static struct
{
    uint32_t *address;

    uint32_t width;
    uint32_t height;

    uint32_t pitch;
    uint16_t bpp;
} g_framebuffer;

/* ----------------------------
 * Initialization
 * ---------------------------- */

bool fb_init(struct limine_framebuffer *fb)
{
    if (fb == NULL)
        return false;

    g_framebuffer.address = (uint32_t *)fb->address;
    g_framebuffer.width   = fb->width;
    g_framebuffer.height  = fb->height;
    g_framebuffer.pitch   = fb->pitch;
    g_framebuffer.bpp     = fb->bpp;

    return true;
}

/* ----------------------------
 * Query API
 * ---------------------------- */

uint32_t fb_width(void)
{
    return g_framebuffer.width;
}

uint32_t fb_height(void)
{
    return g_framebuffer.height;
}

/* ----------------------------
 * Pixel primitive
 * ---------------------------- */

void fb_put_pixel(uint32_t x, uint32_t y, uint32_t color)
{
    if (x >= g_framebuffer.width || y >= g_framebuffer.height)
        return;

    uint8_t *row = (uint8_t *)g_framebuffer.address + y * g_framebuffer.pitch;
    uint32_t *pixel = (uint32_t *)row;

    pixel[x] = color;
}

/* ----------------------------
 * Screen fill
 * ---------------------------- */

void fb_clear(uint32_t color)
{
    for (uint32_t y = 0; y < fb_height(); y++)
    {
        for (uint32_t x = 0; x < fb_width(); x++)
        {
            fb_put_pixel(x, y, color);
        }
    }
}