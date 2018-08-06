/**
 *  Union access
 *  ============
 */

#include <stdio.h>

int
main()
{
	union {
		int a;
		char b[2];
	} *p, u;

	p = &u;
	p->b[0] = 0x38;
	p->b[1] = 0x39;

	printf("%x\n", u.a); // 3938 (little-endian)

	char* rp = (char*)p;

	printf("%x\n", rp[0]);
	printf("%x\n", rp[1]);
	printf("%x\n", rp[2]); // XXX: uninited
	printf("%x\n", rp[3]); // XXX: uninited

	return 0;
}
