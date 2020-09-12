# Core

A case study for debugging core file.

Also, checkout the [blog](http://www.brendangregg.com/blog/2016-08-09/gdb-example-ncurses.html)
by God of system engineering, Brendan Gregg.

The following command enables dumping of the core file with unlimited size.

```bash
$ ulimit -c unlimited
```

In macOS, the core files are located at `/cores`, the write permission of the
directory should be guaranteed first.

```bash
$ sudo chown -R anqur /cores
```

The snippet to analyze is fairly simple, and the goal is to find out in which
function/frame the code causes the segmentation fault, with information of
variables, manipulations, and context (e.g. registers, signals).

```c
#include <stdlib.h>

int main()
{
    char *p = NULL;
    *p = 'c';
    return 0;
}
```

Compile and run it.

```bash
$ gcc oops.c -g3
$ ./a.out
```

Use `lldb` to debug the core file.  The command map of `lldb` and `gdb` is
[here](http://lldb.llvm.org/use/map.html).

```bash
$ lldb -c /cores/core.$PID
```

Checkout the backtrace.

```
(lldb) bt
* thread #1, stop reason = signal SIGSTOP
  * frame #0: 0x0000000106ca4fa9 a.out`main at oops.c:6:8
    frame #1: 0x00007fff706dacc9 libdyld.dylib`start + 1
```

By `oops.c:6:8`, we see that the operation `=` causes the segmentation fault.

```c
int main()
{
    char *p = NULL;
    *p = 'c';
//~~~~~^
    return 0;
}
```

But why?  Why is the assignment fatal?  We need to know the content of `p`.
Just use the `print`/`p` command.

```
(lldb) p p
(char *) $0 = 0x0000000000000000 <no value available>
```

Sometimes we can totally forget what the function is doing, like we don't have
the access to the source code, or the symbols are stripped.  For instance, we
have no idea there is a null pointer deference in the function `main`.  In this
scenerio, we should observe the behavior of the function.

Strip it, without mercy.

```bash
$ strip a.out
```

No symbols anymore.

```
(lldb) bt
* thread #1, stop reason = signal SIGSTOP
  * frame #0: 0x000000010529dfa9 a.out`___lldb_unnamed_symbol1$$a.out + 25
    frame #1: 0x00007fff706dacc9 libdyld.dylib`start + 1
```

Similar to Java, we can do disassembly of the program to understand what the
function/frame actually does.  And the debugger can indicate the location where
the segfault occurs.

The diassembled code is in x86 assembly, not that readable as that from Java
bytecode :) (Actually, this phase is called *discompilation*, which is hard for
C because assembly is hardware-specific).

```
(lldb) disas -f
a.out`___lldb_unnamed_symbol1$$a.out:
    0x10529df90 <+0>:  pushq  %rbp
    0x10529df91 <+1>:  movq   %rsp, %rbp
    0x10529df94 <+4>:  xorl   %eax, %eax
    0x10529df96 <+6>:  movl   $0x0, -0x4(%rbp)
    0x10529df9d <+13>: movq   $0x0, -0x10(%rbp)
    0x10529dfa5 <+21>: movq   -0x10(%rbp), %rcx
->  0x10529dfa9 <+25>: movb   $0x63, (%rcx)
    0x10529dfac <+28>: popq   %rbp
    0x10529dfad <+29>: retq
```

The address and assembly code related to the segfault is listed, but we need to
know the context.  Use the command `register read` to check out the register
values.

```
(lldb) register read
General Purpose Registers:
       rax = 0x0000000000000000
       rbx = 0x0000000000000000
       rcx = 0x0000000000000000
       rdx = 0x00007ffeea962ad0
       rdi = 0x0000000000000001
       rsi = 0x00007ffeea962ac0
       rbp = 0x00007ffeea962aa0
       rsp = 0x00007ffeea962aa0
        r8 = 0x0000000000000000
        r9 = 0x0000000000000000
       r10 = 0x0000000000000000
       r11 = 0x0000000000000000
       r12 = 0x0000000000000000
       r13 = 0x0000000000000000
       r14 = 0x0000000000000000
       r15 = 0x0000000000000000
       rip = 0x000000010529dfa9  a.out`___lldb_unnamed_symbol1$$a.out + 25
    rflags = 0x0000000000010246
        cs = 0x000000000000002b
        fs = 0x0000000000000000
        gs = 0x0000000000000000
```

So the behavior of the unknown frame is clear:

1. Move 32-bit value `0` to the stack, location `-0x04` via `%rbp`, I have no
idea what is it for, maybe it's a local variable for the return value
1. Move 64-bit value `0`/`NULL` to the stack, location `-0x10` via `%rbp`, it's
definitely for the pointer variable `p`
1. Move the 64-bit value from `-0x10(%rbp)` to `%rcx`, act as a memory address.
By [calling convention](https://docs.microsoft.com/en-us/windows-hardware/drivers/debugger/x64-architecture#calling-conventions),
`%rcx` is used to store the first value of first four integers or pointers
1. `%rcx` is dereferenced and assigned to 8-bit value `0x63` (`'c'`), segfault!
(the syntax of pointer dereferencing is `(%rcx)`)

Other useful registers:

1. `%rip`, the instruction pointer

Other advanced commands:

1. `image list`, print the locations of loaded libraries, e.g.
    ```
    (lldb) image list
    [  0] E4698FBD-806A-3396-B279-E685BA37430B 0x000000010f73c000 /usr/lib/dyld
    [  1] 2F21935D-282E-3E2B-87D5-D2F26889918D 0x000000010529d000 /Users/anqur/workspace/cppl/debug/core/a.out
    ...
    [  9] 7E711A46-5E4D-393C-AEA6-440E2A5CCD0C 0x00007fff706c0000 /usr/lib/system/libdyld.dylib
    ...
    ```
    Remember that `libdyld.dylib` is listed in the backtrace?  By the name I
    guess that it is related to the metafunctions of dynamically linking.

Other advanced topics, like thread states, are not discussed here since they are
trivial.
