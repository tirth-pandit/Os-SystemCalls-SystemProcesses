#define _POSIX_C_SOURCE 200112L
#include<iostream>
#include<stdio.h>
#include<fstream>
#include<fcntl.h>
#include<unistd.h>

using namespace std;

int main(void)
{
	char c[512];
	int id = open("/proc/190/environ",O_RDONLY);

	int n=read(id,c,511);
	c[512] = '\0';
	
	for(int i=0 ;i<n ;i++)
	{
		cout<<c[i];
	}	

}
