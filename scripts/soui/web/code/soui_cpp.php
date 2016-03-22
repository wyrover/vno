<?php

require_once('php_utils.php');

function soui_control_type($type)
{
  static $ctrl_dicts = array(
    // "window" => "SWindow",
    // "caption" => "SCaption",
    // "group" => "SGroup",
    // "imgbtn" => "SImageButton",
    // "button" => "SButton",
    "text" => "SStatic",
    "edit" => "SEdit",
    "richedit" => "SRichEdit",
    "combobox" => "SComboBox",
    "radio" => "SRadioBox",
    "toggle" => "SToggle",
    "check" => "SCheckBox",
    "img" => "SImageWnd",
    "link" => "SLink",
    "icon" => "SIconWnd",
    "comboboxex" => "SComboBoxEx",
    "header" => "SHeaderCtrl",
    "listbox" => "SListBox",
    "listboxex" => "SListBoxEx",
    "listctrl" => "SListCtrl",
    "slider" => "SSliderBar",
    "splitpane" => "SSplitPane",
    "splitwnd" => "SSplitWnd",
    // "page" => "STabPage",
    "tabctrl" => "STabCtrl",
    "treebox" => "STreeBox",
    "treectrl" => "STreeCtrl",
    "animateimg" => "SAnimateImgWnd"
  );
  if(!isset($ctrl_dicts[$type]) || is_null($type)) 
    return null;
  else
    return $ctrl_dicts[$type];
}

function short_name($type)
{
  static $short_names = array(
    "combobox" => "combox",
    "text" => "label"
  );
  if(!isset($short_names[$type])) {
    return $type;
  }
  else {
    return $short_names[$type];
  }
}

function real_name($name, $type)
{
  //去掉左右两侧的$type表示的字符串
  $name = str_ireplace($type, "", $name);
  //去掉两侧多余的下划线
  $name = trim($name, "_");

  if(preg_match("/^[0-9]+/", $name)) {
    if($type == 'text') 
      return null;
    else
      return short_name($type).$name;
  }
  else {
    return $name."_".short_name($type);
  }
}

function declare_vars_by_name($file, $vars)
{
  foreach ($vars as $name => $type) {
    $ctrl_type = soui_control_type($type);
    if(is_null($ctrl_type)) continue;

    $var_name = real_name($name, $type);
    if(is_null($var_name)) continue;

    $var_name = camel_case($var_name);
    fwrite($file, TAB.$ctrl_type."* m_".$var_name.";".ENTER);
  }
}

function impl_function_onInitDialog($file, $vars)
{
  foreach ($vars as $name => $type) {
    $ctrl_type = soui_control_type($type);
    if(is_null($ctrl_type)) continue;

    $var_name = real_name($name, $type);
    if(is_null($var_name)) continue;

    $var_name = camel_case($var_name);
    fwrite($file, TAB."m_$var_name = FindChildByName2<$ctrl_type>(L".DBL_QUOT.$name.DBL_QUOT.");".ENTER);
  }
}

function msg_map_by_name($file, $vars)
{
  foreach ($vars as $name => $type) {
    // $ctrl_type = soui_control_type($type);
    $var_name = camel_case(real_name($name, $type));

    if($type == 'button') {
      $func_name = "On".$var_name."Click";
      fwrite($file, TWO_TAB."EVENT_NAME_COMMAND(".tchar($name).", $func_name)".ENTER);
    }
    else if($type == 'combobox') {
      $func_name = "On".$var_name."SelChanged";
      fwrite($file, TWO_TAB."EVENT_NAME_HANDLER(".tchar($name).", EVT_CB_SELCHANGE, $func_name)".ENTER);
    }
    else if($type == 'listbox') {
      $func_name = "On".$var_name."SelChanged";
      fwrite($file, TWO_TAB."EVENT_NAME_HANDLER(".tchar($name).", EVT_LB_SELCHANGED, $func_name)".ENTER);
    }
  }
}

function msg_map_by_id($file, $ids)
{
  $nCount = 1;
  foreach ($ids as $id) {
    $min_id = min($id);
    $max_id = max($id);
    $func_name = "OnRadioGroup".$nCount."Switch";
    $nCount = $nCount + 1;
    fwrite($file, TWO_TAB."EVENT_ID_COMMAND_RANGE($min_id, $max_id, $func_name)".ENTER);
  }
}

function make_function($func_name, $params="", $prefix="", $return_type="void")
{
  if($prefix != "" && !is_null($prefix)) {
    $prefix = $prefix."::";
  }
  return "$return_type"." ".$prefix."".$func_name."(".$params.")";
}

