//============================================================================
// Name        : lab10.cpp
// Author      : 
// Version     : C++
// Copyright   : Your copyright notice
// Description : B+ tree
//============================================================================
#include <iostream>
#include <cmath>
using namespace std;
struct node
{
	int ele[4];
	int child[4];
	node *next;
};
class bptree
{
public:
	node *tree[10][10];
	int count[10];
	int leaf;
	int path[10];
	node *head;
	
	bptree();
	node* create_node();
	void insert(int);
	void main_search(int);
	void display_tree();
	void insert_node(node*,int);
	void search(int);
	int search_node (node*,int);
	int nodefull(node*);
	void split(node*);
	void display_seqset();
};
node *first_node;
bptree::bptree()
{
	leaf=-1;
	for (int i=0;i<10;i++){  count[i]=-1; path[i]=-1; }
	first_node=create_node();
		tree[0][0]=first_node;
		leaf++;count[0]++;
	head=first_node;
}
node* bptree::create_node()
{
  node *n;
  n = new node;
  for (int i=0;i<4;i++) 
  {
	  n->ele[i]=-1;
	  n->child[i]=-1;
  }
  n->next=NULL;
  return n;
}
void bptree::insert(int key)
{
	int n;
	if (leaf==0)	path[leaf]=0;
	else search(key);
		n=path[leaf];
		if ( (nodefull(tree[leaf][n])) ) 
		{
			split(tree[leaf][n]);
			insert(key);
		}
		else 
			insert_node(tree[leaf][n],key);
}		
void bptree::main_search(int key)
{
	int i;	
	node *node1;
	search(key);
	node1=tree[leaf][path[leaf]];
	for (i=0;i<4;i++)
		if (node1->ele[i]==key) 
		{
		cout<<"\nThe path traversed is: "; 
		for (i=0;path[i]!=-1;i++)
		cout<<path[i]<<" -> ";

		 cout <<"\nElement Found";
			return;
		}
	 cout<<"\nNot Found!";
}
void bptree::display_tree()
{
	int i,j,k=0;	
	for (i=0;i<=leaf;i++)
	{
		cout<<"\n\nLevel------ " <<i<<"\n";
		for (j=0;j<=count[i];j++)
		{
			k=0; if (i!=leaf&&j==0) 	k=1; 	             
			for (;tree[i][j]->ele[k]!=-1 && k<4;k++)	
			cout<<" "<<tree[i][j]->ele[k];
			cout<<"\t";
		}
	}
} 	
void bptree::search(int key)
{
	int i,j=0,temp;	
	path[0]=0;
	if(!leaf) return;				//always start the path from root					
		for (i=0;i<leaf;i++)
		{
			temp=search_node(tree[i][j],key);
	 		path[i+1]=temp;
			j=temp;
		}
}	
int bptree::search_node(node *node1, int key)
{
	if (key<=node1->ele[0]) 	return  node1->child[0];	
	for (int i=0;i<4;i++)
	{	
		if ((key >= node1->ele[i]) && (key < node1->ele[i+1])) 	return node1->child[i];
		else if (i==3 || node1->ele[i+1]==-1) 	return node1->child[i];
	}
}
int bptree::nodefull(node *node1)
{
	if (node1->ele[3]!=-1) 	return 1;
	else 	return 0;
} 
void bptree::insert_node(node *node1, int key)
{
	int flag=0, ct=-1,i=0,j, x, y, l;
	node *newnode, *parent;
	while(node1->ele[ct+1]!=-1)ct++;
	while (!flag && node1->ele[i]!=-1)
	{
		if (node1->ele[i] > key)			//not considering duplicate entries
		{
			flag=1;			
			for (int j=ct;j>=i;j--)  node1->ele[j+1]=node1->ele[j];
   			node1->ele[i]=key;
		}
		i++;
	}
	if (!flag) 	
		node1->ele[ct+1]=key;			//highest element added at end
	if (node1->ele[0]==key)						//new element is the lowest, hence propogate this till root
	{
			
		for (i=leaf-1;i>=0;i--)
		{
			x=path[i+1];			
			if (tree[i][path[i]]->ele[x] > key) tree[i][path[i]]->ele[x]=key;
			else insert_node(tree[i][x],key);
		}
	}
}
void bptree::split(node *oldnode)
{
	node *newnode, *parent, *n1, *n2;
	int i,j,k,n,t=0,x,ct=0;
	newnode = create_node();
	newnode->ele[0]=oldnode->ele[2];		//copy elements to new node
	newnode->ele[1]=oldnode->ele[3];
	oldnode->ele[2]=-1;				//delete entries in old node
	oldnode->ele[3]=-1;
	k=count[leaf];
	n=path[leaf];
	for (i=k,j=k+1;i>n;i--,j--)	tree[leaf][j]=tree[leaf][i];							
	tree[leaf][n+1] = newnode;			//insert new node to the tree
	count[leaf]++;
	x=leaf;	
	if(leaf==0)t=1;
	else 
	{	parent=tree[leaf-1][path[leaf-1]];
		if(nodefull(parent)) t=1;
	}
	if(t)					//split with increase in level
	{
		leaf++;  cout<<"level increased\n";
		count[leaf]=count[x];
		for (i=0;i<=count[leaf];i++)			
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
			newnode->ele[0]=n1->ele[0];
			newnode->child[0]=k;
			newnode->ele[1]=n2->ele[0];
			newnode->child[1]=k+1;
			k+=2;
			if(k<=count[i]){
			   n1=tree[i][k];
			   newnode->ele[2]=n1->ele[0];
			   newnode->child[2]=k;
			   k++;
			   }
		       }
		}	  
	}
	else						//split without level increase ; update parents
	{
		cout<<"-----------";
		i=n; j=-1; ct=0;
		while(parent->ele[ct]!=-1)ct++;
		k=tree[leaf][n]->ele[0];
		while(parent->ele[++j]!=k);		//find the position of new node in parent
		while(j<=ct)
		{
			 n1=tree[leaf][i];
			 parent->ele[j]=n1->ele[0];
			  parent->child[j]=i;
				cout<<j<<"----"<<i<<"---";
				i++; j++;
		}
		cout<<"------\n";
		j=path[leaf-1]+1;				// to find next parent
		while(j<=count[leaf-1])
		{
			parent=tree[leaf-1][j];
			 for (x=0;parent->ele[x]!=-1;x++) (parent->child[x])++;
			j++;
		}		
			
	}
	parent = tree[0][0];
	for(i=0;parent->ele[i]!=-1 &&i<4;i++) { cout<<"   "<<parent->ele[i]; }
	for(i=0;i<count[leaf];i++) 
	{
		n1=tree[leaf][i];
		n1->next=tree[leaf][i+1];
	}
	head=tree[leaf][0];	
}
void bptree::display_seqset()
{
	node *t;
	int k;
	t=head;
	cout<<"\n\nThe sequence set is:";	
	while (t)
	{
		for (k=0;t->ele[k]!=-1;k++)
			cout<<" "<<t->ele[k];
		cout<<"\t";
		t=t->next;
	}
}		
int main()
{
	bptree bt;
	int choice, key;

	while(1)
	{
		cout<<"\n\n\nMain Menu\n-------------------\n1.Insert\n2.Search\n3.Display Tree\n4.Display Sequence Set\n5.Exit\n\nEnter your choice:";
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
		case 4: bt.display_seqset();
			break;
		case 5: return 0;
		default: cout<<"\nEnter valid choice";
		}
	}
}
