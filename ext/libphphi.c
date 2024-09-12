#define _GNU_SOURCE
#include "libphphi.h"
#include "zend.h"
#include "php.h"

int setrlimit(__rlimit_resource_t resource, const struct rlimit *rlim);
int getrlimit(__rlimit_resource_t resource, struct rlimit *rlim);

// int setrlimit(int resource, const struct rlimit *rlim);
// int getrlimit(int resource, struct rlimit *rlim);


/* void c2php(void); */

void c2php_const(const char *name, long value)
{
    zend_register_long_constant(name, strlen(name), value, CONST_CS | CONST_PERSISTENT, 0);
}


void c2php_common_consts()
{
    c2php_const("RLIM_INFINITY", RLIM_INFINITY);
    c2php_const("RLIMIT_MSGQUEUE", RLIMIT_MSGQUEUE);
    c2php_const("RLIMIT_NOFILE", RLIMIT_NOFILE);
    c2php_const("O_RDONLY", O_RDONLY);
    c2php_const("O_WRONLY", O_WRONLY);
    c2php_const("O_RDWR", O_RDWR);
    c2php_const("O_CREAT", O_CREAT);
    c2php_const("O_EXCL", O_EXCL);
    c2php_const("O_NONBLOCK", O_NONBLOCK);
}

