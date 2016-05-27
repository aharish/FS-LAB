//============================================================================
// Name        : lab12.cpp
// Author      : 
// Version     : C++
// Copyright   : Your copyright notice
// Description : Reclamimg Space In Records
//============================================================================
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
using namespace std;
class node{
	node *p;
	int offset;
public:
	node(int ioffset):offset(ioffset) {}
	friend class list;
};
class list{
	node *head;
public:
	list()
	{
		head = NULL;
        }
	void insert(int offset)
	{
		node *temp = new node(offset);
		temp->p = head;
		head = temp;
	}
	int get()
	{
		int offset;
		if (head == NULL) {
			return -1;
		}
		node *temp=head;
		head = head->p;
		offset = temp->offset;
		delete temp;
		return offset;
	}
};
class Student
{
public:
	string name;
	string usn;
	int sem;
	string branch;
public:
	Student ()
	{
	}
	Student (string iname, string iusn, int isem, string ibranch):name (iname),
			usn (iusn), sem (isem), branch (ibranch)
	{
	}
	string pack(int n)
	{
		string s;
		stringstream ss;
		ss << sem;
		s = name + "|" + usn + "|" + ss.str () + "|" + branch;
		s.resize(n,'$');
		return s;
	}
	static Student unpack (string in)
	{
		stringstream ss;
		ss << in;
		string name, usn, sem, branch;
		getline (ss, name, '|');
		getline (ss, usn, '|');
		getline (ss, sem, '|');
		getline (ss, branch, '$');
		return Student (name, usn, atoi (sem.c_str ()), branch);
	}
	bool match (string key, string value)
	{
		return (key == "name" && value == name) ||
				(key == "usn" && value == usn) ||
				(key == "sem" && sem == atoi (value.c_str ())) ||
				(key == "branch" && value == branch);
	}
};
class fixedlengthrecordfile {
	string filename;
	list lar;
	int recordsize;
public:
	fixedlengthrecordfile(string fname, int (rsize)):filename(fname),recordsize(rsize) {}
	void addrecord(string s)
	{	
		int offset = lar.get();
		if(offset >=0) {
			fstream of(filename.c_str(),ios::in|ios::out);
			of.seekp(offset,ios::beg);
			of.write(s.c_str(),recordsize);
			of.close();
	
		}
		else{
			ofstream of(filename.c_str(),ios::app);	
			of.write(s.c_str(),recordsize);
			of.close();
		}
	}
	void deleterecord(string key,string value)
	{
		char buffer[recordsize+1];
		int off;
		fstream of(filename.c_str(),ios::in|ios::out);
		buffer[recordsize] = '$';
		while(!of.eof()) {
                        off = of.tellg();
			of.read(buffer,recordsize);
			if ( '\n' == buffer[0]) {
				continue;
                        }
			Student s = Student::unpack(buffer);
			if (s.match(key,value)) {
				of.seekp(off,ios::beg);
				of.write("\n",1);
  				lar.insert(off);
                                break;
			}
			
		}
                of.close();
	}


};
int main()
{
	string  rs[10];
	const char* a= "a";
	int st=1;
	Student s;
	fixedlengthrecordfile f("abc.txt",100);
	Student s1 ("a", "b", 1, "c");
	Student s2 ("d", "e", 2, "f");
	Student s3 ("g", "h", 3, "i");
	Student s4 ("j", "k", 3, "l");
	Student s5 ("m", "n", 3, "p");
	f.addrecord(s1.pack(100));
	f.addrecord(s2.pack(100));
	f.addrecord(s3.pack(100));
	f.addrecord(s4.pack(100));
	f.addrecord(s5.pack(100));
	f.deleterecord("name","d");
	Student s6 ("s", "z", 3, "q");
	f.addrecord(s6.pack(100));
	return 0;
}
