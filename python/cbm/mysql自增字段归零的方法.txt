-- 清空表,并将自增字段归零
-- 参考: http://www.cnblogs.com/top5/archive/2013/10/24/3385938.html
-- 原因: 钻场和钻孔数据比较多,会导致id编号非常大,有可能会超出int类型的最大取值范围
delete from design_site;
alter table design_site auto_increment=1;

delete from design_pore;
alter table design_pore auto_increment=1;