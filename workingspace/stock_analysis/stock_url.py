#!/usr/bin/env python
# -*- coding:utf-8 -*-
import _mysql
import urllib
import string
import os
import sys
#debug=True
debug=False

class Utility:
	def ToGB(self,str):
		if(debug): print(str)
		return str.decode('GBK')

class StockInfo:
	"""
	0: 未知
	1: 名字
	2: 代码
	3: 当前价格
	4: 涨跌
	5: 涨跌%
	6: 成交量（手）
	7: 成交额（万）
	8:
	9: 总市值"""
	def GetStockStrByNum(self,num):
		f= urllib.urlopen('http://hq.sinajs.cn/list='+ str(num))
		if(debug): print(f.geturl())
		if(debug): print(f.info())
		#return like: v_s_sz000858="51~五 粮 液~000858~18.10~0.01~0.06~94583~17065~~687.07";
		return f.readline()
		f.close()
	def ParseResultStr(self,resultstr):
		if(debug): print(resultstr)
		slist=resultstr[14:-3]
		if(debug): print(slist)
		slist=slist.split('~')
		if(debug) : print(slist)
		#print('*******************************')
		print('  股票名称:', slist[1])
		print('  股票代码:', slist[2])
		print('  当前价格:', slist[3])
		print('  涨    跌:', slist[4])
		print('  涨   跌%:', slist[5],'%')
		print('成交量(手):', slist[6])
		print('成交额(万):', slist[7])
		#print('date and time is :', dateandtime)
		print('*******************************')
	def GetStockInfo(self,num):
		str = self.GetStockStrByNum(num)
		util = Utility()
		strGB= util.ToGB(str)
#		self.ParseResultStr(strGB)
		print(strGB)
		return strGB
class DB_A:
	db = 0
	def	__init__(self):
		self.db = _mysql.connect(host ="127.0.0.1",passwd="1131211",db="stock_daily")
	def insert(self,sql):
		self.db.query(sql)
	def delete(self):
		self.db.close()
		print(self.db)
if __name__ == '__main__':
	stocks = ['sh600888','sz300104','sz300027','sz000919']
	path = "/Users/xuanwang/Documents/all_trading_data/stock_data/"
	files = os.listdir(path)
	instance = StockInfo()
	database = DB_A()
	for stock in stocks:
		print(stock)
		stock_str = instance.GetStockInfo(stock)
		str_list  = stock_str[21:-3]
		str_list  = str_list.split(',')
		if str_list[30] !='':
			print(str_list[30])
			sql = """insert into """+file_1[0:-4]+""" values ( """ +file_1[0:-4] +
				","+str_list[30]+","+
