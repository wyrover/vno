<pre>

  <?php

require_once('php_utils.php');
require_once('soui_cpp.php');

function mockups_type_to_soui_type($type)
{
  static $soui_type_dicts = array(
    'TextInput' => 'edit',
    'Label' => 'text',
    'Button' => 'button',
    'ComboBox'=> 'combobox',
    'CheckBox' => 'check',
    'RadioButton' => 'radio',
    'Image' => "img",
    'Link' => 'link',
    'TextArea' => 'richedit',
    'Paragraph' => 'richedit',
    'List' => 'listbox',
    'HSlider' => 'sliderbar',
    'VSlider' => 'sliderbar',
    'ProgressBar' => 'progress',
    'HRule' => 'hr',
    'VRule' => 'hr',
    'DataGrid' => 'listctrl',
    'TabBar' => 'tabctrl',
    'VerticalTabBar' => 'tabctrl',
    'Tree' => 'treectrl',
    'FieldSet' => 'group',
    'Canvas' => 'window',
    'ButtonBar' => 'caption',
    'LinkBar' => 'caption'
    );

  if(isset($soui_type_dicts[$type])) {
    return $soui_type_dicts[$type];
  }
  else {
    return 'unknown'; // 未知控件或暂不支持的控件
  }
}

//美化xml输出
//如果在mockups_to_soui_xml函数中直接用$doc->save()保存xml文件,效果非常的差
//但又折腾一次之后居然就给美化了,奇怪！！！
function prettyXml($xml_src, $xmlfile) 
{
  $doc = new DOMDocument('1.0');
  $doc->preserveWhiteSpace = false;
  //$dom->loadXML($simpleXml->asXML());
  $doc->loadXML($xml_src);
  $doc->formatOutput = true;
  echo htmlspecialchars($doc->saveXML())."<br/><br/>";
  $doc->save($xmlfile);
}

function prettyXmlSrc($xml_src) 
{
  if($xml_src == '') return '';

  $doc = new DOMDocument('1.0');
  $doc->preserveWhiteSpace = false;
  //$dom->loadXML($simpleXml->asXML());
  $doc->loadXML($xml_src);
  $doc->formatOutput = true;
  return $doc->saveXML();
}

function create_node($doc, $name, $text, $attribs) 
{
  $text = htmlspecialchars($text);
  $node = $doc->createElement($name, $text);
  if(!is_null($attribs) && is_array($attribs)) {
    foreach($attribs as $key => $value) {
      $node->setAttribute( strval($key), strval($value));
    }
  }
  return $node;
}

function xml_append_child($parentNode, $childNode)
{
  if($childNode == null) return;
  $parentNode->appendChild($childNode);
}

function xml_append_child_by_string($parentNode, $xml_src)
{
  if(is_null($xml_src) || $xml_src == '') return;
  
  $new_doc = new DOMDocument('1.0');
  // $new_doc->preserveWhiteSpace = false;
  $new_doc->loadXML($xml_src);
  // $new_doc->formatOutput = true;

  //查找<include>标签
  $incNode = $new_doc->getElementsByTagName('include')->item(0);

  //通过节点获取所属的文档对象
  $doc = $parentNode->ownerDocument;
  foreach($incNode->childNodes as $childNode) {
    //另一个文档中的子节点要导入该文档中才能使用!!!
    $cloneNode = $doc->importNode($childNode, true);
    $parentNode->appendChild($cloneNode);
  }
}

function create_subtree($doc, $tree)
{
  if(!isset($tree['node'])) return null;

  $text = escapeUnicodeString($tree['node']);
  $parentNode = create_node($doc, 'item', null, array('text'=>$text, 'expand'=>1));
  if(isset($tree['children'])) {
    $childNoderen = $tree['children'];
    foreach ($childNoderen as $childNode) {
      $childNode = create_subtree($doc, $childNode);
      if(!is_null($childNode)) {
        $parentNode->appendChild($childNode);
      }
    }  
  }
  return $parentNode;
}

function createIncNode($doc, $node, $jsonfile)
{
  if(!is_file($jsonfile)) return;

  //解析json文件
  $xml_src = mockups_to_soui_xml($jsonfile, false);
  $xml_src = prettyXmlSrc($xml_src);
  echo htmlspecialchars($xml_src)."<br/><br/>";
  if(is_null($xml_src) || $xml_src == '') {
    $fname = pathinfo($jsonfile)['filename'];
    $node->appendChild(create_node($doc, 'include', null, array("src"=>"layout:$fname", "json"=>$jsonfile)));
  }
  else {
    //添加到<group> <window>等容器节点下
    xml_append_child_by_string($node, $xml_src); 
  }
}

