//============================================================================
// Name        : coseq.cpp
// Author      : sneha
// Version     :
// Copyright   : Your copyright notice
// Description : cosequential matching
//============================================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include<string.h>
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
	void display();
	void match();
};
void coseq::insert()
{
	int i,n1,n2;
	fstream l1,l2;
	cout<<"enter how many names to enter in list1"<<endl;
	cin>>n1;
	for(i=0;i<n1;i++)
	{
		buffer.erase();
		cout<<"Enter name";
		cin>>name;
		buffer+=name;
		l1.open("list1.txt",ios::out|ios::app);
		l1<<buffer<<endl;
		l1.close();
	}
	cout<<"enter how many names to enter in list2"<<endl;
	cin>>n2;
	for(i=0;i<n2;i++)
	{
		buffer.erase();
		cout<<"Enter name";
		cin>>name;
		buffer+=name;
		l2.open("list2.txt",ios::out|ios::app);
		l2<<buffer<<endl;
		l2.close();
	}
}
void coseq::load()
{
	int i;
	fstream l1,l2;
	string name;
	count1=-1;
	count2=-1;
	l1.open("list1.txt",ios::in);
	while(!l1.eof())
	{
		name.erase();
		getline(l1,name);
		a[++count1]=name;
	}
	cout<<"Names in the 1st file are"<<endl;
	for(i=0;i<count1;i++)
		cout<<a[i]<<endl;
	l2.open("list2.txt",ios::in);
	while(!l2.eof())
	{
			name.erase();
			getline(l2,name);
			b[++count2]=name;
	}
	cout<<"Names in the 2nd file are"<<endl;
	for(i=0;i<count2;i++)
		cout<<b[i]<<endl;
	l1.close();
	l2.close();
}
void coseq::sort()
{
	int i,j;
	string temp;
	for(i=0;i<count1;i++)
	{
		for(j=i+1;j<count1;i++)
		{
			if(a[i]>a[j])
			{
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
	}
	cout<<"After sorting 1st file"<<endl;
	for(i=0;i<count1;i++)
		cout<<a[i]<<endl;
	for(i=0;i<count2;i++)
	{
		for(j=i+1;j<count2;i++)
		{
			if(b[i]>b[j])
			{
				temp=b[i];
				b[i]=b[j];
				b[j]=temp;
			}
		}
	}
	cout<<"After sorting 2nd file"<<endl;
	for(i=0;i<count2;i++)
		cout<<b[i]<<endl;
}
int main()
{
	coseq c;
	//c.insert();
	c.load();
	cout<<"hi";
	c.sort();
	cout<<"Hello";
	return 0;
}
