$rlimit = $this->ffi->new("struct rlimit");

if( !in_array($limit_type,[RLIMIT_NOFILE,RLIMIT_MSGQUEUE],true) )
    throw new Exception("Unknown limit type {$limit_type}");

$this->ffi->getrlimit(RLIMIT_NOFILE,FFI::addr($rlimit));
var_dump($rlimit);
$this->ffi->getrlimit(RLIMIT_MSGQUEUE,FFI::addr($rlimit));
var_dump($rlimit);

