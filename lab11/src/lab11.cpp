//============================================================================
// Name        : lab11.cpp
// Author      : 
// Version     : C++
// Copyright   : Your copyright notice
// Description : Adding records using hashing
//============================================================================
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
using namespace std;
bool isprime(int n)
{
	if(n==1 || n==2)
		return true;
	if (!(n%2))
		return false;
	for(int i=3; i <= sqrt(n); i++ ){
		if(!(n%2))
			return false;
	}
	return true;
}
int nearprime(int n)
{
	int i;
	if(!(n%2))n++;
	for(i=n;isprime(i)==false;i++);
	return i;
}
int hash(string str,int prime)
{
	unsigned long hash = 5381;
	int c;
	int i = 0;
	while (c = str[i++])
		hash = ((hash << 5) + hash) + c;
	return hash % prime;
}


class Student
{
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
	string getkey()
	{
		return name;
	}
	bool match (string key, string value)
	{
		return (key == "name" && value == name) ||
				(key == "usn" && value == usn) ||
				(key == "sem" && sem == atoi (value.c_str ())) ||
				(key == "branch" && value == branch);
	}
};
class Hashfile {
	string filename;
	int no_of_buckets;
	int bucket_size;
	int recordsize;
public:
	Hashfile(string fname, int no_of_buckets,int bucket_size, int rsize):
		filename(fname),no_of_buckets(nearprime(no_of_buckets)),bucket_size(bucket_size),recordsize(rsize) {
		string s="\n";
		s.resize(recordsize,'$');
		ofstream f(filename.c_str(),ios::app);
		for(int i = 0; i<(no_of_buckets*bucket_size*recordsize); i+=recordsize) {
			f<<s;
		}
		f.close();
	}
	int addrecord(string s,string key)
	{
		int bucket_no = hash(key,no_of_buckets);
		char buff[recordsize];
		fstream f(filename.c_str(),ios::in|ios::out);
		f.seekg(bucket_no * bucket_size * recordsize);
		for(int i = 0; i < bucket_size; i++) {
			int offset = f.tellg();
			f.read(buff,recordsize);
			if ( buff[0] == '\n' ) {
				f.seekp(offset);
				f<<s;
				f.close();
				return 0;
			}
		}
		f.close();
		return -1;
	}
	string search(string key,string value)
	{
		char buffer[recordsize+1];
		int off;
		fstream f(filename.c_str(),ios::in|ios::out);
		buffer[recordsize] = '\0';

		int bucket_no = hash(key,no_of_buckets);
		f.seekg(bucket_no * bucket_size * recordsize);
		for(int i = 0; i < no_of_buckets; i++) {
			off = f.tellg();
			f.read(buffer,recordsize);
			if ( buffer[0] != '\n' ) {
				Student s = Student::unpack(buffer);
				if (s.match(key,value)) {
					return buffer;
				}

			}
		}
		return "";

	}


};
int main()
{
	Hashfile f("abc.txt",1,5,100);
	Student s1 ("a", "b", 1, "c");
	Student s2 ("d", "e", 2, "f");
	Student s3 ("a", "h", 3, "i");
	Student s4 ("j", "k", 3, "l");
	Student s5 ("m", "n", 3, "p");
	f.addrecord(s1.pack(100),"a");
	f.addrecord(s2.pack(100),"d");
	f.addrecord(s3.pack(100),"a");
	f.addrecord(s4.pack(100),"j");
	f.addrecord(s5.pack(100),"m");
	cout << f.search("name","a") << endl;
	return 0;
}
