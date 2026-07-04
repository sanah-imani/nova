#include <stdint.h>
#include <stddef.h>
#include "limine.h"

/* Limine base revision - must be set to indicate protocol version */
__attribute__((used, section(".limine_requests")))
static volatile uint64_t base_revision[3] = LIMINE_BASE_REVISION(3);

/* Request a framebuffer from the bootloader */
__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request fb_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0,
    .response = NULL,
};

/* Requests start/end markers required by Limine v2+ */
__attribute__((used, section(".limine_requests_start")))
static volatile uint64_t requests_start_marker[] = LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile uint64_t requests_end_marker[] = LIMINE_REQUESTS_END_MARKER;

static void draw_pixel(struct limine_framebuffer *fb, uint32_t x, uint32_t y, uint32_t color) {
    uint32_t *pixel = (uint32_t *)((uint8_t *)fb->address + y * fb->pitch + x * (fb->bpp / 8));
    *pixel = color;
}

static void draw_rect(struct limine_framebuffer *fb, uint32_t x, uint32_t y,
                      uint32_t w, uint32_t h, uint32_t color) {
    for (uint32_t row = y; row < y + h; row++)
        for (uint32_t col = x; col < x + w; col++)
            draw_pixel(fb, col, row, color);
}

void _start(void) {
    /* Halt if bootloader didn't fulfil our framebuffer request */
    if (fb_request.response == NULL || fb_request.response->framebuffer_count < 1) {
        for (;;) __asm__("hlt");
    }

    struct limine_framebuffer *fb = fb_request.response->framebuffers[0];

    /* Clear screen to dark blue */
    draw_rect(fb, 0, 0, fb->width, fb->height, 0x00001A33);

    /* Draw a white rectangle as a "window" placeholder */
    draw_rect(fb, 100, 100, 400, 200, 0x00FFFFFF);

    /* Draw a title bar */
    draw_rect(fb, 100, 100, 400, 24, 0x000055AA);

    for (;;) __asm__("hlt");
}
