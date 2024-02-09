#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
	//char *str = "hello world";
	char *arr[] = {"/usr/bin/which", "ls", NULL};
	//int fd = open("main.c", O_RDONLY);
	//dup2(fd, 0);
	execve(arr[0], arr, NULL);
}