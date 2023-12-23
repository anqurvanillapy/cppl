.PHONY: all
all: a.out

a.out: algeff.c
	clang \
		-std=c99 \
		-Werror \
		-Wall \
		-Wextra \
		-Wpedantic \
		-Wshadow \
		-Wcast-align \
		-Wunused \
		-Wconversion \
		-Wsign-conversion \
		-Wnull-dereference \
		-Wdouble-promotion \
		-Wformat=2 \
		-fsanitize=address \
		-O0 \
		-g3 \
		-o $@ \
		$^

.PHONY: clean
clean:
	rm -rf a.out
