#define _POSIX_C_SOURCE 200112L
#include<iostream>
#include<stdio.h>
#include<fstream>
#include<fcntl.h>
#include<unistd.h>

using namespace std;

int main(void)
{
	char c[128];
	int id = open("/proc/1/sessionid",O_RDONLY);

	int n=read(id,c,127);
	c[128] ='\0';
	
	cout<<c;
}
