#ifndef _CPPL_PRIVATE_H
#define _CPPL_PRIVATE_H

#define PRIVATE __attribute__((__visibility__("hidden")))

extern void foo();

// Or using #pragma.
// #pragma GCC visibility push(hidden)

// PRIVATE here is optional but better to be kept as an annotation in header.
/* PRIVATE */ extern void bar();

// #pragma GCC visibility pop

#endif /* !_CPPL_PRIVATE_H */