function make_function_no_param($func_name, $prefix="", $return_type="void")
{
  return make_function($func_name, "", $prefix, $return_type);
}

function declare_msg_handler_by_name($file, $vars)
{
  foreach ($vars as $name => $type) {
    // $ctrl_type = soui_control_type($type);
    $var_name = camel_case(real_name($name, $type));

    if($type == 'button') {
      $func_name = "On".$var_name."Click";
      $func = make_function_no_param($func_name);
      fwrite($file, TAB."$func;".ENTER);
    }
    else if($type == 'combobox') {
      $func_name = "On".$var_name."SelChanged";
      $func = make_function($func_name, $params="SOUI::EventArgs *pEvt");
      fwrite($file, TAB."$func;".ENTER);
    }
    else if($type == 'listbox') {
      $func_name = "On".$var_name."SelChanged";
      $func = make_function($func_name, $params="SOUI::EventArgs *pEvt");
      fwrite($file, TAB."$func;".ENTER);
    }
  }
}

function declare_msg_handler_by_id($file, $ids)
{
  $nCount = 1;
  foreach ($ids as $id) {
    $func_name = "OnRadioGroup".$nCount."Switch";
    $nCount = $nCount + 1;
    fwrite($file, TAB."void $func_name(int nID);".ENTER);
  }
}

function impl_msg_handler_by_name($file, $vars, $Class)
{
  fwrite($file, ENTER);
  foreach ($vars as $name => $type) {
    // $ctrl_type = soui_control_type($type);
    $var_name = camel_case(real_name($name, $type));

    if($type == 'button') {
      $func_name = "On".$var_name."Click";
      $func = make_function_no_param($func_name, $Class);
      fwrite($file, ENTER."$func".ENTER);
      fwrite($file, "{".ENTER);
      fwrite($file, "}".ENTER);
    }
    else if($type == 'combobox') {
      $func_name = "On".$var_name."SelChanged";
      $func = make_function($func_name, "SOUI::EventArgs *pEvt", $Class);
      fwrite($file, ENTER."$func".ENTER);
      fwrite($file, "{".ENTER);
      fwrite($file, TAB."if(!isLayoutInited()) return;".ENTER);
      fwrite($file, TAB."EventCBSelChange* pEvtOfCB = (EventCBSelChange*)pEvt;".ENTER);
      fwrite($file, TAB."if(pEvtOfCB == 0) return;".ENTER);
      fwrite($file, TAB."int nCurSel = pEvtOfCB->nCurSel;".ENTER);
      fwrite($file, TAB."if(nCurSel == -1) return;".TWO_ENTER);
  
      fwrite($file, TAB."// do something".ENTER);
      fwrite($file, "}".ENTER);
    }
    else if($type == 'listbox') {
      $func_name = "On".$var_name."SelChanged";
      $func = make_function($func_name, "SOUI::EventArgs *pEvt", $Class);
      fwrite($file, ENTER."$func".ENTER);
      fwrite($file, "{".ENTER);
      fwrite($file, TAB."if(!isLayoutInited()) return;".ENTER);
      fwrite($file, TAB."EventLBSelChanged* pEvtOfLB = (EventLBSelChanged*)pEvt;".ENTER);
      fwrite($file, TAB."if(pEvtOfLB == 0) return;".ENTER);
      fwrite($file, TAB."int nCurSel = pEvtOfLB->nNewSel;".ENTER);
      fwrite($file, TAB."if(nCurSel == -1) return;".TWO_ENTER);
  
      fwrite($file, TAB."// do something".ENTER);
      fwrite($file, "}".ENTER);
    }
  }
}

function impl_msg_handler_by_id($file, $ids, $Class)
{
  $nCount = 1;
  foreach ($ids as $id) {
    $func_name = "OnRadioGroup".$nCount."Switch";
    $func = make_function($func_name, "int nID", $Class);
    $nCount = $nCount + 1;
    fwrite($file, ENTER."$func".ENTER);
    fwrite($file, "{".ENTER);
    fwrite($file, TAB."if(!isLayoutInited()) return;".ENTER);
    fwrite($file, "}".ENTER);
  }
}

