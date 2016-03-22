#coding:utf-8
import xlrd

import sys 
reload(sys) 
sys.setdefaultencoding('utf8') 

def GetFiledText(sheet):
	field = ""
	for col in range(1,sheet.ncols):
		field = field + ( "\n\
		`%s` %s DEFAULT NULL,\n\
		"% (sheet.cell_value(1,col),sheet.cell_value(0,col)))
	return field

def GetTilteText(sheet):
	title_text = "INSERT INTO `%s` (`id`, " % (sheet.cell_value(0,0))
	for col in range(1,sheet.ncols):
		title_text = title_text + "`%s`" % (sheet.cell_value(1,col))
		if col != sheet.ncols-1:
			title_text = title_text + ', '
		else:
			title_text = title_text + ' ) VALUES\n'
	return title_text

def GetDataText(sheet):
	data_text = "("
	for row in range(2,sheet.nrows):
		for col in range(0,sheet.ncols):
			if col == 0:
				tmp = "%d" %(int(sheet.cell_value(row,col)))
			else:
				tmp = "'%s'" %(sheet.cell_value(row,col))
			data_text = data_text + tmp
			# print u'总行数:%d\t目前行:%d' % (sheet.nrows,row) 
			if col != sheet.ncols-1:
				data_text = data_text + ', '
			elif row != sheet.nrows -1:
				data_text = data_text + '),\n('
			else:
				data_text = data_text + ');\n\n'
	return data_text

def GetSQL(xlsFile):
	bk = xlrd.open_workbook(xlsFile)
	sheetxrange = range(bk.nsheets)
	sheet = bk.sheet_by_name("Sheet1")

	field = GetFiledText(sheet)

	sql = "CREATE TABLE IF NOT EXISTS `%s` (\
	  `id` int(11) NOT NULL AUTO_INCREMENT," % (sheet.cell_value(0,0)) + field +\
	  "PRIMARY KEY (`id`)\
	  ) ENGINE=InnoDB  DEFAULT CHARSET=utf8;\n\n"

	title_text = GetTilteText(sheet)

	data_text = GetDataText(sheet)

	sql = sql + title_text + data_text
	return sql

def CreatSQL():
	sqlList = []
	for i in range(0,17):
		xlsFile = u'%d.xls' %(i)
		print xlsFile
		sql = GetSQL(xlsFile)
		sqlList.append(sql)
	sqlFile = open('cbm_pores.sql', 'w')
	# sqlFile.write(sql)
	sqlFile.writelines(sqlList)
	sqlFile.close( )

if __name__ == '__main__':
	CreatSQL()