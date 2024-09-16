## Goal

The confluence of FFI and modern Intermediate Representations
like MLIR/LLVM, can let developers move between languages easier
than before, andwith GPT, "fullstack" development takes on another
dimension - multi-stack.

A part of that is making it easier to call across language backends -
in this case from PHP -> C.  As things develop, I hope to slowly progress
towards a generic semi-structured syntax that's generated to a powerful
IR, abtracting the syntax from capability.

### This Package

This is a trait a few constants that can help keep FFI integrations
consistent.  By default, modules (i.e. classes that use this trait) are
expected to instantiate their own FFI object with their required headers,
.c code, and dependencies, resulting in a shared object.

That shared object .so should also link this shared libray in, resulting
in a single .so which is then ready for FFI::load() and FFI::scope().

It also provides some shared `Makefile` code.

This generally isn't used by itself unless you really want to.  See
specific modules for use examples.

