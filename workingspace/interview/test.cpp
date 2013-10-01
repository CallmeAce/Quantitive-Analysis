#include <iostream.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
class Node
{
	public:
		int q_number;
		int layer;
		int value;
		vector<Node*> n_list;

		Node(int n):q_number(n),n_list(n) //initialize node vector
	{
	}
};

Node* buildtree(int n,int depth)
{
	Node * node = new Node(depth);

	if(n==depth)
	{
		for(int i = 0; i<depth;i++)
		{
			node->n_list[i] = NULL;
			node->value = i;
			node->layer = depth;
		}
	}
	else
	{ 
		for (int i =0;i<depth;i++)
		{               
			node->n_list[i] = buildtree(n+1,depth);// span the tree recursively           
			node->n_list[i]->value = i;
			node->n_list[i]->layer = n;   // the layer value
		}
	}

	return node;
}

void printnode(Node*a,int n)
{
	if(a)
	{
		printf("%d ",a->layer);
		for(int i =0;i<n;i++)
		{
			printnode(a->n_list[i],n);
		}
	}
}

int main()
{
	Node * a = buildtree(0,8);
	printnode(a,8);
}
