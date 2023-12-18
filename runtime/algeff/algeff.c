#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum Unit { TT };

struct Context;

struct Handler·Reader {
  enum Unit (*ask)(struct Context *ctx,
                   enum Unit (*next)(struct Context *ctx, int n));
};

union Handler {
  struct Handler·Reader reader;
};

struct Context {
  bool isYielding;
  size_t handlerCount;
  union Handler handlers[16];
};

static void Context·init(struct Context *ctx) {
  ctx->isYielding = false;
  ctx->handlerCount = 0;
}

static void Context·push(struct Context *ctx, union Handler h) {
  ctx->handlers[ctx->handlerCount] = h;
  ctx->handlerCount++;
  if (ctx->handlerCount > sizeof(ctx->handlers) / sizeof(ctx->handlers[0])) {
    printf("push error: handlers overflow\n");
    exit(1);
  }
}

static union Handler Context·pop(struct Context *ctx) {
  if (ctx->handlerCount == 0) {
    printf("pop error: handlers overflow");
    exit(1);
  }
  ctx->handlerCount--;
  return ctx->handlers[ctx->handlerCount];
}

static bool Context·isYielding(struct Context *ctx) { return ctx->isYielding; }

/*
effect reader
  ctl ask(): int

fun main()
  with handler
    ctl ask()
      resume(42)
      resume(69)
  println(ask())
  // Output:
  // 42
  // 69
*/

static enum Unit perform·ask(struct Context *ctx, int evID,
                             enum Unit (*next)(struct Context *ctx, int n));
static enum Unit main·k0(struct Context *ctx);
static enum Unit main·k1(struct Context *ctx, int n);

static enum Unit perform·ask(struct Context *ctx, int evID,
                             enum Unit (*next)(struct Context *ctx, int n)) {
  union Handler *handler = &ctx->handlers[evID];
  return handler->reader.ask(ctx, next);
}

static enum Unit main·k0(struct Context *ctx) {
  return perform·ask(ctx, 0, main·k1);
}

static enum Unit main·k1(struct Context *ctx, int n) {
  (void)ctx;
  printf("%d\n", n);
  return TT;
}

static enum Unit main·reader·ask(struct Context *ctx,
                                 enum Unit (*next)(struct Context *ctx,
                                                   int n)) {
  next(ctx, 42);
  if (Context·isYielding(ctx)) {
    return TT;
  }
  enum Unit ret = next(ctx, 69);
  if (Context·isYielding(ctx)) {
    return TT;
  }
  return ret;
}

int main(int argc, const char *argv[]) {
  (void)argc;
  (void)argv;

  struct Context ctx;
  Context·init(&ctx);

  Context·push(&ctx, (union Handler){.reader = {.ask = main·reader·ask}});
  main·k0(&ctx);
  Context·pop(&ctx);

  return 0;
}
