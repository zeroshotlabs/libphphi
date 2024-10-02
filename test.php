<?php
require('header.inc');

use zsl\libphphi\c2base as c2b;

class this_ffi extends c2b {

}

$ffi = FFI::cdef("
    struct rlimit {
        uint64_t rlim_cur;
        uint64_t rlim_max;
    };
    
    int getrlimit(int resource, struct rlimit *rlim);
", "libc.so.6");

$tffi = new this_ffi();


$tffi->show_limits();


$rlimit = $tffi->new("struct rlimit");


$this->ffi->getrlimit(RLIMIT_NOFILE,FFI::addr($rlimit));
var_dump($rlimit);


$this->ffi->getrlimit(RLIMIT_MSGQUEUE,FFI::addr($rlimit));
var_dump($rlimit);

