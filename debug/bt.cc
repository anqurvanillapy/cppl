/**
 *  Backtrace
 *  =========
 *
 *  Print the backtrace using libunwind.h, forget about setjmp.h and ucontext.h.
 *
 *  Note: Compile with -g -lunwind and run with env
 *  LD_LIBRARY_PATH=/usr/local/lib.
 */

#define UNW_LOCAL_ONLY
#include <cxxabi.h>
#include <libunwind.h>
#include <iostream>

#define UNLIKELY(cond) __builtin_expect((cond), 0)

void
backtrace()
{
	unw_cursor_t cur;
	unw_context_t ctx;

	unw_getcontext(&ctx);
	unw_init_local(&cur, &ctx);

	while (unw_step(&cur) > 0) {
		unw_word_t offset, pc;
		unw_get_reg(&cur, UNW_REG_IP, &pc);

		if (UNLIKELY(pc == 0)) {
			break;
		}

		std::cout << "pc=0x" << std::hex << pc;

		char sym[256];
		if (unw_get_proc_name(&cur, sym, sizeof(sym), &offset) == 0) {
			char* p = sym;
			int rc;
			char* demangled = abi::__cxa_demangle(sym, nullptr, nullptr, &rc);
			if (rc == 0) {
				p = demangled;
			}
			std::cout
				<< "\t(" << p << "+0x" << std::hex << offset << ")"
				<< std::endl;
			delete demangled;
		} else {
			std::cout
				<< "cannot obtain symbol name for this frame"
				<< std::endl;
		}
	}
}

namespace foo {

template <typename T, typename U>
void
foo(T a, U b)
{
	(void)a; (void)b;
	backtrace();
}

} /* namespace foo */

template <typename T>
struct bar_t {
	T t;
	void
	bar()
	{
		foo::foo(t, 42);
	}
};

int
main()
{
	bar_t<int> x;
	x.bar();
	return 0; // note: no leaks via valgrind
}
