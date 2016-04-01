//============================================================================
// Name        : coseq.cpp
// Author      : sneha
// Version     : C++
// Copyright   : Your copyright notice
// Description : cosequential matching using files
//============================================================================
#include <iostream>
#include <fstream>
#define max 100
using namespace std;
class coseq
{
	string name,buffer;
	int count1,count2;
	string a[max],b[max];
public :
	void load();
	void sort();
	void insert();
	void read();
	void match();
};
void coseq::read()
{
	int i,n;
	cout<<"enter how many names to enter in list1"<<endl;
	cin>>n;
	for(i=0;i<n;i++)
	{
		buffer.erase();
		cout<<"Enter name";
		cin>>name;
		buffer+=name;
	}
}
void coseq::insert()
{
	fstream fp;
	read();
	fp.open("list1.txt",ios::out|ios::app);
	fp<<buffer<<endl;
	fp.close();
	read();
	fp.open("list2.txt",ios::out|ios::app);
	fp<<buffer<<endl;
	fp.close();
}
void coseq::load()
{
	fstream fp;
	count1 = 0;
	fp.open("list1.txt",ios::in);
	while(fp)
	{
		getline(fp,name);
		a[count1++]=name;
	}
	fp.close();
	count2 = 0;
	fp.open("list2.txt",ios::in);
	while(fp)
	{
		getline(fp,name);
		b[count2++]=name;
	}
	fp.close();
}
void sorting(string arr[],int n)
{
	int i,j;
	string temp;
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(arr[i]>arr[j])
			{
				temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}
	}
}
void coseq::sort()
{
	int i;
	sorting(a,count1);
	cout<<"\nThe Sorted Contents of List 1 : \n";
	for(i=0;i<=count1;i++)
			cout<<a[i]<<"\n";
	sorting(b,count2);
	cout<<"\nThe Sorted Contents of List 2 : \n";
	for(i=0;i<=count2;i++)
		cout<<b[i]<<"\n";
}
void coseq::match()
{
	int i=0,j=0;
	while(i<=count1 && j<=count2)
	{
		if(a[i]==b[j])
		{
			cout<<a[i]<<endl;
			i++;
			j++;
		}
		if(a[i]<b[j])i++;
		if(a[i]>b[j])j++;
	}
}
int main()
{
	coseq c;
	c.insert();
	c.load();
	c.sort();
	cout<<"\nCommon Names in Both Lists Are : \n";
	c.match();
	return 0;
}
