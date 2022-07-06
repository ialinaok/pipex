#include <unistd.h>
#include <stdio.h>

int main(int argc, char **jk, char **envp)
{
	argc = 0;
	printf("%s\n", jk[0]);
	char *argv[3] = {"anything", "status", NULL};
	execve("/usr/bin/git", argv, envp);
}