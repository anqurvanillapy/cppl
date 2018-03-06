/**
 *  printf for register
 *  ===================
 *
 *  printf the value of a certain register.  Note that a) even "memory" clobber
 *  is used, it is a fence provided by the compiler so that the processor may
 *  still give unexpected results, e.g. for predictive reads; b) since it is a
 *  macro, memory safety is not regarded.
 */

#include <stdio.h>

#if defined(__i386__)
#define regprintf(reg, format, i) do {  \
	__asm__ volatile(                   \
		"movl %%"#reg", %0"             \
		: "=r"(i)                       \
		:                               \
		: "%"#reg, "memory"             \
	);                                  \
	printf(format, i);                  \
} while (0)
#elif defined(__x86_64__)
#define regprintf(reg, format, i) do {  \
	__asm__ volatile(                   \
		"movq %%"#reg", %0"             \
		: "=r"(i)                       \
		:                               \
		: "%"#reg, "memory"             \
	);                                  \
	printf(format, i);                  \
} while (0)
#else
#error "regprintf not supported on this platform"
#endif

int
main()
{
	unsigned long i = 42;
	regprintf(rsp, "0x%lx\n", i);   // 64-bit stack pointer
	return 0;
}