function dlg_head_file($file, $dlg, $vars, $ids)
{
  $ChildDlg = camel_case($dlg)."Dialog";
  $ParentDlg='AcadSouiDialog';

  fwrite($file, "#pragma once".ENTER);
  fwrite($file, "#include ".DBL_QUOT."$ParentDlg.h".DBL_QUOT.TWO_ENTER);
  fwrite($file, "class $ChildDlg : public $ParentDlg".ENTER);
  fwrite($file, "{".ENTER);
  fwrite($file, ENTER.TAB."/** 构造和析构函数 */".ENTER);
  fwrite($file, "public:".ENTER);
  fwrite($file, TAB."$ChildDlg(BOOL bModal = FALSE);".ENTER);
  fwrite($file, TAB."~$ChildDlg(void);".ENTER);

  fwrite($file, ENTER.TAB."/** 控件消息处理 */".ENTER);
  fwrite($file, "protected:".ENTER);
  declare_msg_handler_by_name($file, $vars);
  declare_msg_handler_by_id($file, $ids);

  fwrite($file, ENTER.TAB."/** 菜单消息 */".ENTER);
  fwrite($file, "protected:".ENTER);
  fwrite($file, TAB."//处理菜单消息(菜单在一个单独的xml文件中描述，每个菜单项都有一个id号)".ENTER);
  fwrite($file, TAB."void OnCommand(UINT uNotifyCode, int nID, HWND wndCtl);".ENTER);


  fwrite($file, ENTER.TAB."/** 窗口消息 */".ENTER);
  fwrite($file, "protected:".ENTER);
  fwrite($file, TAB."//对话框初始化过程".ENTER);
  fwrite($file, TAB."LRESULT OnInitDialog(HWND hWnd, LPARAM lParam);".ENTER);

  fwrite($file, ENTER.TAB."//控件消息映射表".ENTER);
  fwrite($file, TAB."EVENT_MAP_BEGIN()".ENTER);
  //控件消息映射声明
  msg_map_by_name($file, $vars);
  msg_map_by_id($file, $ids);
  fwrite($file, TWO_TAB."CHAIN_EVENT_MAP($ParentDlg)".ENTER);
  fwrite($file, TAB."EVENT_MAP_END()".ENTER);

  fwrite($file, TAB.ENTER."//HOST消息(WINDOWS消息)映射表".ENTER);
  fwrite($file, TAB."BEGIN_MSG_MAP_EX($ChildDlg)".ENTER);
  fwrite($file, TWO_TAB."MSG_WM_INITDIALOG(OnInitDialog)".ENTER);  
  fwrite($file, TWO_TAB."MSG_WM_COMMAND(OnCommand)".ENTER);
  fwrite($file, TWO_TAB."CHAIN_MSG_MAP($ParentDlg)".ENTER);
  fwrite($file, TWO_TAB."REFLECT_NOTIFICATIONS_EX()".ENTER);
  fwrite($file, TAB."END_MSG_MAP()".TWO_ENTER);

  //变量声明
  fwrite($file, "protected:".ENTER);
  declare_vars_by_name($file, $vars);

  fwrite($file, "};".ENTER);

}

function dlg_cpp_file($file, $dlg, $vars, $ids)
{
  $ChildDlg = camel_case($dlg)."Dialog";
  $ParentDlg='AcadSouiDialog';

  fwrite($file, "#include ".DBL_QUOT."stdafx.h".DBL_QUOT.ENTER);
  fwrite($file, "#include ".DBL_QUOT."$ChildDlg.h".DBL_QUOT.ENTER);

  fwrite($file, ENTER."#include <ArxHelper/HelperClass.h>".ENTER);
  fwrite($file, "#include <Dao/DaoHelper.h>".ENTER);
  fwrite($file, "#include <Dao/Entity.h>".ENTER);
  fwrite($file, "using namespace orm;".ENTER);
  fwrite($file, "using namespace cbm;".ENTER);

  //构造函数
  fwrite($file, ENTER."$ChildDlg::$ChildDlg(BOOL bModal) : $ParentDlg(".tchar("layout:$dlg").", bModal)".ENTER);
  fwrite($file, "{".ENTER);
  fwrite($file, "}".ENTER);
  //析构函数
  fwrite($file, ENTER."$ChildDlg::~$ChildDlg()".ENTER);
  fwrite($file, "{".ENTER);
  fwrite($file, "}".ENTER);

  //OnCommand函数
  fwrite($file, ENTER."void $ChildDlg::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )".ENTER);
  fwrite($file, "{".ENTER);
  fwrite($file, TAB."if(uNotifyCode==0)".ENTER);
  fwrite($file, TAB."{".ENTER);
  fwrite($file, TWO_TAB."//if(nID==6)".ENTER);
  fwrite($file, TWO_TAB."//{".ENTER);
  fwrite($file, TWO_TAB."//}".ENTER);
  fwrite($file, TAB."}".ENTER);
  fwrite($file, "}".ENTER);

  //OnInitDialog函数
  fwrite($file, ENTER."LRESULT $ChildDlg::OnInitDialog( HWND hWnd, LPARAM lParam )".ENTER);
  fwrite($file, "{".ENTER);
  fwrite($file, TAB."$ParentDlg::OnInitDialog(hWnd, lParam);".ENTER);
  fwrite($file, TAB."//do something".ENTER);
  //变量定义
  impl_function_onInitDialog($file, $vars);
  fwrite($file, TAB."return 0;".ENTER);
  fwrite($file, "}".ENTER);

  //消息映射函数实现
  impl_msg_handler_by_name($file, $vars, $ChildDlg);
  impl_msg_handler_by_id($file, $ids, $ChildDlg);
}

