<?php

function truncateDatas($file)
{
	fwrite($file, "truncate table tech_mode;".ENTER);
	fwrite($file, "truncate table technology;".ENTER);
	fwrite($file, "truncate table mine_region;".ENTER);
	fwrite($file, "truncate table mine_base;".ENTER);
	fwrite($file, "truncate table topo_geo;".ENTER);
	fwrite($file, "truncate table res_abundance;".ENTER);
}

function genMineBaseSqlFile($file, $txtfile)
{
	fwrite($file, ENTER);
	foreach(file($txtfile) as $line => $content) {
	    //拆分字符串(制表符分隔)
	    $data = explode("\t", trim($content));
		//基地编号
	    $id = intVal($data[0]);
	    //基地名称
	    $name = $data[1];
	    
	    fwrite($file, "insert into mine_base(id, name) values($id, '$name');".ENTER);
	}
}

function genMineRegionSqlFile($file, $txtfile)
{
	fwrite($file, ENTER);
	foreach(file($txtfile) as $line => $content) {
	    //拆分字符串(制表符分隔)
	    $data = explode("\t", trim($content));
		//矿区编号
	    $id = intVal($data[0]);
	    //矿区名称
	    $name = $data[1];
	    //基地编号
	    $mine_base_id = intval($data[2]);
	    
	    fwrite($file, "insert into mine_region(id, name, mine_base_id) values($id, '$name', $mine_base_id);".ENTER);
	}
}

function genTechModeSqlFile($file, $txtfile)
{
	fwrite($file, ENTER);
	foreach(file($txtfile) as $line => $content) {
	    //拆分字符串(制表符分隔)
	    $data = explode("\t", trim($content));
	    var_dump($data);
		//技术模式编号
	    $id = intVal($data[0]);
	    //技术模式名称
	    $name = $data[1];
	    //矿区编号
	    $mine_region_id = intval($data[2]);
	    $c1 = intval($data[3]);
	    $c2 = intval($data[4]);
	    $c3 = intval($data[5]);
	    
	    fwrite($file, "insert into tech_mode(id, name, mine_region_id, c1, c2, c3) values($id, '$name', $mine_region_id, $c1, $c2, $c3);".ENTER);
	}
}

function genTechnologySqlFile($file, $txtfile)
{
	fwrite($file, ENTER);
	foreach(file($txtfile) as $line => $content) {
	    //拆分字符串(制表符分隔)
	    $data = explode("\t", trim($content));
		//技术编号
	    $id = intVal($data[0]);
	    //技术名称
	    $name = $data[1];
	    //矿区编号
	    $mine_region_id = intval($data[2]);
	    //是否关键技术
	    $isKey = intval($data[3]);
	    
	    fwrite($file, "insert into technology(id, name, isKey, mine_region_id) values($id, '$name', $isKey, $mine_region_id);".ENTER);
	}
}

function genComplexitySqlFile($file, $txtfile)
{
	fwrite($file, ENTER);
	foreach(file($txtfile) as $line => $content) {
	    //拆分字符串(制表符分隔)
	    $data = explode("\t", trim($content));
		//编号
	    $id = intVal($data[0]);
	    //名称
	    $name = $data[1];
	    //详细说明
	    $details = $data[2];
	    
	    fwrite($file, "insert into complexity(id, name, details) values($id, '$name', '$details');".ENTER);
	}
}

function genTopoGeoSqlFile($file, $txtfile)
{
	fwrite($file, ENTER);
	foreach(file($txtfile) as $line => $content) {
	    //拆分字符串(制表符分隔)
	    $data = explode("\t", trim($content));
		//编号
	    $id = intVal($data[0]);
	    //分类
	    $name = $data[2];
	    //特点
	    $feature = $data[1];
	    
	    fwrite($file, "insert into topo_geo(id, name, feature) values($id, '$name', '$feature');".ENTER);
	}
}

function genResAbundanceSqlFile($file, $txtfile)
{
	fwrite($file, ENTER);
	foreach(file($txtfile) as $line => $content) {
	    //拆分字符串(制表符分隔)
	    $data = explode("\t", trim($content));
		//编号
	    $id = intVal($data[0]);
	    //分类
	    $name = $data[1];
	    //丰度上下限
	    $min_a = floatval($data[2]);
	    $max_a = floatval($data[2]);
	    
	    fwrite($file, "insert into res_abundance(id, name, min_abundance, max_abundance) values($id, '$name', $min_a, $max_a);".ENTER);
	}
}

function genAccountSqlFile($file, $txtfile)
{
	fwrite($file, ENTER);
	foreach(file($txtfile) as $line => $content) {
	    //拆分字符串(制表符分隔)
	    $data = explode("\t", trim($content));
		//编号
	    $id = intVal($data[0]);
	    //用户名
	    $user = $data[1];
	    //密码
	    $pwd = $data[2];
	    
	    fwrite($file, "insert into account(username, password) values('$user', '$pwd');".ENTER);
	}
}

function genMineSqlFile($file, $txtfile)
{
	fwrite($file, ENTER);
	foreach(file($txtfile) as $line => $content) {
	    //拆分字符串(制表符分隔)
	    $data = explode("\t", trim($content));
		//编号
	    $id = intVal($data[0]);
	    //用户名
	    $name = $data[1];
	    //矿区
	    $mine_region_id = $data[2];
	    //账户
	    $account_id = $data[3];
	    
	    fwrite($file, "insert into mine(name, mine_region_id, account_id) values('$name', $mine_region_id, $account_id);".ENTER);
	}
}

function genRockSqlFile($file, $txtfile)
{
	fwrite($file, ENTER);
	foreach(file($txtfile) as $line => $content) {
	    //拆分字符串(制表符分隔)
	    $data = explode("\t", trim($content));
		//编号
	    $id = intVal($data[0]);
	    //名称
	    $name = $data[1];
	    //a
	    $a = floatval($data[2]);
	    //b
	    $b = floatval($data[3]);
	    //c
	    $c = floatval($data[3]);
	    
	    fwrite($file, "insert into rock(id, name, a, b, c) values($id, '$name', $a, $b, $c);".ENTER);
	}
}

//将建表的sql文件一次性追加到cbm-data.sql文件中
function make_sql_files()
{
	// file_put_contents('cbm.sql', file_get_contents('cbm-mysql.sql'));
	//生成sql插入语句
	$file = fopen("cbm-data.sql", "w");
	//生成煤炭基地的sql数据文件
	// truncateDatas($file);
	// genAccountSqlFile($file, 'account.txt');
	genMineBaseSqlFile($file, 'mine_base.txt');
	genMineRegionSqlFile($file, 'mine_region.txt');
	// genMineSqlFile($file, 'mine.txt');
	genTechModeSqlFile($file, 'tech_mode.txt');
	genTechnologySqlFile($file, 'technology.txt');
	genTopoGeoSqlFile($file, 'topo_geo.txt');
	genComplexitySqlFile($file, 'complexity.txt');
	genResAbundanceSqlFile($file, 'res_abundance.txt');
	genRockSqlFile($file, 'rock.txt');
	fclose($file);
}

?>
