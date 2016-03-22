<?php
 
error_reporting(E_ALL);
 
require_once __DIR__.'/rpc/CbmClientHelper.php';
require_once __DIR__.'/rpc/SQLClientHelper.php';

echo \CbmClientHelper\VerifyMineAccount('dlj', '123');
var_dump(\SQLClientHelper\GetMineBaseNames());
var_dump(\CbmClientHelper\GetMineRegionsOfBase('神东基地'));

\CbmClientHelper\SendCommandToCAD('regen', false);
echo \CbmClientHelper\GetJsonDatasFromCAD("{}", 2);

?>