//后处理:给某些soui控件附加一些基本属性
function postProcess($doc, $node, $type)
{
  //设置边界属性
  $node->setAttribute('margin-x', '1');
  $node->setAttribute('margin-y', '1');
  // $node->setAttribute('ncSkin', '_skin.sys.border');

  if($type == 'listbox') {
    $node->setAttribute('ncSkin', '_skin.sys.border');
    //删除标签的文本值
    $text = $node->nodeValue;
    $node->nodeValue = '';
    //拆分节点上的文本值并转换成listbox需要的item
    $items = explode('\n', $text);
    $comboItemsNode = $doc->createElement('items');
    foreach ($items as $item) {
      $comboItemsNode->appendChild(create_node($doc, 'item', null, array('text'=>$item)));
    }
    $node->appendChild($comboItemsNode);
  }
  else if($type == 'combobox') {
    $node->setAttribute('ncSkin', '_skin.sys.border');
    //取出combobox属性的数据进行解析,得到标题信息
    $text = $node->getAttribute('value');
    //删除combobox属性和combobox的节点文本值
    $node->removeAttribute("value");
    $node->nodeValue = '';

    //定义liststyle,否则combobox显示黑乎乎的一片
    $listStyleNode = create_node($doc, 'liststyle', null, array('itemHeight'=>"30", 'colorText'=>"#000000", 'colorSelText'=>"#FFFFFF", 'colorItemBkgnd'=>"#FFFFFF", 'colorItemSelBkgnd'=>"#000088"));
    $node->appendChild($listStyleNode);
    //创建<items>子标签
    $comboItemsNode = $doc->createElement('items');
    $node->appendChild($comboItemsNode);

    //解析子节点数据,生成下拉列表
    $text = escapeUnicodeString($text);
    //得到标签页对应的json文件名数组
    //增加一些数据(combobox没有数据的时候，下拉显示的也是黑乎乎一片)
    $lists = explode(',', $text);
    foreach ($lists as $list_text) {
      $comboItemsNode->appendChild(create_node($doc, 'item', null, array('text'=>$list_text)));
    }    
  }
  else if($type == 'listctrl') {
    //删掉标签的值
    $text = $node->nodeValue;    
    $node->nodeValue = '';

    //拆分文本得到listctrl的标题数组
    $items = explode('\n', $text);

    //align属性只能在<header>里设置,因此需要删掉
    $align = $node->getAttribute('align');
    $node->removeAttribute('align');
    //新建<header>子标签
    $header_node = create_node($doc, 'header', null, array('align'=>$align, 'itemSwapEnable'=>'0', 'fixWidth'=>'0', 'sortHeader'=>'0'));
    $node->appendChild($header_node);

    //<header>下新建子标签<items>
    $comboItemsNode = $doc->createElement('items');
    $header_node->appendChild($comboItemsNode);
    
    //计算标题的宽度
    $header_width = intval($node->getAttribute('width')/(1+count($items)));

    //取数据的第1行作为标题(listctrl的内容要在代码里动态增加,不能在xml里增加数据)
    $titles = explode(',', $items[0]);
    foreach ($titles as $title) {
      //去掉多余的空格
      $title = trim($title);
      //新增标题子标签<item>
      $comboItemsNode->appendChild(create_node($doc, 'item', $title, array('width'=>$header_width)));
    }

  }
  else if($type == 'richedit') {
    $node->setAttribute('multiLines', '1');
    $node->setAttribute('vscrollBar', '1');
    $node->setAttribute('hscrollBar', '1');
    $node->setAttribute('wantReturn', '1');
    $node->setAttribute('wordWrap', '1');
    $node->setAttribute('autoVscroll', '1');
    $node->setAttribute('autoHScroll', '1');
    $node->setAttribute('transParent', '1');
  }
  /*
  参考示例:(这里为了便于描述,格式化成树状结构,但实际应用中都是格式化成一行后再进行传递)
{
  "name": "tree1",
  "treectrl": {
    "node": "组织结构",
    "children": [
      {
        "node": "市场部",
        "children": [
          {
            "node": "南一区"
          },
          {
            "node": "北二区"
          },
          {
            "node": "西三区",
            "children": [
              {
                "node": "第一分队",
                "children": [
                  {
                    "node": "李四组"
                  },
                  {
                    "node": "王五组"
                  }
                ]
              }
            ]
          }
        ]
      },
      {
        "node": "宣传部",
        "childeren": [
          {
            "node": "南一区"
          },
          {
            "node": "南一区"
          },
          {
            "node": "南一区"
          }
        ]
      }
    ]
  }
}
  */
else if($type == 'treectrl') {
    //取出treectrl属性的数据进行解析,得到treectrl的子节点
  $text = $node->getAttribute('value');
    //删除nodes属性和treectrl的节点文本值
  $node->removeAttribute("value");
  $node->nodeValue = '';

    //解析子节点数据,并生成treectrl的item
  $tree = json_decode($text, true);
    //该函数通过递归来实现
  $tree_nodes = create_subtree($doc, $tree);
  if(!is_null($tree_nodes)) {
    $node->appendChild($tree_nodes);
  }
}
else if($type == 'caption') {
    //取出caption属性的数据进行解析,得到标题信息
  $text = $node->getAttribute('value');

    //删除caption属性和caption的节点文本值
  $node->removeAttribute("value");
  $node->nodeValue = '';
    //删除几个用不到的属性
  // $node->removeAttribute('name');
  $node->removeAttribute('margin-x');
  $node->removeAttribute('margin-y');

    //解析子节点数据,生成标题的相关信息
  // $text = escapeUnicodeString($text);
  $caps = json_decode($text, true);
  // var_dump($text);

  //删除width和height属性
  $cap_width = intval($node->getAttribute('width'));
  $cap_height = intval($node->getAttribute('height'));
  $node->removeAttribute('width');
  $node->removeAttribute('height');
  //修改pos属性
  $node->setAttribute('pos', "0,0,-0,$cap_height");
  //修改name属性
  $node->setAttribute('name', "caption");

    //(1)标题
  $title = '测试程序v1.0';
  if(isset($caps['title'])) {
    $title = escapeUnicodeString($caps['title']);
  }
    //增加<text>子节点
  $node->appendChild(create_node($doc, 'text', $title, array('pos'=>'0,8', 'name'=>'wnd_title')));

    //(2)最大最小关闭按钮的宽度
  $btn_width = 30;
  if(isset($caps['btn_width'])) {
    $btn_width = intval($caps['btn_width']);
  }

    //(3)最大最小关闭按钮
  $btn_names = array('min'=>0, 'max'=>0, 'close'=>1);
  $btn_skins = array('min'=>'minimize', 'max'=>'maximize', 'close'=>'close', 'restore'=>'restore');
  if(isset($caps['min'])) {
    $btn_names['min'] = intval($caps['min']);
  }
  if(isset($caps['max'])) {
    $btn_names['max'] = intval($caps['max']);
  }
  //特殊处理下,只要min或max设置为1,标题栏的min和max按钮就同时显示
  if(($btn_names['min']+$btn_names['max']) > 0) {
    $btn_names['min'] = 1;
    $btn_names['max'] = 1;
  }
  if(isset($caps['close'])) {
    $btn_names['close'] = intval($caps['close']);
  }

    //按钮的个数
  $n_btns = 0;
  foreach ($btn_names as $btn => $show) {
    if($show == 1) {
      $n_btns = $n_btns + 1;
    }
  }
  
  foreach ($btn_names as $btn => $show) {
    if($show == 1) {
      //按钮名字
      $name = 'btn_'.$btn;
      //按钮皮肤
      $skin = '_skin.sys.btn.'.$btn_skins[$btn];
      //坐标位置(用负数表示)
      $pos = -1*$n_btns*$btn_width.',0';
      //增加节点
      $node->appendChild(create_node($doc, 'imgbtn', null, array('name'=>$name, 'pos'=>$pos, 'skin'=>$skin, 'animate'=>1)));
      if($btn == 'max') {
        //额外增加一个不显示的restore按钮
        $node->appendChild(create_node($doc, 'imgbtn', null, array('name'=>'btn_restore', 'pos'=>$pos, 'skin'=>'_skin.sys.btn.restore', 'animate'=>1, 'show'=>0)));
      }
      $n_btns = $n_btns - 1;
    }
  }
}
else if($type == 'tabctrl') {
    //删除标签的文本值
  $text = $node->nodeValue;
  $node->nodeValue = '';

    //拆分标签文本值转换成tabctrl的标签页标题
    $delimiter = '\n'; // 默认用换行符作为分隔符
    if($node->getAttribute('tabAlign') == 'top') {
      //如果标签页在顶部的tabctrl,它的标签页标题是用逗号分隔的
      $delimiter = ',';
    }
    //得到标签页的名字数组
    $pages = explode($delimiter, $text);

    //取出group属性的数据进行解析
    $text = $node->getAttribute('include');
     //删除group属性
    $node->removeAttribute('include');
    //得到标签页对应的json文件名数组
    $jsonfiles = explode(',', $text);

    //循环生成标签页(标签的个数和指定的json文件个数不一定相同)
    $n_pages = count($pages);
    $n_files = count($jsonfiles);
    for($i=0;$i<max($n_pages, $n_files);$i++) {
      //创建<page>子节点
      if($i < $n_pages) {
        $page_node = create_node($doc, 'page', null, array('title'=>trim($pages[$i])));
        $node->appendChild($page_node);
      }
      else {
        $page_node = create_node($doc, 'page', null, null);
        $node->appendChild($page_node);
      }
    
      if($i < $n_files) {
        //构造json文件名,并创建<page>子节点下的具体内容
        $jsonfile = $jsonfiles[$i];
        $jsonfile = escapeUnicodeString(trim($jsonfile));
        $jsonfile = 'json/'.$jsonfile.'.json';
        //解析json文件,并添加到<page>子节点下
        createIncNode($doc, $page_node, $jsonfile);
      } 
    }
  }
  else if($type == 'group') {
    $node->setAttribute('ncSkin', '_skin.sys.border');
    //取出group属性的数据进行解析
    $text = $node->getAttribute('include');
     //删除group属性
    $node->removeAttribute('include');

    $jsonfile = escapeUnicodeString(trim(explode(',', $text)[0]));
    //构造json文件名
    $jsonfile = 'json/'.$jsonfile.'.json';
    //解析json文件,并添加到<group>子节点下
    createIncNode($doc, $node, $jsonfile);
  }
  else if($type == 'window') {
    // $node->setAttribute('ncSkin', '_skin.sys.border');
    //取出group属性的数据进行解析
    $text = $node->getAttribute('include');
     //删除group属性
    $node->removeAttribute('include');

    $jsonfile = escapeUnicodeString(trim(explode(',', $text)[0]));
    //构造json文件名
    $jsonfile = 'json/'.$jsonfile.'.json';
    if(is_file($jsonfile)) {
      //解析json文件,并添加到<group>子节点下
      createIncNode($doc, $node, $jsonfile);
    }
    else {
      $node->setAttribute('enable', '0');
      $node->setAttribute('visible', '0');
    }
  }
  else if($type == 'img') {
    //$node->setAttribute('ncSkin', '_skin.sys.border');
    $node->removeAttribute('margin-x');
    $node->removeAttribute('margin-y');
  }
}

