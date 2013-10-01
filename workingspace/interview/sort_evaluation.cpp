/***********************************************************
 ***********  Evaluation of Sorting Algorithms  ************
 ***********  File: Sort_Algs_Evaluation.cpp    ************
 ***********  Author: XuanWang					************	
 ***********  Motivation: For Fun     			************

 ***********************************************************/

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void swap(int array[],int a, int b)
{
	int tmp = array[a];
	array[a]= array[b];
  	array[b]= tmp;	
}

void bubblesort(int array[], int n)
{
	for(int i=0; i<n; i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(array[j]>array[j+1])
				swap(array,j,j+1);
		}
	}
}


void selectsort(int array[],int n)
{
	int tmp_p;
	int tmp_v;
	int j;
	for(int i = 0; i<n;i++)
	{
		 tmp_p = i;
		 tmp_v = array[i];
		for( j=i;j<n;j++)
		{
			if(tmp_v>array[j])
			{
				tmp_v = array[j];
				tmp_p = j;
		
			}
		}
		swap(array,i,tmp_p);
	}	
}

void insertsort(int array[],int n)
{
	int j;
	for(int i =1;i<n;i++)
	{
		if(array[i]<array[i-1])
		{
			 j = i-1;
			 int tmp = array[i];
			while(j>=0&&array[j]>tmp)
			{
				array[j+1] = array[j];
				j--;
			}
			array[j+1] = tmp; 
		}
	}

}

void quicksort(int array[],int start,int end)
{
	if( start<end)
	{
		int pivot = array[start];
		int k=start;
		for(int i=start+1;i<end;i++)
		{
			if(array[i]<pivot)
			{	
				k++;
				swap(array,k,i);
	
			}
		}
		swap(array,k,start);

		quicksort(array,start,k-1);
		quicksort(array,k+1,end);		

	}	

}

void merge(int array[],int a_start,int b_start,int n, int tmp[])
{
//	if(a_start<b_start)
//	{
		int i = a_start;
		int j = b_start+1;
		int k = 0;
		while(i<=b_start&&j<=n)
		{
			if(array[i]>array[j])
				tmp[k++] = array[j++];
			else
				tmp[k++] = array[i++];
		}
		while(i<=b_start)
			tmp[k++] = array[i++];
		while(j<=n)
			tmp[k++] = array[j++];
		for(i=0;i<k;i++)
			array[a_start+i] = tmp[i];

//	}
}

void mergesort(int array[],int start, int end, int tmp[])
{
	if(start<end)
	{
		int mid = (end+start)/2;
		mergesort(array,start,mid,tmp);
		mergesort(array,mid+1,end,tmp);
		merge(array,start,mid,end,tmp);
	
	}
}

void heapdown(int array[],int start,int n)
{
	int i=start;
	int value = array[start];
	int j= 2*i+1;
	while(j<n)
	{
		if(j+1<n&&array[j]<array[j+1])
			j++;
		if(array[j]<value)
			break;
		array[i] = array[j];
		i = j;
		j = 2*i+1;
	}
	array[i] = value;
}


void buildheap(int array[],int n)
{
	for(int i = n/2-1;i>=0;i--)
	{
		heapdown(array,i,n);
	}

}

void heapsort(int array[],int n)
{
	buildheap(array,n);
	for(int i=n-1;i>=0;i--)
	{
		swap(array,0,i);
		heapdown(array,0,i);
	}
			
}

void shellsort(int array[],int n)
{
	for(int step = n/2;step>0;step=step/2)
	{
		for(int i= step;i<n;i++)
		{
			if(array[i]<array[i-step])
			{
				int tmp = array[i];
				int k   = i-step;
				while(k>=0&&array[k]>tmp)
				{
					array[k+step]=array[k];
					k= k-step;
				}
				array[k+step]=tmp;
			}	
		
		}
	}

}


int main()
{
	cout<<endl;
	cout<<"Thank for using the \"Sorting Algorithm Evaluation Software\""<<endl;
	cout<<endl;
	cout<<" Algorithms supported: "<<endl;
	cout<<" 1. Bubble Sort "<<endl;
	cout<<" 2. Selection Sort "<<endl;
	cout<<" 3. Insert Sort "<<endl;
	cout<<" 4. Quick Sort "<<endl;
	cout<<" 5. Merge Sort "<<endl;
	cout<<" 6. Heap Sort "<<endl;
	cout<<" 7. Shell Sort "<<endl;
	cout<<"Please input the number of algorithm you want to use"<<endl; 
	int choice;
	cin>>choice;
//	int test[] = {123,43,56,876,84,44,32,331,65,8,5,231,88,42,22,11,8};
    int test[] = {7,12,343,32,56,3,21,53,21,56,46,7,98,5};
	int n = sizeof(test)/sizeof(test[0]);
	int * tmp = new int[n];
    cout<<" The numbers need to be sorted: "<<endl;
	for(int i=0;i<n;i++)
		cout<<test[i]<<" ";
	clock_t start,finish;
	double duration;
	start = clock();
	switch(choice)
	{
		case 1:
				{
					bubblesort(test,n);
					break;
				}
		case 2:
				{
					selectsort(test,n);
					break;
				}
		case 3:
				{
					insertsort(test,n);
					break;
				}
		case 4:
				{
					quicksort(test,0,n);
					break;
				}
		case 5:
				{
					mergesort(test,0,n-1,tmp);
					break;
				}
		case 6:
				{
					heapsort(test,n);
					break;
				}
		case 7:
				{
					shellsort(test,n);
					break;
				}
}			
	finish = clock();
	cout<<endl;
	cout<<endl;
	cout<<" The numbers after sorting: "<<endl;
	for(int i=0;i<n;i++)
	cout<<test[i]<<" ";	
	cout<<endl;
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	cout<<" Time cost for sorting is : "<<duration<<" seconds"<<endl;

}
