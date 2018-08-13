/**
 *  Blocky
 *  ======
 *
 *  A simple buddy memory allocator, inspired by cloudwu/buddy.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define BLK_UNUSED  0
#define BLK_USED    1
#define BLK_SPLIT   2
#define BLK_FULL    3

#define UNLIKELY(c) __builtin_expect(!!(c), 0)

static inline uint32_t
next_pow_of_2(uint32_t x)
{
	--x;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	return x + 1;
}

typedef struct blky_t {
	int lvl;
	uint8_t tree[1];
} blky_t;

blky_t*
blky_new(int lvl)
{
	int siz = 1 << lvl;
	blky_t* self = (blky_t*)malloc(sizeof(blky_t) +
								   sizeof(uint8_t) * (siz * 2 - 2));
	self->lvl = lvl;
	memset(self->tree, BLK_UNUSED, siz * 2 - 1);
	return self;
}

void
blky_delete(blky_t* self)
{
	free(self);
}

static inline int
_index_offset(int i, int lvl, int max_lvl)
{
	return ((i + 1) - (1 << lvl)) << (max_lvl - lvl);
}

static void
_mark_parent(blky_t* self, int i)
{
	for (;;) {
		int blk = i - 1 + (i & 1) * 2;
		uint8_t item = self->tree[blk];
		if (blk > 0 && (item == BLK_USED || item == BLK_FULL)) {
			i = (i + 1) / 2 - 1;
			self->tree[i] = BLK_FULL;
		} else {
			return;
		}
	}
}

int
blky_alloc(blky_t* self, int siz)
{
	if (siz == 0) {
		siz = 1;
	} else {
		siz = next_pow_of_2(siz);
	}

	int blksiz = 1 << self->lvl;

	if (UNLIKELY(siz > blksiz)) {
		return -1;
	}

	int i = 0;
	int lvl = 0;

	while (i >= 0) {
		if (siz < blksiz) {
			switch (self->tree[i]) {
			case BLK_USED:
			case BLK_FULL:
				break;
			case BLK_UNUSED:
				self->tree[i] = BLK_SPLIT;
				self->tree[i * 2 + 1] = self->tree[i * 2 + 2] = BLK_UNUSED;
				// fallthrough
			default:
				i = i * 2 + 1;
				blksiz /= 2;
				++lvl;
				continue;
			}
		} else {
			if (self->tree[i] == BLK_UNUSED) {
				self->tree[i] = BLK_USED;
				_mark_parent(self, i);
				return _index_offset(i, lvl, self->lvl);
			}
		}
		if (i & 1) {
			++i;
			continue;
		}
		for (;;) {
			--lvl;
			blksiz *= 2;
			i = (i + 1) / 2 - 1;
			if (i < 0) {
				return -1;
			}
			if (i & 1) {
				++i;
				break;
			}
		}
	}

	return -1;
}

static void
_compact(blky_t* self, int i)
{
	for (;;) {
		int blk = i - 1 + (i & 1) * 2;
		if (blk < 0 || self->tree[blk] != BLK_UNUSED) {
			self->tree[i] = BLK_UNUSED;
			while (( (i = (i + 1) / 2 - 1) >= 0) && self->tree[i] == BLK_FULL) {
				self->tree[i] = BLK_SPLIT;
			}
			return;
		}
		i = (i + 1) / 2 - 1;
	}
}

void
blky_free(blky_t* self, int offset)
{
	int left = 0;
	int i = 0;
	int blksiz = 1 << self->lvl;
	assert(offset < blksiz);

	for (;;) {
		switch (self->tree[i]) {
		case BLK_USED:
			assert(offset == left);
			_compact(self, i);
			return;
		case BLK_UNUSED:
			assert(0);
			return;
		default:
			blksiz /= 2;
			if (offset < left + blksiz) {
				i = i * 2 + 1;
			} else {
				left += blksiz;
				i = i * 2 + 2;
			}
			break;
		}
	}
}

int
blky_size(blky_t* self, int offset)
{
	int left = 0;
	int i = 0;
	int blksiz = 1 << self->lvl;
	assert(offset < blksiz);

	for (;;) {
		switch (self->tree[i]) {
		case BLK_USED:
			assert(offset == left);
			return blksiz;
		case BLK_UNUSED:
			assert(0);
			return -1;
		default:
			blksiz /= 2;
			if (offset < left + blksiz) {
				i = i * 2 + 1;
			} else {
				left += blksiz;
				i = i * 2 + 2;
			}
			break;
		}
	}
}

static void
_dump(blky_t* self, int i, int lvl)
{
	switch (self->tree[i]) {
	case BLK_UNUSED:
		printf("(%d: %d)",
			   _index_offset(i, lvl, self->lvl), 1 << (self->lvl - lvl));
		break;
	case BLK_USED:
		printf("[%d: %d]",
			   _index_offset(i, lvl, self->lvl), 1 << (self->lvl - lvl));
		break;
	case BLK_FULL:
		printf("{");
		_dump(self, i * 2 + 1, lvl + 1);
		_dump(self, i * 2 + 2, lvl + 1);
		printf("}");
		break;
	default:
		printf("(");
		_dump(self, i * 2 + 1, lvl + 1);
		_dump(self, i * 2 + 2, lvl + 1);
		printf(")");
		break;
	}
}

void
blky_dump(blky_t* self)
{
	_dump(self, 0, 0);
	printf("\n");
}

int
main()
{
	blky_t* b = blky_new(5);
	blky_dump(b);

	int a1 = blky_alloc(b, 5);
	printf("a1=%d\n", a1);
	assert(a1 >= 0);
	blky_dump(b);

	int a2 = blky_alloc(b, 15);
	printf("a2=%d\n", a2);
	assert(a2 >= 0);
	blky_dump(b);

	blky_free(b, a1);
	blky_dump(b);

	blky_free(b, a2);
	blky_dump(b);

	blky_delete(b);
	return 0;
}
