#! /usr/bin/python
#_*_coding:utf-8 _*_
# time complexity O(n)
import os
#import win32api
import glob
import re
import sys
def compute_volume(a):
	length    = len(a)
	left  = 0;
	right = length-1
	left_max  = a[0]
	right_max = a[length-1]
	volume    = 0
	while left <= right:
		if left_max<right_max:
			if left_max < a[left]:
				left_max = a[left]
				left+=1
			else:
				volume = volume + left_max - a[left]
				left+=1
		else:
			if right_max < a[right]:
				right_max = a[right]
				right-=1
			else:
				volume = volume + right_max - a[right]
				right-=1
	return volume


if __name__ == '__main__':
	a = [2,1,4,8,1,5]
	b = compute_volume(a)
	print(b)


# °¢Ä¢¶à twitterÊÔÌâ