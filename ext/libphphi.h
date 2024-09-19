#ifndef LIBPHPHI_H
#define LIBPHPHI_H

#include <string.h>
#include <limits.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <stdint.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dlfcn.h>

typedef unsigned long rlim_t;
typedef __rlimit_resource_t __rlimit_resource_t;
// typedef rlimit rlimit;

extern int errno;
char *strerror(int errnum);

// struct rlimit {
//     rlim_t rlim_cur;
//     rlim_t rlim_max;
// };


#endif  // LIBPHPHI_H
