#include <limine.h>

extern void kernel_main(struct limine_framebuffer *fb);

/* Limine framebuffer request */
__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request fb_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0,
};

__attribute__((used, section(".limine_requests_start")))
static volatile uint64_t start[] = LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile uint64_t end[] = LIMINE_REQUESTS_END_MARKER;

void _start(void)
{
    if (!fb_request.response || fb_request.response->framebuffer_count == 0)
    {
        for (;;) __asm__ volatile("cli; hlt");
    }

    kernel_main(fb_request.response->framebuffers[0]);

    for (;;) __asm__ volatile("cli; hlt");
}
