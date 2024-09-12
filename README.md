# libphphi
Base traits and helpers for working with PHP FFI modules.

By default, modules (i.e. classes that use this trait) are expected to
instantiate their own FFI object using their header and such with their
dependencies, that'll end up building their own shared object.  That
shared object (.so) should also link this in, resulting in a single .so.

It also provides some shared `Makefile` stuff.

This isn't used by itself unless you really want to.  See specific
modules for usage.


