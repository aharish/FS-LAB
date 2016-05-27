//============================================================================
// Name        : lab8.cpp
// Author      : Sneha
// Version     : C++
// Copyright   : Your copyright notice
// Description : Merge Sort for files
//============================================================================
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<vector>
#include<string>
#include<sys/types.h>
using namespace std;
string merge(vector<string>fnames,int left,int right)
{
	string s1,s2,s3;
	if(left==right)
	{
		return fnames[left];
	}
	if ((right-left)==1)
	{
		ifstream if1(fnames[left].c_str());
		ifstream if2(fnames[right].c_str());
		string newfile=fnames[left]+"a";
		ofstream of(newfile.c_str());
		getline(if1,s1);
		getline(if2,s2);
		while(!if1.eof() && !if2.eof())
		{
			if(s1==s2)
			{
				if(s1!="")
					of<<s1<<endl;
				getline(if1,s1);
				getline(if2,s2);
			}
			else if(s1<s2)
			{
				if(s1!="")
					of<<s1<<endl;
				getline(if1,s1);
			}
			else if(s2<s1)
			{
				if(s2!="")
					of<<s2<<endl;
				getline(if2,s2);
			}
		}
		while(!if1.eof())
		{
			if(s1!="")
				of<<s1<<endl;
			getline(if1,s1);
		}
		while(!if2.eof())
		{
			if(s2!="")
				of<<s2<<endl;
			getline(if2,s2);

		}
		if1.close();
		if2.close();
		of.close();
		return newfile;

	}
	else
	{
		int mid=(left+right)/2;
		string f1,f2;
		f1=merge(fnames,left,mid);
		f2=merge(fnames,mid+1,right);
		vector<string>op;
		op.push_back(f1);
		op.push_back(f2);
		return merge(op,0,1);
	}

}
int main()
{
	vector <string> v;
	v.push_back("f0.txt");
	v.push_back("f1.txt");
	v.push_back("f2.txt");
	v.push_back("f3.txt");
	v.push_back("f4.txt");
	v.push_back("f5.txt");
	v.push_back("f6.txt");
	v.push_back("f7.txt");
	cout<<"Resulting file is ";
	cout<<merge(v,0,7)<<endl;
	return 0;
}


