#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
	char *arr[] = {"/bin/cat", NULL};
	int fd = open("main.c", O_RDONLY);
	dup2(fd, 0);
	execve(arr[0], arr, NULL);
}