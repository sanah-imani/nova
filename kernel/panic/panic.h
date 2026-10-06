#ifndef NOVA_PANIC_H
#define NOVA_PANIC_H

/**
 * Halts the system permanently with an unrecoverable error.
 * Never returns.
 */
_Noreturn void panic(const char *msg);

#endif
