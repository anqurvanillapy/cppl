/**
 *  Blocks
 *  ======
 *
 *  Lambda-expression-like syntax to create closures in C.
 *
 *  Note: libblocksruntime-dev is required.  Use clang to compile with arguments
 *  -fblocks -lBlockRuntime.
 */

#include <stdio.h>
#include <Block.h>
#include <assert.h>

typedef int (^int_block)();

int_block
make_counter(int start, int step)
{
	// Closure local variables.
	__block int i = start;

	return Block_copy(^(void) {
		int ret = i;
		i += step;
		return ret;
	});
}

int
main()
{
	void (^greet)(void) = ^(void) {
		printf("Hello, BlockRuntime!\n");
	};
	greet();

	int_block cnt = make_counter(0, 3);
	(void)cnt();    // => 0
	(void)cnt();    // => 3
	assert(6 == cnt());

	return 0;
}
