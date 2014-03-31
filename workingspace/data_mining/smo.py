#! /usr/bin/python
# _*_ coding:utf-8 _*_

import numpy as np
from random import randint
import time,os,sys
datas = []
labels = []

train_data = "tran_data.txt"
file_in =''.join(sys.argv[1:])
file_out=file_in +"_result.txt"
print(file_in)
def load_data(datas,labels) :
	try:
		fn =open(file_in,"r")
	except IOError:
		print("\t ERR: File Not Exist!")
	else:
		print("\t Open File Successfully")
		line = ""# the line
		line = fn.readline()
		while line:
			line = line[:-1]
			print(line)
			line = line.replace('\n','')
			s_line = line.split("\t")
       #     s_line = s_line.replace('\n','')
			col_count = len(s_line)
			if col_count != 3:# check the length, the length of the data for test is 3	
				print("\t"+time.strftime('%y-%m-%d %X', time.localtime())+'第'+str(line_count)+'行数据处理失败')
				break;
		#	datas.append((int(s_line[0]),int(s_line[1])))
			tmp_data =[]
			for i in range(col_count-1):
				tmp_data.append(int(s_line[i]))
			datas.append(tmp_data)
			#global labels
			print(datas)
			labels.append(int(s_line[col_count-1]))
			line =""
			line = fn.readline()


#kernel
def kernel(x1,x2):
	#linear kernel
	return x1.dot(x2.T)



def modelOut(x,w,b,y):
	return x.dot(w.T)-b-y



def cal_LH(a1,a2,C,s):
	if s>0:
		L = max([0,a1+a2-C])
		H = min([C,a1+a2])
	else:
		L = max([0,a2-a1])
		H = min([C,C+a2-a1])
	return L,H


def value_SVMFunction(alpha,datas_X,y):# the value of the SVM optimization function
	#optimization function is :
	# sum(alpha_i) - 0.5* sum(alpha_i*alpha_j*y_i*y_j*k(x_i,x_j))
	length = datas_X.shape[0]
	Sum = 0
	for i in range(0,length):
		for j in range(0,length):
			x1= datas_X[i,:]
			x2= datas_X[j,:]
			Sum += alpha[i]*alpha[j]*y[i]*y[j]*kernel(x1,x2)
	return alpha.sum()-0.5*Sum



def takeStep(i1,i2,datas,labels,alpha,w,b,C):
	if(i1 == i2): 
		return 0
	# alpha2_new = alpha2_old -y2(E1-E2)/eta
	# eta = 2k12 -k11-k22 is the second derivative of the function 
	# E_i = w*x_i -b -y_i
	# then clipped the alpha_new according to the threshold
	# a2_clipped = H (if a2_new >= H); = a2_new (if L<a2new<H); = L if(a2new<=L)
	alpha1		 = alpha[i1]
	alpha2		 = alpha[i2]
	alpha1_old_v = alpha1[0]
	alpha2_old_v = alpha2[0]
	y1 			 = labels[i1]
	y2  		 = labels[i2]
	point1		 = datas[i1,:]
	point2		 = datas[i2,:]
	E1			 = w.dot(point1.T) - b - y1
	E2			 = w.dot(point2.T) - b - y2
	s			 = y1 * y2
	L, H		 = cal_LH(alpha1,alpha2)
	if abs(L-H) <eps:
		return 0
	k11			 = kernel(point1,point1)
	k12			 = kernel(point1,point2)
	k22			 = kernel(point2,point2)
	eta			 = 2*k12 - k11 - k22
	if eta<0: # second derivative is smaller than 0, the function has maximum value
		a2 = alpha2 - y2 * (E1-E2) / eta
		if a2 < L:
			a2 = L
		else:
			a2 = H
	else:   # the function has no maximum point, so we have to check L and H which one can maximize the function
		alpha[i2] = L
		L_v = optimize_SVMFuction(alpha,datas,labels)
		alpha[i2] = H
		H_v = optimize_SVMFuction(alpha,datas,labels)
		alpha[i2] = alpha2 # change it back
		if L_v<H_v-eps: # eps,allow some errors
			a2 = H
		elif L_v>H_v+eps:
			a2 = L
		else:
			a2 = alpha2
	if a2 < 1e-8:  # real border
		a2 = 0
	if a2 > C-1e-8:
		a2 = C
	if abs(a2-alpha2)<eps*(a2 + alpha2 + eps):
		return 0  # a2 == alpha2 , nothing changed , so return 0
	a1 = alpha1 + s(alpha2-a2)
	alpha[i1] = a1 #update alpha1
	alpha[i2] = a2 #update alpha2
	
	#update w and b
	delta_w = y1 * (a1 - alpha1) * point1 + y2 * (a2-alpha2) * kernel(point1,point2) + b[0]

	d = delta_w.shape[1]
	for i in range(0,d):
		w[i] += delta_w[i]
	b1 = E1 + y1 * (a1 - alpha1) * kernel(point1, point1) + y2 * (a2 - alpha2) * kernel(point1,point2) + b

	b2 = E2 + y1 * (a1 - alpha1) * kernel(point1, point2) + y2 * (a2 - alpha2) * kernel(point2,point2) + b
	if a1 >0 and a1 < C:
		b = b1
	elif a2 >0 and a2 < C:
		b = b2
	else:
		b = (b1 + b2)/2
	return 1

def find_Ind(List):
	length = List.shape[0]
	Ind   = []
	for i in range(0,length-1):
		if List[i]:
			Ind.append(List[i])
	return Ind
			

def find_Max(i2,Ind,datas_X,w,b,labels)
	length = Ind.shape[0]
	Max    = Ind[0]
	Max_v  = 0
	E2     = w.dot(datas_X[i2,:].T)- labels[i2]
	for i in range(1,length-1)
		E1 = w.dot(datas_X[Ind[i],:].T)-labels[Ind[i]]
		diff_E = abs(E2-E1)
		if diff_E>Max_v:
			Max = i
			Max_v = diff_E
	return Max


def examineExample(i2,datas_X,alpha,labels,w,b,C):
	y2 = lables[i2]
	alpha2 = alpha[i2]
	point2 = datas_X[i2,:]
	E2 = w.dot(point2.T)-b-y2
	r2 = E2 *y2
	#KKT condition:
	# alpha_i=0<==>y_i*u_i>=1
	# 0<alpha_i<C <==> y_i*u_i=1
	# alpha_i=C <==> y_i*u_i<=1
	# r2 = E2*y2=(f(x2)-y2)*y2=y2*f(x2)-1
	# always select the point that violate KKT condition
	if(r2 < -tol and alpha2 < C) or (r2 > tol and alpha2 > 0):
		# second choince heuristic: maximize the step
		ind_a1 = [alpha > 0]
		ind_a2 = [alpha < C]
		ind_a = np.logical_and(ind_a1,ind_a2)
		ind_a = ind_a.T
		if ind_a.any():
			i1 = find_Max(i2,ind_a,datas_X,w,b,labels)
			if i1 !=i2:
				if takeStep(i1,i2,datas_X,labels,alpha,w,b,C):
					return 1
		# if didn't find any point, use random
		length = len(ind_a)
		if length>0:
			if not (length==1 and Ind[0]==i2):
			




# The Main Algorithm
def SMO (alpha)





if __name__ == "__main__":
	eps = 1e-5 #threshold
	tol = 1e-7
	thre = 1e-1 #optimizaiton threshold
	datas=[]
	labels=[]
	load_data(datas,labels)
	datas  = np.matrix(datas)
	labels = np.matrix(labels)
	a = kernel(datas[0],datas[1])
	print(datas)
	print(a)
