#include "panic.h"

_Noreturn void panic(const char *msg)
{
    (void)msg; /* No output path yet: no font renderer, no serial driver */

    for (;;)
        __asm__ volatile("cli; hlt");
}
