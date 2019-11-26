#include<iostream>
#include<stdio.h>
#include<fstream>
#include<fcntl.h>
#include<unistd.h>
#include<bits/stdc++.h>
#include <chrono> 
using namespace std::chrono; 

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

int main(int argc ,char **argv)
{
	auto start = high_resolution_clock::now();

	if( argc == 3)
	{
		//simple Copy
		int src_fd = open( argv[1],O_RDONLY);
		int des_fd = open( argv[2] ,O_CREAT | O_RDWR ,0666);

		char c[1024];
		int n;

		while((n=read(src_fd ,c ,1023)) > 0)
		{
			c[n] = '\0';
			write(des_fd ,c ,n);
		}
	}
	if( strcmp(argv[1],"-s") == 0)
	{
		int src_fd = open(argv[2],O_RDONLY);
		
		int file_count = 1;
		int n =0;
		
		while(1)
		{
			string s = argv[3];
			s += to_str(file_count);
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
	}
	if( strcmp(argv[1],"-m") == 0)
	{
		// "./prog -m des sorce f1 f2 f3.....
 
		int des_fd = open(argv[2],O_CREAT | O_RDWR ,0666);

		for(int i=4 ;i<argc ;i++)
		{
			string s = argv[3];
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
	
	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop - start); 
  
    	cout << "Total Time "<< duration.count() << " microseconds" << endl;

	
	return 0;	
}
