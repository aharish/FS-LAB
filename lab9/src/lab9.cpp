//============================================================================
// Name        : lab9.cpp
// Author      : 
// Version     : C++
// Copyright   : Your copyright notice
// Description : B - tree
//============================================================================
#include <iostream>
#include <cmath>
using namespace std;
struct node
{
	int ele[4];
	int child[4];
};
class btree
{
public:
	node *tree[10][10];
	int count[10];
	int leaf;
	int path[10];

	btree();
	node* create_node();
	void insert(int);
	void main_search(int);
	void display_tree();
	void insert_node(node*,int);
	void search(int);
	int search_node (node*,int);
	int nodefull(node*);
	void split(node*);
};
btree::btree()
{
	leaf=-1;
	for (int i=0;i<10;i++)
	{
		count[i]=-1;
		path[i]=-1;
	}
}
node* btree::create_node()
{
	node *n;
	n = new node;
	for (int i=0;i<4;i++) 
	{
		n->ele[i]=-1;
		n->child[i]=-1;
	}
	return n;
}
void btree::insert(int key)
{
	int n, parent;
	node *first_node;
	if (leaf==-1) 
	{
		first_node=create_node();
		tree[0][0]=first_node;
		leaf++;count[0]++;
		first_node->ele[0]=key;		
	}
	else if (leaf==0)
	{
		if (nodefull(tree[0][0])) 
		{
			path[leaf]=0;
			split(tree[0][0]);
			insert(key);
		}
		else insert_node(tree[0][0],key);
	}	
	else
	{
		search(key);
		n=path[leaf];
		parent=path[leaf-1];
		if ( (nodefull(tree[leaf][n])) ) 
		{
			split(tree[leaf][n]);
			insert(key);
		}
		else 
			insert_node(tree[leaf][n],key);
	}
}		
void btree::main_search(int key)
{
	int flag=0, i;	
	node *node1;
	search(key);
	node1=tree[leaf][path[leaf]];
	for (i=0;node1->ele[i]!=-1;i++)
		if (node1->ele[i]==key) 
		{
			flag=1; 
			break;
		}
	cout<<"\nThe path traversed is: "; 
	for (i=0;path[i]!=-1;i++)
		cout<<path[i]<<" -> ";

	if (flag) 
		cout <<"\nElement Found";
	else 
		cout<<"\nNot Found";
}
void btree::display_tree()
{
	int i,j,k;	
	for (i=0;i<=leaf;i++)
	{		cout<<"\n\nLevel------ " <<i<<"\n";
	for (j=0;j<=count[i];j++)
	{
		cout<<"   tree["<<i<<"]["<<j<<"]:";
		for (k=0;tree[i][j]->ele[k]!=-1&& k<4;k++)
			cout<<" "<<tree[i][j]->ele[k];
	}
	}
}	
void btree::search(int key)
{
	int i,j,temp;	
	path[0]=0;				//always start the path from root
	if (leaf)
	{						// search only if there are more than 1 level
		j=0;		
		for (i=0;i<leaf;i++)
		{
			temp=search_node(tree[i][j],key);
			path[i+1]=temp;
			j=temp;
		}
	}
}	
int btree::search_node(node *node1, int key)
{
	for (int i=0;i<4;i++)
	{
		if (key<=node1->ele[i]) 
			return node1->child[i];
		else if (node1->ele[i+1]==-1) 
			return node1->child[i];
	}
}
int btree::nodefull(node *node1)
{
	if (node1->ele[3]!=-1) 
		return 1;
	else 
		return 0;
}
void btree::insert_node(node *node1, int key)
{
	int flag=0,count=-1,i,j, x, y, l,t;
	node *newnode, *n1;
	for (i=0;i<4;i++) 
		if (node1->ele[i]!=-1) ++count;
	i=0;
	while (!flag && node1->ele[i]!=-1)
	{
		if (node1->ele[i] > key)			//not considering duplicate entries
		{
			flag=1;			
			for (int j=count;j>=i;j--)
				node1->ele[j+1]=node1->ele[j];
			node1->ele[i]=key;
		}
		i++;
	}
	if (!flag)						//highest element added at end
	{
		node1->ele[count+1]=key;	
		for (i=leaf-1;i>=0;i--)
		{

			n1=tree[i][path[i]];			
			for (t=0;n1->ele[t]!=-1;t++);
			n1->ele[t-1]= key;
		}	
	}
}
void btree::split(node *oldnode)
{
	node *newnode, *parent, *n1, *n2;
	int i,j,k,n,t=0,x,y,pos,m,ct=0;
	newnode = create_node();
	newnode->ele[0]=oldnode->ele[2];		//copy elements to new node
	newnode->ele[1]=oldnode->ele[3];	
	oldnode->ele[2]=-1;				//delete entries in old node
	oldnode->ele[3]=-1;
	t=count[leaf];
	n=path[leaf];
	cout<<"\nleaf= "<<leaf<<"\tcount[leaf]= "<<t <<" path[leaf]=  "<<n;
	for (i=t,j=t+1;i>n;i--,j--)			//move the elements in leaf level one place right
	{
		cout<<"\ninside for";
		tree[leaf][j]=tree[leaf][i];
	}
	tree[leaf][n+1] = newnode;			//insert new node to the tree
	count[leaf]++;
	x=leaf;	
	t=0;
	if(leaf==0)t=1;
	else 
	{	parent=tree[leaf-1][path[leaf-1]];
	if(nodefull(parent)) t=1;
	}
	if(t)
	{
		leaf++;  cout<<"level increased\n";
		count[leaf]=count[x];
		for (i=0;i<=count[leaf];i++)			//copy the leaf nodes to the new level
			std::swap(tree[leaf][i],tree[x][i]);
		for (i=leaf-1;i>=0;i--) count[i]=-1;
		for(i=leaf,j=i-1;i>0;i--,j--)
		{
			k=0;
			while(k<=count[i])
			{
				newnode=create_node();
				count[j]++;
				tree[j][count[j]]=newnode;
				n1=tree[i][k];
				n2=tree[i][k+1];
				for (x=0;n1->ele[x]!=-1;x++);	//find last element in the nodes
				for (y=0;n2->ele[y]!=-1;y++);
				newnode->ele[0]=n1->ele[x-1];
				newnode->child[0]=k;
				newnode->ele[1]=n2->ele[y-1];
				newnode->child[1]=k+1;
				k+=2;
				if(k<=count[i]){
					n1=tree[i][k];
					for (x=0;n1->ele[x]!=-1;x++);
					newnode->ele[2]=n1->ele[x-1];
					newnode->child[2]=k;
					k++;
				}
			}
		}	  
	}
	else
	{
		cout<<"-----------\n";
		i=n; j=0; ct=0;
		while(parent->ele[ct]!=-1)
			ct++;
		k=tree[leaf][n+1]->ele[1];
		while(parent->ele[j]!=k)j++;
		while(j<=ct)
		{
			n1=tree[leaf][i];
			for (x=0;n1->ele[x]!=-1;x++);
				parent->ele[j]=n1->ele[x-1];
			if(leaf==2) 
				cout<<"  "<<n1->ele[0];
			cout<<"\n "<<n1->ele[x-1]<<" "<<j;
			parent->child[j]=i;
			i++; 
			j++;
		}
		cout<<"------\n";
		j=path[leaf-1]+1;
		while(j<=count[leaf-1])
		{
			parent=tree[leaf-1][j];
			for (x=0;parent->ele[x]!=-1;x++) 
				(parent->child[x])++;
			j++;
		}		

	}	
}
int main()
{
	btree bt;
	int choice, key;
	while(1)
	{
		cout<<"\n\n\nMain Menu\n-------------------\n1.Insert\n2.Search\n3.Display Tree\n4.Exit\n\nEnter your choice:";
		cin>>choice;
		switch(choice)
		{
		case 1:	cout<<"\nEnter the element:";
			cin>>key;
			bt.insert(key);
			break;
		case 2:cout<<"Enter the key:";
			cin>>key;
			bt.main_search(key);
			break;
		case 3: bt.display_tree();
			break;
		case 4: return 0;
		default: cout<<"\nEnter valid choice";
		}
	}
}
