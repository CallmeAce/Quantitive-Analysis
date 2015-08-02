# -*- coding: utf-8 -*-  
#coding=utf-8  
import _mysql,MySQLdb
import os,time,sys



if __name__=="__main__":
	path = "/Users/xuanwang/Documents/all_trading_data/stock_data/"
	files = os.listdir(path)
	db = _mysql.connect(host ="127.0.0.1",passwd="1131211",db="stock_daily")
#	cursor = db.cursor()
	for file_1 in files:
		n = len(file_1)
		if file_1[n-3:n]!="csv":
			continue
#		sql ="""create table """+file_1[0:n-4]+"""(code varchar(12) not NULL,date date not NULL,open double,high double,low double,close double,net_change double,  	volume double,  	money double,  	traded_market_val double,  	market_value double,  	turnover double,  	adjust_price double,  	report_date date,  	report_type double,  	PE_TTM double,  	PS_TTM double,  	PC_TTM double,  	PB double,  	primary key (date))"""
#		sql = """drop table """+ file_1[0:n-4]
		sql = """load data local infile '"""+path+file_1+"""' into table """+file_1[0:n-4]+""" FIELDS TERMINATED BY ','
		LINES TERMINATED BY '\n'
		IGNORE 1 LINES
		(code,date,open,high,low,close,net_change,volume,money,traded_market_val,
		market_value,turnover,adjust_price,report_date,report_type,PE_TTM,PS_TTM,PC_TTM,PB)"""
		db.query(sql)
	db.close()
