#include<iostream>
#include<stdio.h>
#include<fstream>
#include<fcntl.h>
#include<unistd.h>
#include<bits/stdc++.h>

using namespace std;

string to_str(int n)
{
	string s = "";
	
	while(n>0)
	{
		int temp = n%10;
		n=n/10;
			
		s += char('0'+temp);
	}

	reverse(s.begin(), s.end());
	return s;
}

int main()
{
	int src_fd = open("cp.txt",O_RDONLY);
	
	int file_count = 1;
	int n =0;
	
	while(1)
	{
		string s = "/home/tirth/try/" + to_str(file_count);
		char path[s.size()+1];
		strcpy(path ,s.c_str());

		cout<<path<<" "<<endl;

		int des_fd = open( path ,O_CREAT | O_RDWR ,0666);

		int total = 0;
		
		char c[10];

		while(total<30)
		{
			n = read(src_fd ,c ,10);
			
			//cout<<n<<" INNER "<<endl;

			if( n == 0)
			{
				break;
			}

			total += n;
			
			c[n]='\0';

			write(des_fd,c,n);
		}

		if( n == 0)
		{
			break;
		}

		
		close(des_fd);

		file_count++;
		
	}

	return 0;	
}
