create table "tablename" (
code varchar(12) not null,
date date not null,
open double,
high double,
low double,
close double,
change double,#涨跌幅 复权后真实涨跌幅
volume double, #成交量
money double, # 成交额
traded_market_val double, #流通市值
market_value double, #总市值
turnover double,   #换手率 成交量/流通股本
adjust_price double, #后复权价
report_date date, #最近一期财务报告发布日期
report_type double, #最近一期财务报告类型
PE_TTM double,#最近12个月市盈率，股价/最近12个月归属母公司的每股收益
PS_TTM double,#最近12个月市销率， 股价/最近12个月每股营业收入
PC_TTM double,#最近12个月市现率， 股价/最近12个月每股经营现金率
PB     double,#市净率，股价/最近期财报每股净资产
primary key (date)
)
