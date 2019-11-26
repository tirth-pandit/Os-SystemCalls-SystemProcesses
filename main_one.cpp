#define _POSIX_C_SOURCE 200112L
#include<iostream>
#include<stdio.h>
#include<fstream>
#include<fcntl.h>
#include<unistd.h>
#include <dirent.h>
#include<bits/stdc++.h>

using namespace std;


void exe(string s)
{
	char buf[1024];
	
	string temp = "/proc/";
	temp += s;
	temp += "/exe";
			
	char path[temp.length() + 1];

	//cout<<temp<<endl;
			
	strcpy(path ,temp.c_str());
	
	//cout<<path<<endl;
	ssize_t len = readlink(path, buf, 1023);
	
	//cout<<len<<endl;

	buf[len]='\0';
	
	if( len == -1)
	{
		cout<<"Executable :"<<endl;
	}
	else
	{
		printf("Executable : %s\n", buf);
	}
}

int state(string s)
{
	char buf[244];
	
	string temp = "/proc/";
	temp += s;
	temp += "/status";
			
	char path[temp.length() + 1];

	//cout<<temp<<endl;
			
	strcpy(path ,temp.c_str());
	
	int id = open(path,O_RDONLY);

	int n=read(id,buf ,243);
	int i=0; 

	for(i=0 ;i<244 ;i++)
	{
		if( buf[i] == 'S')
		{
			break;
		}
	}

	string st ="";
	
	while( buf[i] != '\n')
	{
		st += buf[i];
		i++;
	}
	
	cout<<st<<endl;
}

int parentID(string s)
{
	char buf[244];
	
	string temp = "/proc/";
	temp += s;
	temp += "/status";
			
	char path[temp.length() + 1];

	//cout<<temp<<endl;
			
	strcpy(path ,temp.c_str());

	int id = open(path,O_RDONLY);

	int n=read(id,buf,243);
	int i=0;

	for(i=0 ;i<244 ;i++)
	{
		if( buf[i] == 'P' && buf[i+1] == 'P')
		{
			break;
		}
	}

	string pp ="";
	
	while( buf[i] != '\n')
	{
		pp += buf[i];
		i++;
	}
	
	cout<<pp<<endl;
}

void session(string s)
{
	char c[128];
	
	string temp = "/proc/";
	temp += s;
	temp += "/sessionid";
			
	char path[temp.length() + 1];

	//cout<<temp<<endl;
			
	strcpy(path ,temp.c_str());
	
	int id = open(path,O_RDONLY);

	int n=read(id,c,127);
	c[n] ='\0';
	
	cout<<"Session ID :"<<c<<endl;
}

void env(string s)
{
	char c[512];
	
	string temp = "/proc/";
	temp += s;
	temp += "/environ";
			
	char path[temp.length() + 1];

	//cout<<temp<<endl;
			
	strcpy(path ,temp.c_str());
	
	int id = open(path,O_RDONLY);

	int n=read(id,c,511);
	c[n] = '\0';
	
	cout<<"Env Vars : ";

	for(int i=0 ;i<n ;i++)
	{
		cout<<c[i];
	}
	
	cout<<endl;

}

void fd(string s)
{
	DIR *d;
	struct dirent *dir;
	
	string t = "/proc/";
	t += s;
	t += "/fd";
			
	char p[t.length() + 1];

	//cout<<temp<<endl;
			
	strcpy(p ,t.c_str());
	
        d = opendir(p);
	
	cout<<"File Descriptors :"<<endl;

        if (d)
        {
        	while ((dir = readdir(d)) != NULL)
        	{
			
			char buf[1024];
			string st = t;
			st += "/";
			st += (dir->d_name);
			
			char path[st.length() + 1];
			
			strcpy(path ,st.c_str());	
			
			ssize_t len = readlink(path, buf, 1023);
		
			buf[len]='\0';
			printf("\t\tDescriptor: %s\n", buf);

               	        //printf("%s\n", dir->d_name);
        	}
        	closedir(d);
    	}
}

void root(string s)
{
	char buf[1024];

	string t = "/proc/";
	t += s;
	t += "/root";
			
	char p[t.length() + 1];

	//cout<<temp<<endl;
			
	strcpy(p ,t.c_str());
	
	ssize_t len = readlink(p, buf, 1023);
	
	buf[len]='\0';
	printf("Root : %s\n", buf);
}

int main(int argc ,char **argv)
{
	if( argc == 2)
	{
		//Get Pid and print details of that process
		string pid = argv[1];
		
		cout<<"PID :"<<pid<<endl;
		cout<<endl;
		exe(pid);
		cout<<endl;
		state(pid);
		cout<<endl;
		parentID(pid);
		cout<<endl;	
		session(pid);
		cout<<endl;
		env(pid);
		cout<<endl;
		fd(pid);
		cout<<endl;
		root(pid);
		cout<<endl;
	}
	else
	{
		//Print all details of All running process
		
		DIR* proc = opendir("/proc");
		struct dirent* ent;

		while(ent = readdir(proc))
		{
		    if(!isdigit(*ent->d_name))
			continue;

		    string pid = ent->d_name;
			
		    cout<<"PID :"<<pid<<endl;
		    cout<<endl;
			exe(pid);
			cout<<endl;
			state(pid);
			cout<<endl;
			parentID(pid);
			cout<<endl;
			session(pid);
			cout<<endl;
			env(pid);
			cout<<endl;
			fd(pid);
			cout<<endl;
			root(pid);
			cout<<endl;
			cout<<"--------------------------------------------------"<<endl<<endl;
		}

		closedir(proc);
	}

	cout<<endl<<endl<<"System Information "<<endl<<endl;

	char buf[10000];
	int id = open("/proc/stat",O_RDONLY);
	int n=read(id,buf,10000);
	
	buf[n] = '\0';

	int i=0;
	int cs = 0;
	int run = 0;
	int blocked = 0;

	for(i=0 ;i<n ;i++)
	{
		if( buf[i] == 'c' && buf[i+1] == 't' && buf[i+2] == 'x' && buf[i+3] == 't')
		{
			cs = i;
		}
	
		if( buf[i] == 'p' && buf[i+1] == 'r' && buf[i+2] == 'o' && buf[i+3] == 'c' && buf[i+4] == 's' && buf[i+5] == '_' && buf[i+6] == 'r')
		{
			run = i;
		}
	
		if( buf[i] == 'p' && buf[i+1] == 'r' && buf[i+2] == 'o' && buf[i+3] == 'c' && buf[i+4] == 's' && buf[i+5] == '_' && buf[i+6] == 'b')
		{
			blocked = i;
		}
	}

	string num = "";
	while( buf[cs] != '\n')
	{
		if( isdigit(buf[cs]) )
		{
			num += buf[cs];
		}
		cs++;
	}
		
	cout<<"Context Switches :"<<num<<endl;

	num = "";
	while( buf[run] != '\n')
	{
		if( isdigit(buf[run]) )
		{
			num += buf[run];
		}
		run++;
	}
		
	cout<<"Running Process : "<<num<<endl;

	num = "";
	while( buf[blocked] != '\n')
	{
		if( isdigit(buf[blocked]) )
		{
			num += buf[blocked];
		}
		blocked++;
	}
		
	cout<<"Blocked Process : "<<num<<endl;	
	
}
