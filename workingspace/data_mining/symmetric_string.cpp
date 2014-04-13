/*
 * Interesting Interview Problem
 * Given a string, your task is to add alphabets at the end of it, and 
 * make it symmetric. of course, add a whole string is the most convinent
 * way of doing that. But our goal is to make the symmetric string as short
 * as possible
 * 
 * It could be solved by dynamic programming!
 *
 * Author: Xuan Wang
 * Input: a string, no space
 * Output: a symmetric string
 *
 */

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<vector>
using namespace std;

class SymmetricString
{
	public:
		char input_string[100];
		char output_string[100];
		vector<int> ind_list;
		int length;
	
		/* Methods */
		void Sym_Run(int ind);
		void init();
		void P_Result();
};

void SymmetricString::init()
{
	memset(input_string,0,sizeof(char)*100);
	cin>>input_string;
	for(int i=0;i<100;i++)
	{
		if(input_string[i]==0)
			break;
		length=i;
	}

}

void SymmetricString::Sym_Run(int ind)
{
	int len_ind =0;
	for(int i=ind;i<100;i++)
	{
		if(input_string[i]==0)
			break;
		len_ind=i;
	}
	if(!((len_ind-ind)%2))   // if the length is odd, pushback the first alphabet, because the length of the string has to be even. like "ABA, ABCBA"
	{
		int j =0;
		for(int i=ind;i<length;i++)
		{
			if (i == length-j)
			{
				return;
			}
			if(input_string[i]!=input_string[length-j])
			{
				for(int k =ind;k<=i;k++)
				{
					ind_list.push_back(k);
				}
				Sym_Run(i+1);
				break;
			}
			j++;	
		}
	}
	else
	{
		ind_list.push_back(ind);
		Sym_Run(ind+1);
	}	
}

void SymmetricString::P_Result()
{

	cout<<"Input String is : "<<endl;
	for(int i=0;i<=length;i++)
		cout<<input_string[i];
		cout<<endl;


	cout<<"Output String is : "<<endl;
	for(int i=0;i<=length;i++)
		cout<<input_string[i];
//		cout<<endl;
//	cout<<"the string needs to be added: ";
	for(int i=ind_list.size();i>0;i--)
		cout<<input_string[i-1];
		cout<<endl;
}


int main()
{
	SymmetricString * a = new SymmetricString();
	a->init();
	a->Sym_Run(0);
	a->P_Result();

}
