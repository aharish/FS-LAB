//============================================================================
// Name        : lab2.cpp
// Author      : sneha
// Version     : C++
// Copyright   : Your copyright notice
// Description : fixed length records (c++)
//============================================================================
#include <iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;
class student
{
	string usn,name,branch,sem,buffer;
public:
	void read();
	void pack();
	void unpack();
	void write();
	int search(string);
	void modify(string);
};
void student::read()
{
	cout<<"Enter the name"<<endl;
	cin>>name;
	cout<<"Enter the usn"<<endl;
	cin>>usn;
	cout<<"Enter the branch"<<endl;
	cin>>branch;
	cout<<"Enter the semester"<<endl;
	cin>>sem;
}
void student::pack()
{
	string temp;
	int i;
	temp.erase();
	buffer.erase();
	temp+=usn+'|'+name+'|'+branch+'|'+sem;
	for(i=temp.size();i<100;i++)
		temp+='$';
	buffer+=temp;
	cout<<buffer<<endl;
}
void student::write()
{
	fstream f1;
	f1.open("Data.txt",ios::out|ios::app);
	f1<<buffer;
	f1<<endl;
	f1.close();
}
int student::search(string key)
{
	fstream f1;
	int pos;
	f1.open("Data.txt",ios::in);
	while(!f1.eof())
	{
		getline(f1,buffer);
		pos=f1.tellp();
		unpack();
		if(usn==key)
		{
			cout<<"found the record"<<endl;
			f1.close();
			return pos;
		}

	}
	return 0;
}
void student::unpack()
{
	int i=0;
	usn.erase();
	while(buffer[i]!='|')
		usn+=buffer[i++];
	i++;
	name.erase();
	while(buffer[i]!='|')
		name+=buffer[i++];
	i++;
	branch.erase();
	while(buffer[i]!='|')
		branch+=buffer[i++];
	i++;
	sem.erase();
	while(buffer[i]!='$')
		sem+=buffer[i++];
	i++;
}
void student::modify(string key)
{
	int ch,pos;
	fstream fp1;
	pos=search(key);
	cout    <<"1.USN"<<endl
			<<"2.NAME"<<endl
			<<"3.BRANCH"<<endl
			<<"4.SEMESTER"<<endl;
	cout<<"Enter your choice: ";
	cin>>ch;
	switch(ch)
	{
	case 1:
		cout<<"Enter the USN : "<<endl;
		cin>>usn;
		break;
	case 2:
		cout<<"Enter the name "<<endl;
		cin>>name;
		break;
	case 3:
		cout<<"Enter the branch "<<endl;
		cin>>branch;
		break;
	case 4:
		cout<<"Enter the sem"<<endl;
		cin>>sem;
		break;
	}
	pack();
	pos=pos-101;
	fp1.open("Data.txt");
	fp1.seekp(pos,ios::beg);
	fp1<<buffer;

}
int main()
{
	int choice,i;
	string key;
	student s;
	while(1)
	{
		cout    <<"1.INSERT"<<endl
				<<"2.SEARCH"<<endl
				<<"3.MODIFY"<<endl;
		cout<<"Enter your choice";
		cin>>choice;
		switch(choice)
		{
		case 1:
			s.read();
			s.pack();
			s.write();
			break;
		case 2:

			cout<<"Enter the key ; "<<endl;
			cin>>key;
			i= s.search(key);
			if(i!=0)
				cout<<"Found at "<<i-101;
			else
				cout<<"Not found";
			break;
		case 3:
			cout<<"Enter key "<<endl;
			cin>>key;
			s.modify(key);
			break;

		default:return 0;
		}
	}
	return 0;
}
