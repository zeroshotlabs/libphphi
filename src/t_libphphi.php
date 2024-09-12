<?php declare(strict_types=1);
namespace zeroshotlabs\libphphi;


use \Exception;
use \FFI;
use \FFI\CData as cdata;


trait libphphi
{
    const O_RDONLY    = 0x00;
    const O_WRONLY    = 0x01;
    const O_RDWR      = 0x02;
    const O_CREAT     = 0x40;
    const O_EXCL      = 0x80;
    const O_NONBLOCK  = 0x800;

    const SIGRTMIN = 34;
    const SIG_BLOCK = 0;
    const SIGEV_SIGNAL = 0;

    const S_IRUSR = 256;
    const S_IWUSR = 128;

    public ?ffi $ffi = null;

    public string $libphphi_so = '';
    /* void c2php(void); */


    // @todo secondary load_so()?
    // generally a module will have libphphi linked so this shouldn't be needed
    function _phphi_init(): bool
    {
        if( empty($this->libphphi_so) )
            $this->libphphi_so = LIBPHPHI_ROOT."/lib/libphphi.so";

        if( !is_readable($this->libphphi_so))
            throw new Exception("libphphi.so not readable from '".$this->libphphi_so."'");

        if( defined('_DEBUG') )
            $this->show_limits();

        return true;
    }

    public function set_consts()
    {
        if( empty($this->ffi) )
            $this->ffi_init();

        $this->ffi->c2php_common_consts();
    }

    public function zerod( cdata $ffi_struct,int $size = 0 ): void
    {
        FFI::memset($ffi_struct, 0, $size>0?$size:(FFI::sizeof($ffi_struct)));
    }

    public function to_eights( int $num ): int
    {
        return intval(ceil($num / 8) * 8);
    }

    public function errno(): int
    {
        return FFI::addr($this->ffi->errno)[0]??0;
    }

    public function strerror( int $errno = 0 ): string
    {
        $errno = $errno===0?$this->ffi->errno():$errno;
        $strerror = $this->ffi->strerror($errno);

        return "ERROR ($errno): ".FFI::string($strerror);
    }

    // not fully tested - not used
    public function ch_sysctl( string $path, int $value ): bool
    {
        if( stripos($path, 'size') !== false  )
            $paths = ['/proc/sys/fs/mqueue/msgsize_default','/proc/sys/fs/mqueue/msgsize_max'];
        else if( stripos($path, 'count') !== false )
            $paths = ['/proc/sys/fs/mqueue/msg_default','/proc/sys/fs/mqueue/msg_max'];
        else
            throw new Exception("Invalid ch_sysctl: $path");

        foreach( $paths as $p )
        {
            $result = file_put_contents($p, $value);
    
            if( !$result )
                throw new Exception("Failed to write sysctl '$value' to $p");
        }

        return true;
    }

    public function show_limits( $ret = false ): string|null
    {
        $buf = "\n\n==== Limits for PID ".posix_getpid().
               "\n\n".file_get_contents('/proc/self/limits').
               "\n\n Soft/Hard limit open files ".(RLIMIT_NOFILE).": ".trim(shell_exec("ulimit -Sn")).' / '.trim(shell_exec("ulimit -Hn")).
               "\n\n    Soft/Hard limit mqueue ".(RLIMIT_MSGQUEUE).": ".trim(shell_exec("ulimit -Sq")).' / '.trim(shell_exec("ulimit -Hq"));

        return plog($buf,$ret);        
    }

    // 7
    public function max_filedes( float $limit ): bool
    {
        if( defined('_DEBUG') )
            plog("RLIMIT_NOFILE as ".RLIMIT_NOFILE." setting at {$limit}");

        return $this->_set_rlimit(RLIMIT_NOFILE,$limit);
    }

    // 12
    public function max_msgq( float $limit ): bool
    {
        if( defined('_DEBUG') )
            plog("RLIMIT_MSGQUEUE as ".RLIMIT_MSGQUEUE." setting at {$limit}");

        return $this->_set_rlimit(RLIMIT_MSGQUEUE,$limit);
    }
    
    // infinity may not work
    public function _set_rlimit( int $limit_type,float $limit = RLIM_INFINITY ): bool
    {
        if( empty($this->ffi) )
            $this->ffi_init();

        $rlimit = $this->ffi->new("struct rlimit");

        if( !in_array($limit_type,[RLIMIT_NOFILE,RLIMIT_MSGQUEUE],true) )
            throw new Exception("Unknown limit type {$limit_type}");

        $this->ffi->getrlimit($limit_type,FFI::addr($rlimit));

        $before = implode(" / ",[(float) $rlimit->rlim_cur,(float)$rlimit->rlim_max]);

        $rlimit->rlim_cur = $limit;
        $rlimit->rlim_max = $limit;

        $result = $this->ffi->setrlimit($limit_type,FFI::addr($rlimit));

        if( $result < 0 )
            throw new Exception("Failed to set rlimit '$limit_type' to $limit: " .$this->strerror());

        $this->zerod($rlimit);

        $result = $this->ffi->getrlimit($limit_type,FFI::addr($rlimit));
        $after = implode(" / ",[(float) $rlimit->rlim_cur,(float)$rlimit->rlim_max]);

        plog("RLIMIT {$limit_type} changed from {$before} => {$after}");

        return true;
    }
}