function adjust_node_seq($doc)
{
  //调整标题节点caption的位置(作为root的第一个子节点)
  $root = $doc->getElementsByTagName("root")->item(0);
  if(is_null($root)) return;

  $caption = $doc->getElementsByTagName("caption")->item(0);
  if(is_null($caption)) return;

  $firstSibling = $root->firstChild;
  if( $caption !== $firstSibling ) {
    $root->insertBefore( $caption, $firstSibling );
  }

  //调整window节点的位置和包含关系
  //有待实现!!!
}

function create_root($doc, $attribs)
{
  if(is_null($attribs) || empty($attribs)) {
    $root = $doc->createElement('include');
    $doc->appendChild($root);
    return $root;
  }
  else {
    //创建SOUI根节点
    $soui = create_node($doc, 'SOUI', null, array('width'=>$attribs['width'], 'height'=>$attribs['height'], 'translucent'=>0, 'alpha'=>255, 'resizable'=>0));
    $doc->appendChild($soui);
    //创建skin节点
    $skin = create_node($doc, 'skin', null, null);
    $soui->appendChild($skin);
    //创建style节点
    $style = create_node($doc, 'style', null, null);
    $soui->appendChild($style);
    //创建root节点
    $root = create_node($doc, 'root', null, array('cache'=>1, 'skin'=>'_skin.sys.wnd.bkgnd'));
    $soui->appendChild($root);  
    return $root;
  }
}

