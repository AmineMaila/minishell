#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv, char **env)
{
	char *arr;

	(void)argc;
	(void)argv;
	arr = NULL;
	arr = env[0];
	printf("%s\n", arr);
	//char *str = "hello world";
	//char *arr[] = {"/bin/ls", "~q", NULL};
	//int fd = open("main.c", O_RDONLY);
	//dup2(fd, 0);
	//execve(arr[0], arr, NULL);
	close(7);
}