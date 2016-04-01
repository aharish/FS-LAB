//============================================================================
// Name        : lab8.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <cstring>
#include <fstream>
#include<vector>
using namespace std;
class mergep
{
	char list[20][80];
	//vector <char[][]> list[][];
	int n;
	public:
	void merger();
	void input(char filename[]);
};
void mergep::merger()
{
	int i,j,k,m;
	//vector <char[][]> merge[][];
	//vector <char[][]> output[][];
	char merge[80][20];
	char output[100][20];
	i=0;j=0;k=0;m=0;
	while(i<n && j<m)
	{
		if(strcmp(list[i],merge[j])<0 || strcmp(list[i],merge[j])==0)
			strcpy(output[k++],list[i++]);
		else
			strcpy(output[k++],merge[j++]);
	}
	while(i<n)
		strcpy(output[k++],list[i++]);
	while(j<m)
		strcpy(output[k++],merge[j++]);
	i=0;
	while(i<k)
	{
		strcpy(merge[i],output[i]);
		i++;
	}
	m=k;
}
void mergep::input(char filename[])
{
	int i=0;
	fstream out;
	out.open(filename,ios::out);
	cout<<"Enter the no of names:";
	cin>>n;
	cout<<"Enter the names in ascending order:\n";
	while(i<n)
	{
		cin>>list[i];
		out<<list[i++];
		out<<'\n';
	}
	out.close();
}
int main()
{
	int i=0,m=0;
	mergep s;
	char merge[80][20];
	char filename[30];
	fstream file;
	file.open("output.txt",ios::out);
	cout<<"Enter name of the first file:";
	cin>>filename;
	s.input(filename);
	s.merger();
	cout<<"Enter name of the second file:";
	cin>>filename;
	s.input(filename);
	s.merger();
	cout<<"Enter name of the third file:";
	cin>>filename;
	s.input(filename);
	s.merger();
	cout<<"Enter name of the fourth file:";
	cin>>filename;
	s.input(filename);
	s.merger();
	cout<<"Enter name of the fifth file:";
	cin>>filename;
	s.input(filename);
	s.merger();
	cout<<"Enter name of the sixth file:";
	cin>>filename;
	s.input(filename);
	s.merger();
	cout<<"Enter name of the seventh file:";
	cin>>filename;
	s.input(filename);
	s.merger();
	cout<<"Enter name of the eigth file:";
	cin>>filename;
	s.input(filename);
	s.merger();
	cout<<"Merged output:"<<endl;
	while(i<m)
	{
		file<<merge[i];
		cout<<merge[i]<<endl;
		file<<'\n';
		i++;
	}
	file.close();
}