function dlg_file($dir, $dlg, $vars, $ids)
{
  $ChildDlg = camel_case($dlg)."Dialog";

  //生成头文件
  $file = fopen($dir."/"."$ChildDlg.h", "w");
  dlg_head_file($file, $dlg, $vars, $ids);
  fclose($file);

  //生成源文件
  $file = fopen($dir."/"."$ChildDlg.cpp", "w");
  dlg_cpp_file($file, $dlg, $vars, $ids);
  fclose($file);
}

function walk_xml_tree($root, &$vars, &$ids) 
{
  $node_ids = array();
   foreach ($root->childNodes as $node) {
    if($node->nodeType == XML_TEXT_NODE) continue;

    $type = $node->nodeName;
    $name = $node->getAttribute('name');
    //过滤掉<text>控件
    // if($type == 'text') continue;

    echo "$name --> $type"."<br/>";
    $vars[$name] = $type;

    if($type == 'radio') {
      $id = $node->getAttribute('id');
      if(!is_null($id)) {
        $node_ids[] = intval($id);
      }
    }
    if($type == 'window' || $type == 'group') {
      walk_xml_tree($node, $vars, $ids);
    }
   }
   //至少要2个radio
   if(count($node_ids) > 1) {
    $ids[] = $node_ids;
   }
   else {
    unset($node_ids);
   }
}

function xml_to_vars($xmlfile)
{
  //记录所有的变量
  $vars = array();
  //记录所有radio的id
  $ids = array();

  //创建一个XML文档并设置XML版本和编码
  $doc = new DomDocument();
  $doc->preserveWhiteSpace = false;
  $doc->load($xmlfile);
  // $doc->formatOutput = true;
  //xml输出的时候要加上编码,否则输出的中文变成一堆奇怪的符号
  $doc->encoding = 'UTF-8';

  $root = $doc->getElementsByTagName('root')->item(0);
  walk_xml_tree($root, $vars, $ids);
   return array($vars, $ids);
}

function dlg_file_gbk_encoding($dir, $dlg)
{
  $ChildDlg = camel_case($dlg)."Dialog";
  gbk_encoding($dir."/"."$ChildDlg.h");
  gbk_encoding($dir."/"."$ChildDlg.cpp");
}

function xml_to_dialog($xmlDir, $cppDir)
{
  // rmdirs($cppDir);
  // mkdirs($cppDir);

  //获取本文件目录的文件夹地址
  $filesnames = scanfiles($xmlDir);
  //获取也就是扫描文件夹内的文件及文件夹名存入数组 $filesnames
  foreach ($filesnames as $name) {
    if($name == '.' || $name == '..') continue;

    //得到没有扩展名的文件名
    $fname = pathinfo($name)['filename'];
    $ext = pathinfo($name)['extension'];
    if($ext != 'xml') continue;
    if($fname == 'init') continue;

    //拼接xml文件名
    $xmlfile = $xmlDir.'/'.$fname.'.xml';
    echo $xmlfile."<br/>";

    //解析得到所有的变量
    $ret = xml_to_vars($xmlfile);
    $vars = $ret[0];
    $ids = $ret[1];
    // var_dump($ids);
    //生成c++代码
    dlg_file($cppDir, $fname, $vars, $ids);
    //编码转换(转为gbk)
    dlg_file_gbk_encoding($cppDir, $fname);
  }
}

//扫描文件夹,并将文件进行编码转换
function xxxx($dir)
{
 //获取本文件目录的文件夹地址
  $filesnames = scanfiles($dir);
  //获取也就是扫描文件夹内的文件及文件夹名存入数组 $filesnames
  foreach ($filesnames as $name) {
    if($name == '.' || $name == '..') continue;
    //编码转换
    gbk_encoding($name);
  }
}
// xxxx('C:\Users\dlj\Desktop\cbm\cbm\ArxSoUI\uires\xml');
// xml_to_dialog('xml', 'cpp');
// recurse_copy('cpp', 'C:\Develop\GitProject\cbm\ArxSoUI');

?>