//============================================================================
// Name        : lab4.cpp
// Author      : Sneha
// Version     : c++
// Copyright   : Your copyright notice
// Description : variable length records based on RRN.
//============================================================================
#include<iostream>
#include<sstream>
#include<string>
#include<fstream>
#include<stdlib.h>
using namespace std;
class student
{
	string usn,name,branch,sem,buffer;
public:
	void read_data();
	void pack();
	void search_rrn();
	void search();
	void unpack(int);
};
int rrn[100],count = 0;
fstream fp;
void student::search_rrn()
{
	int pos;
	fp.open("data.txt",ios::in);;
	while(fp)
	{
		pos = fp.tellg();
		getline(fp,buffer);
		if(buffer.length()==0)
			continue;
		rrn[++count]=pos;
	}
	fp.close();
}
void student::read_data()
{
	cout<<"\nEnter usn: ";
	cin>>usn;
	cout<<"\nEnter name: ";
	cin>>name;
	cout<<"\nEnter branch";
	cin>>branch;
	cout<<"\nEnter sem: ";
	cin>>sem;
}
void student::pack()
{
	int pos = fp.tellg();
	string buffer=usn+'|'+name +'|'+branch +'|'+sem+'|'+'$';
	fp<<buffer<<endl;
	rrn[++count]=pos;
}
void student::unpack(int pos)
{
	fp.seekg(pos, ios::beg);
	getline(fp, usn, '|');
	getline(fp, name, '|');
	getline(fp, branch, '|');
	getline(fp, sem, '|');
}
void student::search()
{
	int rrn_srch, pos;
	cout<<"Enter the RRN of the record to be found:\n";
	cin>>rrn_srch;
	if(rrn_srch>count||rrn_srch<1)
	return;
	cout<<"Record Found:\n";
	pos=rrn[rrn_srch];
	cout<<pos;
	fp.open("data.txt", ios::in);
	unpack(pos);
	fp.close();
	cout<<"\nName: "<<name<<"\nusn: "<<usn<<"\nbranch: "<<branch<<"\nsem: "<<sem<<endl;
}
int main()
{
	int choice;
	student s;
	s.search_rrn();
	while(1)
	{
		cout<<"1. Insert a record\n2. Search for record using RRN\n3. Exit\nEnter Choice : ";
		cin>>choice;
		switch(choice)
		{
		case 1:
			s.read_data();
			fp.open("data.txt",ios::out|ios::app);
			s.pack();
			fp.close();
			break;
		case 2:
			s.search();
			break;
		default: exit(0);
		}
	}
}