function addToSkin($doc, $skin_name, $resType)
{
  $skin_node = $doc->getElementsByTagName("skin")->item(0);
  // 扫描<skin>下的所有name
  $names = array();
  foreach ($skin_node->childNodes as $node) {
    $name = $node->getAttribute('name');
    $names[] = $name;
  }
    
   // $skin_name = "skin_".strtolower($name);
  $name = substr($skin_name, strlen("skin_"));
   $src_name = $resType.":".strtoupper($name);
   if(!in_array($skin_name, $names)) {
     xml_append_child($skin_node, create_node($doc, 'imgframe', null, array('name'=>$skin_name, 'src'=>$src_name, 'tile'=>1)));  
   }
}

function postProcessSkin($doc, $node, $type, $resType)
{
  if($node->hasAttribute('skin')) {
    //设置皮肤
    $name = $node->getAttribute('skin');
    if(substr($name, strlen('_skin.sys')) == '_skin.sys') {

    }
    // $skin_name = "skin_".strtolower($name);
    //删除combobox属性和combobox的节点文本值
    // $node->setAttribute("skin", $skin_name);
  
    //添加到局部<skin>节点下
    addToSkin($doc, $name, $resType);
  }
}

//bMainWnd表示是否主窗口,嵌入到其他窗口的xml文件都是用<include>包括的
function mockups_to_soui_xml($jsonfile, $bMainWnd = true)
{
  if(!is_file($jsonfile)) return '';

  //从文件中读取json字符串
  $json = file_get_contents($jsonfile);
  // var_dump(decode_json($json, true));
  //解析成json数组对象
  $mockup = decode_json($json, true)['mockup'];

  //创建一个XML文档并设置XML版本和编码
  $doc = new DomDocument();
  //$doc->preserveWhiteSpace = false;
  //$doc->formatOutput = true;
  //xml输出的时候要加上编码,否则输出的中文变成一堆奇怪的符号
  $doc->encoding = 'UTF-8';

  //界面的宽度和高度
  $wnd_width = intval($mockup['mockupW']);
  $wnd_height = intval($mockup['mockupH']);
  //图形的宽度和高度(包含多出的空白部分)
  $fig_width = intval($mockup['measuredW']);
  $fig_height = intval($mockup['measuredH']);
  //left和top的偏移量
  $dx = $fig_width - $wnd_width;
  $dy = $fig_height - $wnd_height;

  $root_attribs = null;
  if($bMainWnd) {
    $root_attribs = array('width'=>$wnd_width, 'height'=>$wnd_height);
  }
  //创建根节点
  $root = create_root($doc, $root_attribs);

  //所有子控件
  $controls = $mockup['controls']['control'];
  foreach ($controls as $control) {
    //定义属性数组
    $attribs = array();

    //控件的坐标位置
    $left = intval($control['x']) - $dx;
    $top = intval($control['y']) - $dy;
    $attribs['pos'] = $left.",".$top;
    //控件的宽度和高度属性
    $attribs['width'] = intval($control['measuredW']);
    $attribs['height'] = intval($control['measuredH']);
    if(isset($control['w'])) {
      $attribs['width'] = intval($control['w']);
    }
    if(isset($control['h'])) {
      $attribs['height'] = intval($control['h']);
    }
    //微调(margin-x和margin-y设为1后导致label显示不全,稍微增大宽度和高度用于抵消被margin吃掉的空间)
    $attribs['width'] = $attribs['width'] + 2;
    // $attribs['height'] = $attribs['height'] + 2;

    //控件类型(mockups类型映射到soui控件类型)
    $type = mockups_type_to_soui_type($control['typeID']);
    if($type == 'unknown') {
      if($control['typeID'] == 'StickyNote') {
        //从Comment中提取skin(字符串用换行分隔)
        $skin_text = $control['properties']['text'];
        $skins = explode("\\n", $skin_text);
        foreach($skins as $skin_name) {
          addToSkin($doc, $skin_name, "img");
          // addToSkin($doc, $skin_name, "ico");
        }
      }
      else {
        echo '<h1>暂不支持'.$control['typeID'].'控件!!!</h1><br>';
      }
      //销毁内存
      unset($attribs);
      //跳过该次循环
      continue;
    }
    else {
      echo '<h1>'.$control['typeID'].'-->'.$type.'</h1><br>';
    }

    if(isset($control['properties']['state'])) {
      if($control['properties']['state'] == 'disabled') {
        // $attribs['enable'] = 0;
      }
    }

    //控件的字体属性
    $font_attrib = '';
    if(isset($control['properties']['underline'])) {
      $font_attrib = $font_attrib.',underline:'.intval($control['properties']['underline'] == 'true');
    }
    if(isset($control['properties']['italic'])) {
      $font_attrib = $font_attrib.',italic:'.intval($control['properties']['italic'] == 'true');
    }
    if(isset($control['properties']['bold'])) {
      $font_attrib = $font_attrib.',bold:'.intval($control['properties']['bold'] == 'true');
    }
    if($font_attrib != '') {
      $attribs['font']= $font_attrib;  
    }

    //所有控件增加边框，便于观察
    //后期可以用样式class进行替代或删除该属性
    // $attribs['ncSkin'] = '_skin.sys.border';

    if($type == 'edit' || $type == 'richedit') {
      if(isset($control['properties']['state'])) {
        if($control['properties']['state'] == 'disabled') {
          unset($attribs['enable']);
          // $attribs['readOnly'] = 1;
        }
      }
    }
    if($type == 'check' || $type == 'radio') {
      $attribs['width'] = $attribs['width'] + 30;
      if(isset($control['properties']['state'])) {
        if($control['properties']['state'] == 'selected') {
          $attribs['checked'] = 1;
        }
      }
    }
    //listbox要特殊处理
    if($type == 'listbox') {
      $attribs['itemHeight'] = '21';
      //高亮显示鼠标所在位置的item
      $attribs['hotTrack'] = 1;
      //$attribs['selectedIndex'] = '1';
      if(isset($control['properties']['rowHeight'])) {
        $attribs['itemHeight'] = $control['properties']['rowHeight'];
      }
    }
    //link要特殊处理
    if($type == 'link') {
      $attribs['href'] = 'http://about:blank';  // 默认打开空白页面
      if(isset($control['properties']['href'])) {
        $attribs['href'] = $control['properties']['href']['URL'];
        $attribs['class'] = 'cls_btn_weblink';
        //$attribs['cursor'] = "hand";
      }  
    }
    //slider要特殊处理
    if($type == 'sliderbar') {
     $attribs['value'] = '0';
     $attribs['min']= '0';
     $attribs['max']= '100';
     if(isset($control['properties']['value'])) {
      $attribs['value'] = $control['properties']['value'];
    }
    if($control['typeID'] == 'VSlider') {
      $attribs['vertical'] = 1;
        //调整slider的宽度或高度,否则会出现一个多余的拖动按钮(原因未知!!)
      $attribs['width'] = $attribs['width'] + 8;
    }
    else if($control['typeID'] == 'HSlider') {
        //调整slider的宽度或高度,否则会出现一个多余的拖动按钮(原因未知!!)
      $attribs['height'] = $attribs['height'] + 8;
    }
  }
    //进度条progress特殊处理
  if($type == 'progress') {
   $attribs['scrollBarValue'] = '0';
   $attribs['min']= '0';
   $attribs['max']= '100';
   if(isset($control['properties']['scrollBarValue'])) {
    $attribs['value'] = $control['properties']['scrollBarValue'];
  }
  $attribs['showPercent'] = 1;
}
    //设置水平或垂直线的线型
if($type == 'hr') {
  $attribs['lineStyle'] = 'solid';
  if(isset($control['properties']['stroke'])) {
    $lineStyle = $control['properties']['stroke'];
    if($lineStyle == 'dashed') {
      $lineStyle = 'dash';
    }
    else if($lineStyle == 'dotted') {
      $lineStyle = 'dot';
    }
    $attribs['lineStyle'] = $lineStyle;
  }
      //水平线或垂直线
  if($control['typeID'] == 'HRule') {
    $attribs['mode'] = 'horizontal';
        $attribs['height'] = 1; //  强制修改水平线的宽度为1,如若按照原本的height显示效果比较难看!
      }
      else if($control['typeID'] == 'VRule') {
        $attribs['mode'] = 'vertical';
        $attribs['width'] = 1; //  强制修改垂直线的宽度为1,如若按照原本的width显示效果比较难看!
      }
    }
    //列表控件 
    if($type == 'listctrl') {
     $attribs['hotTrack'] = 1;
     $attribs['itemHeight'] = '20';
     $attribs['headerHeight'] = '30';
     if(isset($control['properties']['rowHeight'])) {
      $attribs['itemHeight'] = $control['properties']['rowHeight'];
      $attribs['headerHeight'] = $control['properties']['rowHeight'];
    }
    $attribs['align'] = 'left';
    if(isset($control['properties']['align'])) {
      $attribs['align'] = $control['properties']['align'];
    }
  }
  //treectrl控件
  if($type == 'treectrl') {
   $attribs['itemHeight'] = "30";
   $attribs['checkBox'] = "1";
 }
    //combobox控件
 if($type == 'combobox') {
    //下拉列表(edit不可编辑)
  $attribs['dropDown'] = 1;
  $attribs['curSel'] = 0;
}
  //tab控件
if($type == 'tabctrl') {
    // $attribs['clipClient'] = 1;
  $attribs['tabAlign'] = 'top';
      //$attribs['tabWidth'] = "70";
      //$attribs['tabHeight'] = "38";
      //$attribs['tabInterSize'] = "0";
      //$attribs['tabPos'] = "10";
      //$attribs['dotted'] = "0";
      //$attribs['animateSteps'] = "10";
  if($control['typeID'] == 'VerticalTabBar') {
    $attribs['tabAlign'] = 'left';
  }
  else if($control['typeID'] == 'TabBar') {
    $attribs['tabAlign'] = 'top';
  }
}
  //group控件
if($type == 'group') {
  $attribs['align'] = 'left';
    // $attribs['clipClient'] = 1;
}
  //window控件
if($type == 'window') {
    // $attribs['align'] = 'left';
    // $attribs['clipClient'] = 1;
}

  //控件的其它属性
  //mockups提供了一种自定义属性功能(一个customID对应一个customData)
  //这2个字段可以是任意类型的数据
  //本程序规定customData以json格式传入自定义数据,从而补充mockups没有的一些属性和数据
  //比如name, min, max等等
$zOrder = mockups_type_to_soui_type($control['zOrder']); // 图形的绘图顺序编号(也决定了图形的层位/遮挡关系)
$name = mockups_type_to_soui_type($control['typeID']);
$attribs['name'] = $name.$control['ID'];
if(isset($control['properties']['customData'])) {
  $json_datas = trim($control['properties']['customData']);
    //json数据中的引号等符号被用url方式进行编码转义了,比如空格变成了%22,需要进行解码
  $json_datas = urldecode($json_datas);
    //将%u替换成\u
  $json_datas = str_replace('%u', '\\u', $json_datas);

  if(!empty($json_datas)) {
      //合并附加的json属性数据
    $more_attribs = decode_json($json_datas,true);

    if(!is_null($more_attribs)) {
      foreach ($more_attribs as $key => $value) {
        if(is_array($value)) {
          $value = json_encode($value);
        }
        else {
          $value =  escapeUnicodeString($value);
        }
        $more_attribs[$key] = $value;
      }
            //合并2个属性关联数组
      $attribs = array_merge($attribs, $more_attribs);
            //销毁内存
      unset($more_attribs);
    }
  }
}

  //控件上的文本内容
$text = '';
if(isset($control['properties']['text'])) {
  $text = $control['properties']['text'];
}

  //创建子控件节点
$control = create_node($doc, $type, $text, $attribs);
$root->appendChild($control);

  //某些控件需要增加子节点,比如listbox
postProcess($doc, $control, $type);
//增加局部皮肤
postProcessSkin($doc, $control, $type, "img");

  //销毁内存
unset($attribs);
}

//调整节点顺序(主要是caption节点)
adjust_node_seq($doc);

return $doc->saveXML();
  //$doc->save($xmlfile);
}

