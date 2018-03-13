/**
 *  shilib private API
 *  ==================
 *
 *  Use `make bar` to try finding the private API `bar` and see what happens,
 *  and `make` to ignore it.
 *
 *  Note: Only supported when `__GNUC__ >= 4`.
 */

#include "liba.h"

int
main()
{
	foo();
#ifdef TRY_BAR
	bar();
#endif /* TRY_BAR */
	return 0;
}
