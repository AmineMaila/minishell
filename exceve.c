#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

// "hello""world" should be "helloworld"
// minishell-4.81$ <in<fi<le cat
// minishell: le: no such file or directory
//                   ↓
// bash-3.2$ <in <fi <le cat
// bash: in: No such file or directory

int main()
{

	//char *str = "hello world";
	char *arr[] = {"/bin/echo", "hello", "world", NULL};
	//int fd = open("main.c", O_RDONLY);
	//dup2(fd, 0);
	execve(arr[0], arr, NULL);
}