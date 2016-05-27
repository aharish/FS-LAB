//============================================================================
// Name        : lab1.cpp
// Author      : Sneha
// Version     : C++
// Copyright   : Your copyright notice
// Description : reversal of a giver string
//============================================================================
#include<iostream> 
#include<string.h> 
#include<fstream> 
using namespace std; 
int main() 
{ 
	char s1[25]; 
	fstream f1,f2; 
	int i=0,j=0,x=0,c=0,kb=0; 
	char filename1[25],filename2[25]; 
	cout<<endl<<"1.for standard i/o:"<<endl<<"2 for file i/o:"<<endl<<"enter your choice"; 
	cin>>kb; 
	switch(kb) 
	{ 
	case 1:cout<<"enter name count:"; 
	cin>>c; 
	for(j=1;j<=c;j++) 
	{ 
		cout<<endl<<"entername"<<j<<":"; 
		cin>>s1; 
		x=strlen(s1); 
		cout<<"reverse name"<<j<<":"; 
		for(i=x-1;i>=0;i--) 
			cout<<s1[i]; 
		cout<<endl; 
	} 
	break; 
	case 2:cout<<"enter data file name:"; 
	cin>>filename1; 
	cout<<"enter reverse data filename2"; 
	cin>>filename2; 
	f1.open(filename1,ios::in); 
	f2.open(filename2,ios::out); 
	while(1) 
	{ 
		f1.getline(s1,25); 
		if(f1.fail()) 
			break; 
		x=strlen(s1); 
		for(i=x-1;i>=0;i--) 
			f2<<s1[i]; 
		f2<<endl; 
	} 
	f1.close(); 
	f2.close(); 
	break; 
	} 
	return 1; 
} 
