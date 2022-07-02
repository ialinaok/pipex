#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);
int		count_strings(const char *s, char c);
int		find_start(const char *s, char c);
int		find_len(const char *start, char c);
char	**ft_split(char const *s, char c);

int	ft_strlen(const char *s)
{
	int	n;

	n = 0;
	while (s[n] != '\0')
	{
		n++;
	}
	return (n);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	newstr = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!newstr)
		return (NULL);
	i = 0;
	while (*s1)
	{
		newstr[i] = *s1++;
		i++;
	}
	while (*s2)
	{
		newstr[i] = *s2++;
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

int	ft_strlcpy(char *dst, const char *src, int dst_size)
{
	int	src_len;
	int	i;

	i = 0;
	src_len = ft_strlen(src);
	if (dst_size > 0)
	{
		dst_size--;
		while (i < dst_size && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0)
	{
		if (*s1 != *s2)
		{
			return ((unsigned char)*s1 - (unsigned char)*s2);
		}
		if ((*s1 == '\0') || (*s2 == '\0'))
		{
			break ;
		}
		s1++;
		s2++;
		n--;
	}
	return (0);
}

char	**get_cmd_path(char *argv, char **envp)
{
	char	**cmd;
	char	**paths;
	char	*cmd_and_path;
	char	*add_slash;
	int		i;

	i = 0;
	cmd = ft_split(argv, ' ');
	printf("the command is: %s\n", cmd[0]);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	paths = ft_split(&envp[i][5], ':');
	i = 0;
	while (paths[i] != NULL)
	{
		add_slash = ft_strjoin(paths[i], "/");
		cmd_and_path = ft_strjoin(add_slash, cmd[0]);
		if (access(cmd_and_path, X_OK) == 0) // zero on success, -1 on error
			break ;
		i++;
		free(add_slash);
		free(cmd_and_path);
	}
	printf("the path: %s\n", cmd_and_path);
	free(cmd_and_path);
	int f;
	for (f = 0; cmd[f] != NULL; f++)
		free(cmd[f]);
	free(cmd[f]);
	free(add_slash);
	free(cmd_and_path);
	return (paths);
}

// int main(int argc, char **argv, char **envp)
// {
// 	char	**path;

// 	path = get_cmd_path(argv[1], envp);
// 	// for (int i = 0; path[i] != NULL; i++)
// 	// 	printf("path--->%s\n", path[i]);
// 	int i;
// 	for (i = 0; path[i] != NULL; i++)
// 		free(path[i]);
// 	free(path[i]);
// 	free(path);
// 	return (0);
// }

int main(void)
{
	char **spliiit = ft_split("fds vs dasdas fsad", ' ');
	int i = 0;
	while (spliiit[i] != NULL)
	{
		printf("%s\n", spliiit[i]);
		free(spliiit[i]);
		i++;
	}
	free(spliiit);
}