function mockups_to_soui_converter($jsonDir='json', $xmlDir='xml')
{
  //获取本文件目录的文件夹地址
  $filesnames = scanfiles($jsonDir);
  //获取也就是扫描文件夹内的文件及文件夹名存入数组 $filesnames
  foreach ($filesnames as $name) {
    if($name == '.' || $name == '..') continue;
    // echo $name."<br/>";
    //得到没有扩展名的文件名
    $fname = pathinfo($name)['filename'];
    //拼接json文件名和xml文件名
    $jsonfile = $jsonDir.'\\'.$fname.'.json';
    $xmlfile = $xmlDir.'\\'.$fname.'.xml';
    echo $jsonfile.' <-----> '.$xmlfile.'<br/>';
    //判断是否主窗口(以c_开头的json文件表示它是一个需要被include到其它控件的子窗口)
    $bMainWnd = (substr($fname, 0, 2) != 'c_');
    //生成xml字符串
    $xml_src = mockups_to_soui_xml($jsonfile, $bMainWnd);
    //美化xml结构并保存到文件中
    prettyXml($xml_src, $xmlfile);
  }
}

function createFileNode($doc, $filename, $prefix='')
{
  $fname = pathinfo($filename)['filename'];
  $ext = pathinfo($filename)['extension'];
  if($prefix != '') {
    $prefix = $prefix.'_';
  }
  $res_name = $prefix.$fname;
  if($ext != 'xml') {
    $res_name = strtoupper($prefix.$fname);
  }
  return create_node($doc, 'file', null, array('name'=>$res_name, 'path'=>$filename));
}

