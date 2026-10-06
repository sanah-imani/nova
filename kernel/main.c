#include "drivers/framebuffer/framebuffer.h"
#include "graphics/renderer/renderer.h"
#include "panic/panic.h"

void kernel_main(struct limine_framebuffer *fb)
{
    /* 1. Initialize framebuffer driver */
    if (!fb_init(fb))
        panic("Framebuffer init failed");

    /* 2. Initialize higher-level systems */
    renderer_init();

    /* 3. Clear screen (via driver, not Limine) */
    fb_clear(0x00112233);

    /* 4. Test renderer (NOT framebuffer directly later) */
    renderer_fill_rect(100, 100, 400, 200, 0x00FFFFFF);

    renderer_fill_rect(100, 100, 400, 24, 0x000055AA);

    /* 5. Halt */
    for (;;) __asm__("hlt");
}