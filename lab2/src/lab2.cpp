//============================================================================
// Name        : lab2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include<iostream>
#include<fstream>
#include<sstream>
#include<string.h>
using namespace std;
class student
{
	string usn,name,branch,buffer;
	string sem;
public:
	void read();
	void pack();
	void unpack();
	void write();
	int search(string);
	void modify(string);
	int del(string);
};
void student::read()
{
	cout<<"enter usn";
	cin>>usn;
	cout<<"Enter name";
	cin>>name;
	cout<<"Enter branch";
	cin>>branch;
	cout<<"Enter semester";
	cin>>sem;
}
void student::pack()
{
	string temp;
	fstream f1;
	temp=usn+'|'+name+'|'+branch+'|'+sem;
	buffer=temp;
	buffer.resize(100,'$');
	// Do not hard code file names.
	f1.open("datafile.txt",ios::out|ios::app);
	f1<<buffer<<endl;
	f1.close();
}
int student::search(string key)
{
	fstream f1;
	int pos,f=0;
	f1.open("datafile.txt",ios::in);
	while(!f1.eof())
	{
		getline(f1,buffer);
		pos=f1.tellp();
		unpack();
		if(key==usn) {
			cout<<"key found";
			//f=1;
			f1.close();
			return pos;
		}

	}

	cout<<"key not found";
	f1.close();
	return 0;
}
void student::unpack()
{
	int i=0;
	usn.erase();
	while(buffer[i]!='|')
		usn+=buffer[i++];
	i++;
	while(buffer[i]!='|')
		name+=buffer[i++];
	i++;
	while(buffer[i]!='|')
		branch+=buffer[i++];
	i++;
	while(buffer[i]!='$')
		sem+=buffer[i++];
	i++;
}
void student:: modify(string key)
{
	int pos,ch;
	string temp;
	fstream f1;
	pos=search(key);
	pos=pos-101;
	cout<<"change 1.usn 2. name 3. br 4.sem \n";
	cin>>ch;
	switch(ch)
	{
	case 1:cout<<"usn";
	cin>>usn;
	break;
	case 2:cout<<"name";
	cin>>name;
	break;
	case 3:cout<<"branch";
	cin>>branch;
	break;
	case 4:cout<<"semester";
	cin>>sem;
	break;
	default: cout<<"wrong choice";
	break;
	}
	buffer.erase();
	temp.erase();
	temp=usn+'|'+name+'|'+branch+'|'+sem;
	buffer=temp;
	buffer.resize(100,'$');
	f1.open("datafile.txt");
	f1.seekp(pos,ios::beg);
	f1<<buffer<<endl;
	f1.close();
}
int main()
{
	int choice;
	student s;
	string key;
	while(1)
	{
		cout<< "1.insert  2.search 3.modify"<<endl;
		cout<<"Enter your choice"<<endl;
		cin>>choice;
		switch(choice)
		{
		case 1:s.read();
		s.pack();
		break;
		case 2:cout<<"Enter the key";
		cin>>key;
		s.search(key);
		break;
		case 3:cout<<"Enter the key";
		cin>>key;
		s.modify(key);
		break;
		}
	}
	return 0;
}