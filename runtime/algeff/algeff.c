#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

enum unit { tt };

struct context;
struct runnable;

struct runnable {
  union args {
    enum unit ask;
    struct args·main·r0 {
      int argc;
    } main·r0;
    struct args·main·r1 {
      int n;
    } main·r1;
  } args;
  union ret {
    enum unit main;
  } (*cb)(struct context *ctx, union args args);
};

struct context {
  int to, back;
  struct runnable runnables[16];
  size_t count;
};

static void context·init(struct context *ctx) {
  ctx->to = -1;
  ctx->back = -1;
  ctx->count = 0;
}

static int context·push(struct context *ctx, struct runnable f) {
  assert(ctx->count < sizeof(ctx->runnables) / sizeof(struct runnable));
  ctx->runnables[ctx->count] = f;
  int at = (int)ctx->count;
  ctx->count++;
  return at;
}

static void context·yield(struct context *ctx, int to, union args args) {
  ctx->to = to;
  ctx->runnables[ctx->to].args = args;
}

static void context·back(struct context *ctx, int back) { ctx->back = back; }

static void context·stop(struct context *ctx) { ctx->to = -1; }

static void context·forward(struct context *ctx) { ctx->back = -1; }

static union ret main·ask·r0(struct context *ctx, union args args);
static union ret main·ask·r1(struct context *ctx, union args args);
static union ret main·r0(struct context *ctx, union args args);
static union ret main·r1(struct context *ctx, union args args);

static union ret main·ask·r0(struct context *ctx, union args args) {
  (void)args;
  int back = context·push(ctx, (struct runnable){.cb = main·ask·r1});
  context·yield(ctx, 2, (union args){.main·r1 = {42}});
  context·back(ctx, back);
  return (union ret){.main = tt};
}

static union ret main·ask·r1(struct context *ctx, union args args) {
  (void)args;
  context·yield(ctx, 2, (union args){.main·r1 = {69}});
  context·forward(ctx);
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
    if (ctx->back >= 0 && ctx->to < 0) {
      r = &ctx->runnables[ctx->back];
    } else if (ctx->to >= 0) {
      r = &ctx->runnables[ctx->to];
    } else {
      break;
    }
    ret = r->cb(ctx, r->args);
  }
  return ret;
}

static int ask(struct context *ctx) {
  context·yield(ctx, 0, (union args){.ask = tt});
  context·back(ctx, 0);
  return 0;
}

static union ret main·r0(struct context *ctx, union args args) {
  int n;
  {
    bool p = args.main·r0.argc == 1;
    if (p) {
      ask(ctx);
      context·push(ctx, (struct runnable){.cb = main·r1});
      return (union ret){.main = tt};
    } else {
      n = 0;
    }
  }
  printf("%d\n", n);
  context·stop(ctx);
  return (union ret){.main = tt};
}

static union ret main·r1(struct context *ctx, union args args) {
  printf("%d\n", args.main·r1.n);
  context·stop(ctx);
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
