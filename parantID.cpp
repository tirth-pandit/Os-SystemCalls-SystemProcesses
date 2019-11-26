#define _POSIX_C_SOURCE 200112L
#include<iostream>
#include<stdio.h>
#include<fstream>
#include<fcntl.h>
#include<unistd.h>

using namespace std;

int main(void)
{
	char buf[244];
	int id = open("/proc/1/status",O_RDONLY);

	int n=read(id,buf ,243);
	int i=0;

	for(i=0 ;i<244 ;i++)
	{
		if( buf[i] == 'P' && buf[i+1] == 'P')
		{
			break;
		}
	}

	string s ="";
	
	while( buf[i] != '\n')
	{
		s += buf[i];
		i++;
	}
	
	cout<<s<<endl;
}
