#include <unistd.h>

int main()
{
	char *arr[] = {"echo", "$path", NULL};

	execve(arr[0], arr, NULL);
}