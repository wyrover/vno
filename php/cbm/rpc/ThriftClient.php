<?php
 
namespace ThriftClient;

require_once __DIR__.'/../Thrift/ClassLoader/ThriftClassLoader.php';

use Thrift\ClassLoader\ThriftClassLoader;
 
$GEN_DIR = realpath(dirname(__FILE__)).'/gen-php';

$loader = new ThriftClassLoader();
$loader->registerNamespace('Thrift', __DIR__.'/..');
$loader->registerDefinition('cbm', $GEN_DIR);
$loader->registerDefinition('ctrl', $GEN_DIR);
$loader->register();
 
use Thrift\Protocol\TBinaryProtocol;
use Thrift\Transport\TSocket;
// use Thrift\Transport\THttpClient;
use Thrift\Transport\TBufferedTransport;
use Thrift\Exception\TException;

// require_once __DIR__.'/gen-php/cbm/CbmService.php';
// require_once __DIR__.'/gen-php/cbm/Types.php';
 
 define('HOST', 'localhost');
 define('PORT1', 9100);
 define('PORT2', 9090);

class ThriftClient {
 
    public $client;
    private $transport;
    private $protocol;
    private $client_class;
    private $server_ip;
    private $server_port;
    private $socket;
 
    function __construct($client_class, $server_ip=HOST, $server_port=PORT2) {
        $this->client_class = $client_class;
        $this->server_ip = $server_ip;
        $this->server_port = $server_port;
    }
 
    function __destruct() {
        $this->transport->close();
    }
 
    public function getClient() {
        $this->socket = new TSocket($this->server_ip, $this->server_port);
        $this->transport = new TBufferedTransport($this->socket, 1024, 1024);
        $this->protocol = new TBinaryProtocol($this->transport);
        $this->client = new $this->client_class($this->protocol);
        $this->transport->open();
        return $this->client;
    }
}

?>