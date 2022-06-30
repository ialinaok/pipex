#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// for double forking

int main(int argc, char **argv)
{
	int id = fork();
	int id2 = fork();
	if (id != 0)
		wait(0);
	printf("Hey, my id is: %d\n", id);
	// printf("Hey hey, my id is: %d\n", id2);
	return (0);
}

// for parent child relationship

int main(int argc, char **argv)
{
	int id = fork();
	if (id == 0)
	{
		printf("I'm a child. My id is: %d\n", getpid());
	}
	else
	{
		printf("I'm a parent and my id is: %d. And this is what fork gave me: %d\n", getpid(), id);
	}
}