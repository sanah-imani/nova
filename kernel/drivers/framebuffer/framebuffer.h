#ifndef NOVA_FRAMEBUFFER_H
#define NOVA_FRAMEBUFFER_H 

#include <stdint.h>
#include <stdbool.h>

struct limine_framebuffer;

/**
Initializes the framebuffer driver.
Returns false if no valid framebuffer exists.
*/

bool fb_init(struct limine_framebuffer* fb);

/* Draw a single pixel */

void fb_put_pixel(uint32_t x, uint32_t y, uint32_t color);

/* Fill the entire screen with a color*/

void fb_clear(uint32_t color);

/*Query framebuffer information*/

uint32_t fb_width(void);
uint32_t fb_height(void);

#endif 