function getNodeByResType($doc, $resType)
{
  //先搜索已有的节点
  $typeNodes = $doc->getElementsByTagName($resType);
  if(is_null($typeNodes) || $typeNodes->length == 0) {
    return $doc->createElement($resType);  
  }
  else {
    return $typeNodes->item(0);
  }
}

function createFileNodes($doc, $resType, $dir, $subDir, $filters='*.*', $prefix='', $bDfs=false)
{
  $full_dir = $dir.$subDir;
  if(!is_dir($full_dir)) return null;
  
  //建立过滤词典
  $filterDict = array();
  if($filters != '*.*') {
    foreach(explode(';', $filters) as $filter) {
      $filter = pathinfo(trim($filter))['extension'];
      if($filter != '') {
        $filterDict[$filter] = 1;  
      }
    }
  }
  
  $n_dir = strlen($dir);
  //遍历文件夹下所有文件(参数bDfs决定是否递归遍历子文件夹)
  $filesnames = scanfiles($full_dir, $bDfs);
  if(empty($filesnames)) return null;

  $node = getNodeByResType($doc, $resType);
  foreach ($filesnames as $fname) {
    //文件名信息对象
    $pi = pathinfo($fname);
    //文件全名(文件名+扩展名)
    $basename = $pi['basename'];
    //扩展名
    $ext = $pi['extension'];
    //文件名
    $name = $pi['filename'];
    if($basename == '.' || $basename == '..') continue;
    if($resType == 'uidef' && $basename != 'init.xml') continue;
    if($resType != 'uidef' && $basename == 'init.xml') continue;
    if($filters != '*.*' && !array_key_exists($ext, $filterDict)) continue;

    //修饰前缀
    //按照约定俗成的习惯(soui、duivision、vc等),xml的资源一般不加前缀,除了init.xml要用xml_init修饰以外
    //其他的比如图片、图标、翻译等资源都是加前缀的,这样就能根据名字区分资源的类型,写代码能清晰一些
    // if($resType == 'UIDEF' && $basename == 'init.xml') { //init.xml需要加前缀xml
    //   $prefix = 'xml';
    // }
    // else 
    if($ext == 'xml') {  // 如果xml文件,默认不加前缀
      $prefix = '';
    }
    // else if($prefix == '') {  //如果没有指定,则以文件的扩展名作为前缀
    //   $prefix = $ext; 
    // }

    //创建file节点
    $node->appendChild(createFileNode($doc, substr($fname, $n_dir), $prefix));
  }

  return $node;
}

