<?php

//带双引号的逗号
define ('COMMA', "\",\"");
define ('SEMICOLON', "\";\"");
define ('STREAM', "<<");
define ('DBL_QUOT', "\"");
define ('SINGLE_QUOT', "\"'\"");
define ('ENTER', "\r\n");
define ('TWO_ENTER', "\r\n\r\n");
define ('THREE_ENTER', "\r\n\r\n\r\n");
define ('TAB', "\t");
define ('TWO_TAB', "\t\t");
define ('THREE_TAB', "\t\t\t");
define ('FOUR_TAB', "\t\t\t\t");
define ("ID_SUBFIX", "_id");
define ('VC_PRECOM', TRUE);
define ('DLL_EXPORT', " ARXDAO_DLLIMPEXP ");
//define ('DLL_EXPORT', " ");

function tchar($str)
{
    return '_T('.DBL_QUOT.$str.DBL_QUOT.')';
}
//创建多级目录(递归)
function mkdirs($dir)
{
    if(!is_dir($dir)) {
        if(!mkdirs(dirname($dir))) {
            return false;
        }
        if(!mkdir($dir, 0777)) {
            return false;
        }
    }
    return true;  
}

//mkdirs('div/css/layout');

//用rmdir和unlink递归删除多级目录
function rmdirs($dir)  
{
    if(!is_dir($dir)) return;

    $d = dir($dir);  
    while (false !== ($child = $d->read())) {
        if($child != '.' && $child != '..') {
            if(is_dir($dir.'/'.$child)) {
                rmdirs($dir.'/'.$child);
            }
            else {
                unlink($dir.'/'.$child);
            }
        }
    }
    $d->close();
    rmdir($dir);
}

function camel_case($name)
{
	return str_replace(" ", "", ucwords(str_replace("_", " ", $name)));
}

//echo camel_case("cbm_adj_layer");

function cpp_type($type)
{
	//static $fields_dict = array("NEWDECIMAL" => "double", "LONG"=>"long", "VAR_STRING"=>"std::string", "LONGLONG"=>"long", "INT"=>"int");
    static $fields_dict = array("NEWDECIMAL" => "double", "LONG"=>"int", "VAR_STRING"=>"CString", "LONGLONG"=>"long", "INT"=>"int");
	return $fields_dict[$type];
}

function type_default($type)
{
    //static $default_value_dict = array("int"=>"0", "double"=>"0.0", "long"=>"0", "std::string"=>"\"NULL\"", "string"=>"\"NULL\"", "float"=>"0.0f");
    static $default_value_dict = array("int"=>"0", "double"=>"0.0", "long"=>"0", "CString"=>"_T(\"\")", "float"=>"0.0f");
    return $default_value_dict[$type];
}

function h_type2txt($type_id)
{
    static $types;

    if (!isset($types)) {
        $types = array();
        $constants = get_defined_constants(true);
        foreach ($constants["mysqli"] as $c => $n) {
        	if (preg_match("/^MYSQLI_TYPE_(.*)/", $c, $m)) $types[$n] = $m[1];
        }
    }

    // var_dump($types);
    return array_key_exists($type_id, $types)? $types[$type_id] : NULL;
}

function h_flags2txt($flags_num)
{
    static $flags;

    if (!isset($flags)) {
        $flags = array();
        $constants = get_defined_constants(true);
        foreach ($constants["mysqli"] as $c => $n) {
        	if (preg_match("/MYSQLI_(.*)_FLAG$/", $c, $m)) if (!array_key_exists($n, $flags)) $flags[$n] = $m[1];
        }
    }

    $result = array();
    foreach ($flags as $n => $t) if ($flags_num & $n) $result[] = $t;
    return implode(" ", $result);
}

function table_no_prefix($name)
{
    $size = strlen("cbm_");
    $cbm = substr($name, 0, $size);
    // var_dump($cbm);
	$tbl_name = substr($name, $size, strlen($name)-$size);
    return ($cbm=='cbm_')?$tbl_name:$name;
}

function table_id($name)
{
	return table_no_prefix($name).ID_SUBFIX;
}

function table_no_id($name)
{
    $size = strlen(ID_SUBFIX);
	$id = substr($name, -1*$size);
	$tbl_name = substr($name, 0, -1*$size);
	return ($id == ID_SUBFIX)?$tbl_name:$name;
}

function obj_prefix($obj_name="")
{
	$prefix = $obj_name.".";
	if($obj_name == "" || $obj_name == "this") {
		$prefix = "(*this).";
	}
	return $prefix;
}

