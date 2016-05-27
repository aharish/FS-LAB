//============================================================================
// Name        : lab5.cpp
// Author      : Sneha
// Version     : C++
// Copyright   : Your copyright notice
// Description : Primary Key Indexing
//============================================================================

#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<stdio.h>
using namespace std;
class primary_index
{
public:string usn_list[100];
	int address_list[100],count;
	void create_p_index();
	void insert();
	void remove(string);
	void search(string);
	int search_primary_index(string);
	string extract_usn(string);
};
void primary_index::create_p_index()
{
	fstream file;
	int pos;
	string buffer,usn;
	count=-1;
	file.open("5.txt",ios::in);
	while(!file.eof())
	{
		pos=file.tellg();
		buffer.erase();
		getline(file,buffer);
		if(buffer.empty()) break;
		usn=extract_usn(buffer);
		if(usn[0]=='*')continue;
		++count;
		usn_list[count]=usn;
		address_list[count]=pos;
	}
	file.close();
}
string primary_index::extract_usn(string buffer)
{
	string usn;
	int i=0;
	usn.erase();
	while(buffer[i]!='|')
		usn+=buffer[i++];
	return usn;
}
void primary_index::insert()
{
	string usn,name,branch,semester,buffer;
	int address,pos;
	fstream file;
	cout<<"\nusn";
	cin>>usn;
	cout<<"\nname";
	cin>>name;
	cout<<"\nbranch";
	cin>>branch;
	cout<<"\nsem";
	cin>>semester;
	buffer.erase();
	buffer=usn+'|'+name+'|'+branch+'|'+semester+'$'+'\n';
	file.open("5.txt",ios::out|ios::app);
	pos=file.tellp();
	file<<buffer;
	file.close();
	count++;
	usn_list[count]=usn;
	address_list[count]=pos;
}
int primary_index::search_primary_index(string key)
{
	int low=0,high=count,mid=0,flag=0,pos;
	while(low<=high)
	{
		mid=(low+high)/2;
		if(usn_list[mid]==key)
		{
			flag=1;
			break;
		}
		if(usn_list[mid]>key)
			high=mid-1;
		if(usn_list[mid]<key)
			low=mid+1;
	}
	if(flag==1)return mid;
	else return -1;
}
void primary_index::search(string key)
{
	int pos=0,address;
	string buffer;
	fstream file;
	buffer.erase();
	pos=search_primary_index(key);
	if(pos>=0)
	{
		file.open("5.txt");
		address=address_list[pos];
                file.seekp(address,ios::beg); 
		getline(file,buffer);
		cout<<"record found...\n"<<buffer;
		file.close();
	}
	else cout<<"record not found\n";
}
void primary_index::remove(string key)
{
	int pos=0,address,i;
	char del_ch='*';
	fstream file;
	pos=search_primary_index(key);
	if(pos>=0)
	{
		file.open("5.txt");
	        address=address_list[pos]; 
                file.seekp(address,ios::beg); 
		file.put(del_ch);
		cout<<"record deleted";
		file.close();
		for(i=pos;i<count;i++)
		{
			usn_list[i]=usn_list[i+1];
			address_list[i]=address_list[i+1];
		}
		count--;
	}
	else cout<<"record to be deleted is not found";
}
int main()
{
	int ch;
	string key;
	primary_index i1;
	i1.create_p_index();
	while(1)
	{
		cout<<"\n1.add  2.search 3.delete  4.exit\n";
		cout<<"enter your choice";
		cin>>ch;
		switch(ch)
		{
		case 1:cout<<"enter the data";
		i1.insert();
		break;
		case 2:cout<<"\nenter the usn to be searched";
		cin>>key;
		i1.search(key);
		break;
		case 3:cout<<"\nenter the usn to be deleted";
		cin>>key;
		i1.remove(key);
		break;
		default:return 0;
		}
	}
	return 0; 
}
