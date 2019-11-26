#define _POSIX_C_SOURCE 200112L
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	char buf[1024];
	ssize_t len = readlink("/proc/1/root", buf, 1023);
	
	buf[len]='\0';
	printf("Root : %s\n", buf);
}
