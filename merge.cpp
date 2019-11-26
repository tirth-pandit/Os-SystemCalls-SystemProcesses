#include<iostream>
#include<stdio.h>
#include<fstream>
#include<fcntl.h>
#include<unistd.h>
#include<bits/stdc++.h>

using namespace std;

int main(int argc ,char **argv)
{
	string path = argv[1];
	
	int des_fd = open("merged_cp.txt",O_CREAT | O_RDWR ,0666);

	for(int i=2 ;i<argc ;i++)
	{
		string s = argv[1];
		s += argv[i];
		char path[s.size()+1];
		strcpy(path , s.c_str());
	
		cout<<path<<endl;

		int src_fd = open(path,O_RDONLY);
		
		char c[1024];
		int n;

		while((n=read(src_fd ,c ,1023)) > 0)
		{
			//cout<<n<<" "<<c<<endl;
			c[n] = '\0';
			write(des_fd ,c ,n);
		}
		
		close(src_fd);
	}
}
