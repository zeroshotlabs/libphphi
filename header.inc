<?php declare(strict_types=1);
namespace zsl\libphphi;

define('LIBPHPHI_ROOT',__DIR__.'/');

require('src/t_libphphi.php');


use \FFI as ffi;

// interface c2php
// {
//     public function _set_consts();
// }


abstract class c2base
// implements c2php
{
    public ?ffi $ffi = null;

    use t_libphphi;

    public function __construct( )
    {
        $this->ffi = ffi::cdef(file_get_contents(LIBPHPHI_ROOT.'ext/libphphi.h'),
                                                 LIBPHPHI_ROOT.'lib/libphphi.so');
    }
}

    // public function __construct()
    // {
    //     $this->ffi = ffi::cdef("
    //         int O_RDONLY;
    //         int O_WRONLY;
    //         int O_RDWR;
    //         int O_CREAT;
    //         int O_EXCL;
    //         int O_NONBLOCK;

    //         int SIGRTMIN;
    //         int SIG_BLOCK;
    //         int SIGEV_SIGNAL;

    //         int S_IRUSR;
    //         int S_IWUSR;
    //     ", "lib/libphphi.so");
    // }
    
    // public function _set_consts()
    // {

    // }


    // const O_RDONLY = 0;
    // const O_WRONLY = 1;
    // const O_RDWR = 2;
    // const O_ACCMODE = 3;
    // const O_CREAT = 0x40;
    // const O_EXCL = 0x80;
    // const O_NOCTTY = 0x100;
    // const O_TRUNC = 0x200;
    // const O_APPEND = 0x400;
    // const O_NONBLOCK = 0x800;
    // const O_RSYNC = 0x1000;
    // const O_SYNC = 0x101000;
    // const O_DSYNC = 0x1000;
    // const O_FSYNC = 0x101000;
    // const O_ASYNC = 0x2000;
    // const O_DIRECT = 0x4000;
    // const O_LARGEFILE = 0x8000;
    // const O_DIRECTORY = 0x10000;



    
    
// array_walk($recv_k, fn($v) => fwrite($all_log,"\nK: ".implode('-',$v)));
// if $out is true, log string is returned, otherwise to file
// has to be called at least once with log file
function plog( $msg,string|bool $out = 'all_out.log' )
{
    static $logfp = null;

    $bt = debug_backtrace(DEBUG_BACKTRACE_IGNORE_ARGS);

    if( $bt[1]['file']??false )
        $caller = [pathinfo($bt[1]['file'], PATHINFO_FILENAME),$bt[1]['line']];
    else if( $bt[2]['file']??false )
        $caller = [pathinfo($bt[2]['file'], PATHINFO_FILENAME),$bt[2]['line']];
    else
        $caller = [pathinfo(strtr($bt[1]['class']??array_pop($bt[0]),'\\','/'),PATHINFO_FILENAME),$bt[0]['line']??$bt[1]['line']];

    if( !$logfp && is_string($out) )
        $logfp = fopen($out, 'a');
    else if( !$logfp )
        throw new Exception("plog to file called before establishing log file");

    $pid = posix_getpid();

    if( !is_scalar($msg) )
        $msg = "\n=====\n".print_r($msg,true);
    else
        $msg = trim((string) $msg, ' #=');

    if( empty($msg) )
        $msg = ' empty ';

    $buf = sprintf("\n=%6d | {$caller[0]}:{$caller[1]} | %s",$pid,$msg);

    if( $out === true )
        return $buf;
    else
        fwrite($logfp,$buf);
}

