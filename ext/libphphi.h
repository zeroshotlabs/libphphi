#define FFI_SCOPE "zsl\\libphphi"

#ifndef LIBPHPHI_H
#define LIBPHPHI_H

#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/stat.h>



// Macro to register a long constant
#define C2PHP_CONST(name, value) \
    do { \
        zend_register_long_constant(name, strlen(name), value, CONST_CS | CONST_PERSISTENT, 0); \
    } while(0)


// // Remove these definitions as they are already defined in <sys/resource.h>
// // #define RLIM_INFINITY;
// // #define RLIMIT_MSGQUEUE;
// // #define RLIMIT_NOFILE;
// C2PHP_CONST('RLIM_INFINITY',R_LIM_INFINITY);
// C2PHP_CONST('RLIMIT_MSGQUEUE', RLIMIT_MSGQUEUE);
// C2PHP_CONST('RLIMIT_NOFILE', RLIMIT_NOFILE);




// // These are typically already defined in <fcntl.h>, but if you need to ensure specific values:
// // #ifndef O_RDONLY
// #define O_RDONLY    00
// // #endif
// //#ifndef O_WRONLY
// #define O_WRONLY    01
// //#endif
// //#ifndef O_RDWR
// #define O_RDWR      02
// //#endif
// //#ifndef O_CREAT
// #define O_CREAT   0100
// //#endif
// //#ifndef O_EXCL
// #define O_EXCL    0200
// //#endif
// //#ifndef O_NONBLOCK
// #define O_NONBLOCK 04000
// //#endif


C2PHP('O_RDONLY',O_RDONLY);
C2PHP('O_WRONLY', O_WRONLY);
C2PHP('O_RDWR', O_RDWR);
C2PHP('O_CREAT', O_CREAT);
C2PHP('O_EXCL', O_EXCL);
C2PHP('O_NONBLOCK', O_NONBLOCK);

C2PHP('RLIM_INFINITY', RLIM_INFINITY);
C2PHP('RLIMIT_MSGQUEUE', RLIMIT_MSGQUEUE);
C2PHP('RLIMIT_NOFILE', RLIMIT_NOFILE);


typedef unsigned long rlim_t;


// Define __rlimit_resource_t if it's not already defined
//#ifndef __rlimit_resource_t
typedef enum __rlimit_resource __rlimit_resource_t;
//#endif


// Declare rlimit struct if not already declared
//#ifndef _STRUCT_RLIMIT
//#define _STRUCT_RLIMIT
typedef struct rlimit rlimit_t;
//#endif


//#ifndef RLIM_INFINITY
//#define RLIM_INFINITY  ((__rlim_t)(~0UL))
//#endif

// #ifndef RLIMIT_MSGQUEUE
//#define RLIMIT_MSGQUEUE 12  // This value may vary by system, adjust if necessary
// #endif

// #ifndef RLIMIT_NOFILE
//#define RLIMIT_NOFILE 7  // This value may vary by system, adjust if necessary
// #endif


// Declare setrlimit and getrlimit for FFI
extern int setrlimit(__rlimit_resource_t resource, const struct rlimit *rlim);
extern int getrlimit(__rlimit_resource_t resource, struct rlimit *rlim);

// These are typically already declared in standard headers, but if you need them explicitly:
extern int errno;
extern char *strerror(int errnum);

// // These function declarations are usually in <sys/resource.h>
// // If they're not, keep these lines:
// extern int setrlimit(int resource, const struct rlimit *rlim);
// extern int getrlimit(int resource, struct rlimit *rlim);


// void _c2php_const(const char *name, long value);

// void c2php_libphphi_consts();





#endif // LIBPHPHI_H



// // #define RLIM_INFINITY;
// // #define RLIMIT_MSGQUEUE;
// // #define RLIMIT_NOFILE;

// // #define O_RDONLY    00
// // #define O_WRONLY    01
// // #define O_RDWR      02
// // #define O_CREAT   0100
// // #define O_EXCL    0200
// // #define O_NONBLOCK 04000

//     const O_RDONLY    = 0x00;
//     const O_WRONLY    = 0x01;
//     const O_RDWR      = 0x02;
//     const O_CREAT     = 0x40;
//     const O_EXCL      = 0x80;
//     const O_NONBLOCK  = 0x800;

//     const SIGRTMIN = 34;
//     const SIG_BLOCK = 0;
//     const SIGEV_SIGNAL = 0;

//     const S_IRUSR = 256;
//     const S_IWUSR = 128;
// #define RLIM_INFINITY;
// #define RLIMIT_MSGQUEUE;
// #define RLIMIT_NOFILE;


// #define O_RDONLY    00
// #define O_WRONLY    01
// #define O_RDWR      02
// #define O_CREAT   0100
// #define O_EXCL    0200
// #define O_NONBLOCK 04000




// #define FFI_SCOPE "zsl\\libphphi"

// //#define FFI_SCOPE "Rindow\\OpenCL\\FFI"
// //#define FFI_LIB "OpenCL.DLL"


// #ifndef LIBPHPHI_H
// #define LIBPHPHI_H

// #include <dlfcn.h>
// #include <errno.h>
// #include <fcntl.h>
// #include <stdint.h>
// #include <string.h>
// #include <stdlib.h>
// #include <sys/resource.h>
// #include <sys/types.h>
// #include <sys/stat.h>





// typedef unsigned long rlim_t;

// struct rlimit {
//     rlim_t rlim_cur;
//     rlim_t rlim_max;
// };

// extern int errno;
// char *strerror(int errnum);

// int setrlimit(int resource, const struct rlimit *rlim);
// int getrlimit(int resource, struct rlimit *rlim);


// // void *memcpy(void *dest, const void *src, size_t n);























// // #include <string.h>
// // #include <limits.h>
// // #include <sys/resource.h>
// // #include <fcntl.h>
// // #include <stdint.h>
// // #include <errno.h>
// // #include <sys/types.h>
// // #include <sys/stat.h>
// // #include <dlfcn.h>
// // #include <string.h>


// // typedef unsigned long rlim_t;
// // typedef __rlimit_resource_t __rlimit_resource_t;
// // // typedef rlimit rlimit;

// // extern int errno;
// // char *strerror(int errnum);

// // // struct rlimit {
// // //     rlim_t rlim_cur;
// // //     rlim_t rlim_max;
// // // };

// // int setrlimit(__rlimit_resource_t resource, const struct rlimit *rlim);
// // int getrlimit(__rlimit_resource_t resource, struct rlimit *rlim);

// // // int setrlimit(int resource, const struct rlimit *rlim);
// // // int getrlimit(int resource, struct rlimit *rlim);





// #endif  // LIBPHPHI_H
