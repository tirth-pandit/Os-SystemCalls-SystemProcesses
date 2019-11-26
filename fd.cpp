#define _POSIX_C_SOURCE 200112L
#include<iostream>
#include<stdio.h>
#include<fstream>
#include<fcntl.h>
#include<unistd.h>
#include <dirent.h>
#include<bits/stdc++.h>

using namespace std;

int main(void)
{
	DIR *d;
	struct dirent *dir;
        d = opendir("/proc/1/fd");

        if (d)
        {
        	while ((dir = readdir(d)) != NULL)
        	{
			char buf[1024];
			string s = "/proc/1/fd/";
			s += (dir->d_name);
			
			char path[s.length() + 1];
			
			strcpy(path ,s.c_str());	
			
			ssize_t len = readlink(path, buf, 1023);
		
			buf[len]='\0';
			printf("Descriptor: %s\n", buf);

               	        //printf("%s\n", dir->d_name);
        	}
        	closedir(d);
    	}
	

}
