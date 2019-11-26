#include<iostream>
#include<stdio.h>
#include<fstream>
#include<fcntl.h>
#include<unistd.h>
#include <dirent.h>
#include<bits/stdc++.h>

using namespace std;

main()
{
	DIR* proc = opendir("/proc");
	struct dirent* ent;
	
	long long int total = 0;

	while(ent = readdir(proc))
	{
		if(!isdigit(*ent->d_name))
			continue;
		
		string pid = ent->d_name;
	
		string temp = "/proc/";
		temp += pid;
		temp += "/status";
	
		char p[temp.length() + 1];	
		strcpy(p ,temp.c_str());
	
		char buf[10000];
		int id = open(p,O_RDONLY);
		int n=read(id,buf,9999);
		
		buf[n] = '\0';
		
		int i=0;
		for(i=0 ;i<n ;i++)
		{
			if(buf[i]=='v' && buf[i+1]=='o'&& buf[i+2]=='l' && buf[i+3]=='u'&& buf[i+4]=='n')
			{
				break;
			}
		}
		
		string num = "";
		while( buf[i] != '\n')
		{
			if( isdigit(buf[i]) )
			{
				num += buf[i];
			}
			i++;
		}
		
		char nu[num.length()+1];
		strcpy(nu,num.c_str());
		total += atoi(nu);
		
	}
	
	cout<<total<<endl;
}
