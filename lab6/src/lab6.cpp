//============================================================================
// Name        : lab6.cpp
// Author      : Sneha
// Version     : C++
// Copyright   : Your copyright notice
// Description : Secondary Key Indexing
//============================================================================
#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<stdio.h>
using namespace std;
class secondary_index
{
public:string name_list[100];
	int address_list[100],count;
	void create_s_index();
	void insert();
	void remove(string);
	void search(string);
	int search_secondary_index(string);
	string extract_name(string);
};
void secondary_index::create_s_index()
{
	fstream file;
	int pos;
	string buffer,name;
	count=-1;
	file.open("6.txt",ios::in);
	while(!file.eof())
	{
		pos=file.tellg();
		buffer.erase();
		getline(file,buffer);
		if(buffer.empty()) break;
		name=extract_name(buffer);
		if(buffer[0]=='*')continue;
		++count;
		name_list[count]=name;
		address_list[count]=pos;
	}
	file.close();
}
string secondary_index::extract_name(string buffer)
{
	string name;
	int i=0;
	name.erase();
	i++;
	while(buffer[i]!='|')
		name+=buffer[i++];
	return name;
}
void secondary_index::insert()
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
	file.open("6.txt",ios::out|ios::app);
	pos=file.tellp();
	file<<buffer;
	file.close();
	count++;
	name_list[count]=name;
	address_list[count]=pos;
}
int secondary_index::search_secondary_index(string key)
{
	int low=0,high=count,mid=0,flag=0,pos;
	while(low<=high)
	{
		mid=(low+high)/2;
		if(name_list[mid]==key)
		{
			flag=1;
			break;
		}
		if(name_list[mid]>key)
			high=mid-1;
		if(name_list[mid]<key)
			low=mid+1;
	}
	if(flag==1)return mid;
	else return -1;
}
void secondary_index::search(string key)
{
	int pos=0,address;
	string buffer;
	fstream file;
	buffer.erase();
	pos=search_secondary_index(key);
	if(pos>=0)
	{
		file.open("6.txt");
		address=address_list[pos];
                file.seekp(address,ios::beg); 
		getline(file,buffer);
		cout<<"record found...\n"<<buffer;
		file.close();
	}
	else cout<<"record not found\n";
}
void secondary_index::remove(string key)
{
	int pos=0,address,i;
	char del_ch='*';
	fstream file;
	pos=search_secondary_index(key);
	if(pos>=0)
	{
		file.open("6.txt");
	        address=address_list[pos]; 
                file.seekp(address,ios::beg); 
		file.put(del_ch);
		cout<<"record deleted";
		file.close();
		for(i=pos;i<count;i++)
		{
			name_list[i]=name_list[i+1];
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
	secondary_index i1;
	i1.create_s_index();
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
		case 2:cout<<"\nenter the name to be searched";
		cin>>key;
		i1.search(key);
		break;
		case 3:cout<<"\nenter the name to be deleted";
		cin>>key;
		i1.remove(key);
		break;
		default:return 0;
		}
	}
	return 0; 
}
