#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	printf("%s\n", getenv("PWD"));
}