/*
参考资料:
(1)在线json工具,用起来还不错
http://www.qqe2.com/
(2)4种生成xml文件的方法
http://www.oschina.net/code/snippet_110138_4727
http://my.oschina.net/zhangb081511/blog/160113
(3)php的json解析方法
http://www.php.net/json_decode
(4)DomDocument使用方法
http://my.oschina.net/zhangb081511/blog/160113
(5))PHP中用json_decode()无法解析有换行符的字符串
http://www.thinkful.cn/archives/233.html
(6)\u编码的中文转换问题
http://www.csdn123.com/html/2013/fuwuqiduanjiaoben_0822/422108.html
(7)PHP官网手册(每个页面的例子都非常丰富全面)
http://www.php.net/manual
(8)php超好用的文件及文件夹复制函数recurse_copy
http://www.12345t.com/code/php/20140525/315.html
*/

function recurse_copy( $src, $dst )   // 原目录，复制到的目录
{
  $handle = opendir( $src );
  @mkdir( $dst );
  while( false !== ( $file = readdir( $handle ) ) ) 
  {
    if( ( $file != '.' ) && ( $file != '..' ) ) 
    {
      if( is_dir( $src . '/' . $file ) )
      {
        recurse_copy( $src . '/' . $file, $dst . '/' . $file );
      }
      else 
      {
        copy( $src . '/' . $file, $dst . '/' . $file );
      }
    }
  }
  closedir( $handle );
}

//PHP 非递归实现查询该目录下所有文件(包括子文件夹)
function scanfiles1($dir) 
{
  if (! is_dir ( $dir ))
    return array ();
  
  // 兼容各操作系统
  $dir = rtrim ( str_replace ( '/', '\\', $dir ), '\\' ) . '\\';
  // 栈，默认值为传入的目录
  $dirs = array ( $dir );
  // 放置所有文件的容器
  $rt = array ();
  do {
    // 弹栈
    $dir = array_pop ( $dirs );
    // 扫描该目录
    $tmp = scandir ( $dir );
    foreach ( $tmp as $f ) {
      // 过滤. ..
      if ($f == '.' || $f == '..') continue;
      // 组合当前绝对路径(全小写)
      $path = strtolower($dir . $f);
      // 如果是目录，压栈。
      if (is_dir ( $path )) {
        array_push ( $dirs, $path . '\\' );
      } 
      else if (is_file ( $path )) { 
        // 如果是文件，放入容器中
        $rt [] = $path;
      }
    }
  } while ( $dirs ); // 直到栈中没有目录
  return $rt;
}

function scanfiles2($dir)
{
  $filesnames = scandir($dir);
  $rt = array();
  foreach ($filesnames as $name) {
    if($name == '.' || $name == '..') continue;
    if(is_dir($dir.'\\'.$name)) continue;

    $rt[] = $dir.'\\'.$name;
  }
  return $rt;
}

function scanfiles($dir, $bDfs = false)
{
  if($bDfs) {
    return scanfiles1($dir);
  }
  else {
    return scanfiles2($dir);
  }
}

//var_dump(scanfiles('C:/Develop/GitProject/cbm/ThirdParty/soui/mfc_test'));

function decode_json($str, $assoc=true){
  $str = str_replace("\\", '\\\\', $str);
  $str = str_replace("\r\n", '\n', $str);
  return json_decode($str, $assoc);
}

function escapeJsonString($value) 
{ 
  static $escapers = array("\\", "/", "\"", "\n", "\r", "\t", "\x08", "\x0c");
  static $replacements = array("\\\\", "\\/", "\\\"", "\\n", "\\r", "\\t", "\\f", "\\b");
  $result = str_replace($escapers, $replacements, $value);
  return $result;
}

function escapeUnicodeString($value)
{
  if(is_string($value)) {

    return json_decode('"'.$value.'"');
  }
  else {
    return $value;
  }
}

 /**
* 检测文件编码
 * @param string $file 文件路径
* @return string|null 返回 编码名 或 null
*/
 function detect_encoding($file) {
     $list = array('ASCII', 'GB2312', 'GBK', 'UTF-8', 'UTF-16LE', 'UTF-16BE', 'ISO-8859-1');
     $str = file_get_contents($file);
     foreach ($list as $item) {
         $tmp = mb_convert_encoding($str, $item, $item);
         if (md5($tmp) == md5($str)) {
             return $item;
         }
     }
     return null;
}

function gbk_encoding($fname)
{
  //探测编码
  $encoding1 = detect_encoding($fname);
  var_dump('文件'.$fname.'编码:'.$encoding1);
  if(strcasecmp($encoding1, 'GB2312') == 0) return;

  $encoding2 = 'GB2312';
  //编码转换
  $str = file_get_contents($fname);
  $str = iconv($encoding1, $encoding2, $str);
  file_put_contents($fname, $str);
}

?>
