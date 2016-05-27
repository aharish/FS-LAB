//============================================================================
// Name        : coseq.cpp
// Author      : sneha
// Version     : C++
// Copyright   : Your copyright notice
// Description : cosequential matching using files
//============================================================================
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;
class namelist{
	vector <string> names;
public:
	void load(string filename)
	{
		string s;
		ifstream f1(filename.c_str());
		while(!f1.eof())
		{
			getline(f1,s);
			names.push_back(s);
		}
		int i,j;
		string temp;
		int n=names.size();
		for(i=0;i<n-1;i++)
		{
			for(j=i+1;j<n;j++)
			{
				if(names[i]>names[j])
				{
					temp=names[i];
					names[i]=names[j];
					names[j]=temp;

				}
			}
		}
		cout<<endl<<"Names in file";
		for(i=0;i<n;i++)
			cout<<names[i]<<endl;
	}
	void cosq(namelist &l2)
	{
		int i=0,j=0;
		cout<<endl<<"Common names";
		while(i<names.size() && j<l2.names.size())
		{
			if(names[i]==l2.names[j])
			{
				cout<<names[i]<<endl;
				i++;
				j++;
			}
			else if(names[i]<l2.names[j])
				i++;
			else
				j++;
		}
	}
};
int main()
{
	namelist n1;
	n1.load("list1.txt");
	namelist n2;
	n2.load("list2.txt");
	n1.cosq(n2);
}