function addImgToRes($res, $doc, $dir)
{
    //扫描image文件,创建<img>子节点
  xml_append_child($res, createFileNodes($doc, 'icon', $dir, 'image', $filters='*.ico', $prefx='ICON', $bDfs=true));
  //扫描image文件,创建<img>子节点
  xml_append_child($res, createFileNodes($doc, 'cursor', $dir, 'image', $filters='*.cur;*.ani', $prefx='CURSOR', $bDfs=true));
  //扫描image文件,创建<img>子节点
  xml_append_child($res, createFileNodes($doc, 'img', $dir, 'image\cbm', $filters='*.png;*.jgp;*.bmp;*.jpge', $prefx='cbm', $bDfs=false));
  xml_append_child($res, createFileNodes($doc, 'img', $dir, 'image', $filters='*.png;*.jgp;*.bmp;*.jpge', $prefx='', $bDfs=false));
  xml_append_child($res, createFileNodes($doc, 'img', $dir, 'image\bk', $filters='*.png;*.jgp;*.bmp;*.jpge', $prefx='', $bDfs=false));
  xml_append_child($res, createFileNodes($doc, 'img', $dir, 'image\button', $filters='*.png;*.jgp;*.bmp;*.jpge', $prefx='', $bDfs=false));
  xml_append_child($res, createFileNodes($doc, 'img', $dir, 'image\dkpac', $filters='*.png;*.jgp;*.bmp;*.jpge', $prefx='DKPAC', $bDfs=false));
  xml_append_child($res, createFileNodes($doc, 'img', $dir, 'image\small', $filters='*.png;*.jgp;*.bmp;*.jpge', $prefx='SMALL', $bDfs=false));
  xml_append_child($res, createFileNodes($doc, 'img', $dir, 'image\icon', $filters='*.png;*.jgp;*.bmp;*.jpge', $prefx='ICON', $bDfs=false));
  xml_append_child($res, createFileNodes($doc, 'img', $dir, 'image\menu', $filters='*.png;*.jgp;*.bmp;*.jpge', $prefx='MENU', $bDfs=false));
  xml_append_child($res, createFileNodes($doc, 'img', $dir, 'image\skins\default', $filters='*.png;*.jgp;*.bmp;*.jpge', $prefx='DEF', $bDfs=false));
  //扫描image文件,创建<img>子节点
  //xml_append_child($res, createFileNodes($doc, 'GIF', 'image', $filters='*.gif', $prefx='', $bDfs=false));
  //扫描gif文件,创建<GIF>子节点
  xml_append_child($res, createFileNodes($doc, 'gif', $dir, 'gif', $filters='*.gif', $prefx='', $bDfs=false));
}

function addOtherToRes($res, $doc, $dir)
{
  //扫描rtf文件,创建<rtf>子节点
  xml_append_child($res, createFileNodes($doc, 'rtf', $dir, 'rtf', $filters='*.rtf', $prefx='', $bDfs=false));
  //扫描lua文件,创建<script>子节点
  // xml_append_child($res, createFileNodes($doc, 'script', $dir, 'lua', $filters='*.lua', $prefx='', $bDfs=false));
  //扫描translator文件,创建<translator>子节点
  // xml_append_child($res, createFileNodes($doc, 'translator', $dir, 'translator', $filters='*.xml', $prefx='', $bDfs=false));
}

function createUIResFile($dir, $uiResFile)
{
  if($dir[strlen($dir)-1] != '\\') {
    $dir = $dir.'\\';
  }

  //创建一个XML文档并设置XML版本和编码
  $doc = new DomDocument();
  //$doc->preserveWhiteSpace = false;
  //$doc->formatOutput = true;
  //xml输出的时候要加上编码,否则输出的中文变成一堆奇怪的符号
  $doc->encoding = 'UTF-8';

  //创建<resource>节点
  $res = $doc->createElement('resource');
  $doc->appendChild($res);

  //扫描xml文件,创建<UIDEF>子节点
  xml_append_child($res, createFileNodes($doc, 'uidef', $dir, 'xml'));
  //扫描xml文件,创建<LAYOUT>子节点
  xml_append_child($res, createFileNodes($doc, 'layout', $dir, 'xml'));

  //创建<img>、<icon>等图片资源节点
  addImgToRes($res, $doc, $dir);
  //创建<rtf>、<script>等资源节点
  addOtherToRes($res, $doc, $dir);

  //美化xml结构并保存到文件中
  prettyXml($doc->saveXML(), $uiResFile); 
}

