<?php declare(strict_types=1);
namespace zeroshotlabs\libphphi;

define('LIBPHPHI_ROOT',__DIR__.'/');


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


require('src/t_libphphi.php');
