#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

enum unit { tt };

struct context;
struct runnable;

struct args·main·r0 {
  int argc;
};

struct args·main·r1 {
  int n;
};

union args {
  enum unit ask;
  struct args·main·r0 main·r0;
  struct args·main·r1 main·r1;
};

union ret {
  enum unit main;
};

struct runnable {
  union args args;
  union ret (*cb)(struct context *ctx, union args args);
};

struct context {
  int to;
  struct runnable *handler;
  struct runnable runnables[16];
  size_t count;
};

static void context·init(struct context *ctx) {
  ctx->to = -1;
  ctx->count = 0;
}

static void context·push(struct context *ctx, struct runnable f) {
  assert(ctx->count < sizeof(ctx->runnables) / sizeof(struct runnable));
  ctx->runnables[ctx->count] = f;
  ctx->count++;
}

static void context·yield(struct context *ctx, int to, union args args) {
  ctx->to = to;
  ctx->handler = NULL;
  ctx->runnables[ctx->to].args = args;
}

static union ret main·ask·r0(struct context *ctx, union args args);
static union ret main·ask·r1(struct context *ctx, union args args);
static union ret main·r0(struct context *ctx, union args args);
static union ret main·r1(struct context *ctx, union args args);

static union ret main·ask·r0(struct context *ctx, union args args) {
  (void)args;
  context·push(ctx, (struct runnable){.cb = main·ask·r1});
  context·yield(ctx, 2, (union args){.main·r1 = {42}});
  ctx->handler = &ctx->runnables[3];
  return (union ret){.main = tt};
}

static union ret main·ask·r1(struct context *ctx, union args args) {
  (void)args;
  context·yield(ctx, 2, (union args){.main·r1 = {69}});
  ctx->handler = NULL;
  return (union ret){.main = tt};
}

static union ret schedule·reader(struct context *ctx, struct runnable handler,
                                 struct runnable expr, union args args) {
  context·push(ctx, handler);
  context·push(ctx, expr);
  context·yield(ctx, 1, args);
  union ret ret;
  while (true) {
    struct runnable *r;
    if (ctx->handler && ctx->to < 0) {
      r = ctx->handler;
    } else if (ctx->to >= 0) {
      r = &ctx->runnables[ctx->to];
    } else {
      break;
    }
    ret = r->cb(ctx, r->args);
  }
  return ret;
}

static int ask(struct context *ctx, struct runnable *handler) {
  ctx->handler = handler;
  context·yield(ctx, 0, (union args){.ask = tt});
  return 0;
}

static union ret main·r0(struct context *ctx, union args args) {
  int n;
  {
    bool p = args.main·r0.argc == 1;
    if (p) {
      ask(ctx, &ctx->runnables[0]);
      context·push(ctx, (struct runnable){.cb = main·r1});
      return (union ret){.main = tt};
    } else {
      n = 0;
    }
  }
  printf("%d\n", n);
  ctx->to = -1;
  return (union ret){.main = tt};
}

static union ret main·r1(struct context *ctx, union args args) {
  ctx->to = -1;
  printf("%d\n", args.main·r1.n);
  return (union ret){.main = tt};
}

/*
effect reader
  ctl ask(): int
fun main()
  with ctl ask()
    resume(42)
    resume(69)
  println(if argc == 1 then ask() else 0)
*/
int main(int argc, const char *argv[]) {
  (void)argv;
  struct context ctx;
  context·init(&ctx);
  schedule·reader(&ctx, (struct runnable){.cb = main·ask·r0},
                  (struct runnable){.cb = main·r0},
                  (union args){.main·r0 = {argc}});
  return 0;
}