function writeImgSrcToDB($uiResFile='uires.idx', $resType='img')
{
  $mysqli = mysqli_connect("localhost", "root", "", "soui");
  /* check connection */
  if (mysqli_connect_errno()) {
    printf("Connect failed: %s\r\n", mysqli_connect_error());
    return;
  }

  //解决php读取mysql utf8编码中文乱码问题
  //还需要配合mysql数据库的编码设置
  //http://www.phpthinking.com/archives/320
  $mysqli->query("set names 'utf8' ");
  $mysqli->query("set character_set_client=utf8");
  $mysqli->query("set character_set_results=utf8");

  //清空skin表
  $mysqli->query("delete from skin");
  $mysqli->query("alter table skin AUTO_INCREMENT=1");

  //创建一个XML文档并设置XML版本和编码
  $doc = new DomDocument();
  $doc->preserveWhiteSpace = false;
  $doc->load($uiResFile);
  // $doc->formatOutput = true;
  //xml输出的时候要加上编码,否则输出的中文变成一堆奇怪的符号
  $doc->encoding = 'UTF-8';
  // echo htmlspecialchars($doc->saveXML());

  foreach ($doc->getElementsByTagName($resType) as $nodes) {
   foreach ($nodes->childNodes as $node) {
     $name = $node->getAttribute('name');
     $src = $node->getAttribute('path');
     $size = getimagesize($src);
     $width = $size[0];
     $height = $size[1];

     //mysql插入的时候斜杠会被转义,因此要替换成\\
     $src = str_replace('\\', '\\\\', $src);
     $sql = "INSERT INTO skin(name, src, width, height) VALUES ('$name', '$src', $width, $height)";
     $mysqli->query($sql);
   }
 }
 /* close connection */
 $mysqli->close();
}

function UpdateInitXml($dir, $resType='img')
{
  $uiResFile = $dir.'\uires.idx';
  $styleFile = $dir.'\xml\init.xml';
  echo $uiResFile."<br>";
  echo $styleFile."<br>";
  //解析uires.idx文件,得到图片资源
  //创建一个XML文档并设置XML版本和编码
  $doc = new DomDocument();
  $doc->preserveWhiteSpace = false;
  $doc->load($uiResFile);
  // $doc->formatOutput = true;
  //xml输出的时候要加上编码,否则输出的中文变成一堆奇怪的符号
  $doc->encoding = 'UTF-8';
  // echo htmlspecialchars($doc->saveXML());

  //读取init.xml文件
  $doc2 = new DomDocument();
  $doc2->preserveWhiteSpace = false;
  $doc2->load($styleFile);
  $doc2->encoding = 'UTF-8';

  $skin_node = $doc2->getElementsByTagName("skin")->item(0);
  //扫描<skin>下的所有name
  $names = array();
  foreach ($skin_node->childNodes as $node) {
    $name = $node->getAttribute('name');
    $names[] = $name;
  }

  //扫描uires.idx文件中的<img>标签
  foreach ($doc->getElementsByTagName($resType) as $nodes) {
   foreach ($nodes->childNodes as $node) {
     $name = $node->getAttribute('name');
     $src = $node->getAttribute('path');
    
     $skin_name = "skin_".strtolower($name);
     $src_name = $resType.":".strtoupper($name);
     if(in_array($skin_name, $names)) continue;

     echo $skin_name.'-->'.$src_name.'<br>';
     xml_append_child($skin_node, create_node($doc2, 'imgframe', null, array('name'=>$skin_name, 'src'=>$src_name, 'tile'=>1)));
    }
  }
  prettyXml($doc2->saveXML(), $styleFile);
}

function genResNameTxtFile()
{
  $file = fopen("ResName.txt", 'w');
  fwrite($file, "layout:coal_design");
  fclose($file);
}

//项目路径(读取root.txt文件得到)
$projDir = file_get_contents('root.txt');

//执行转换,扫描json文件夹里的json文件,解析并生成xml文件,保存到xml文件夹
mockups_to_soui_converter('json', '..\uires\xml');
//生成资源入口文件uires.idx
createUIResFile('..\uires', '..\uires\uires.idx');
//生成图片资源索引数据库
// writeImgSrcToDB('../uires/uires.idx', 'img');
//生成图片皮肤
UpdateInitXml("..\uires", "img");
//在文件中指定layout名称(测试的时候可以动态显示不同的xml模板)
genResNameTxtFile();

//解析xml文件,生成cpp代码
xml_to_dialog('..\uires\xml', 'cpp');

//将uires复制到cbm项目
recurse_copy('..\uires', $projDir.'ArxSoUI\uires');
//将uires复制到soui\bin(方便mfc_test进行预览)
recurse_copy('..\uires', $projDir.'ThirdParty\soui\bin\uires');
copy('ResName.txt', $projDir.'ThirdParty\soui\bin\uires\ResName.txt');

//将php代码复制到cbm项目
// copy('root.txt', $projDir.'php\soui\web\code\root.txt');
copy('index.php', $projDir.'php\soui\web\code\index.php');
copy('soui_cpp.php', $projDir.'php\soui\web\code\soui_cpp.php');
copy('php_utils.php', $projDir.'php\soui\web\code\php_utils.php');

// recurse_copy('cpp', 'C:\Develop\GitProject\cbm\ArxSoUI');

?>

</pre>