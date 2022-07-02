/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialinaok <ialinaok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:33:15 by apielasz          #+#    #+#             */
/*   Updated: 2022/07/02 17:30:31 by ialinaok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	split_path_var(t_ppx *ppx)
{
	int	i;

	i = 0;
	while (ppx->envp[i] != NULL)
	{
		if (ft_strncmp(ppx->envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	ppx->split_paths = ft_split(&ppx->envp[i][5], ':');
}

char	*get_cmd_path(char *argv, t_ppx *ppx)
{
	char	**cmd;
	char	*add_slash;
	char	*cmd_path;
	int		i;

	cmd = ft_split(argv, ' ');
	i = 0;
	while (ppx->split_paths[i] != NULL)
	{
		add_slash = ft_strjoin(ppx->split_paths[i], "/");
		cmd_path = ft_strjoin(add_slash, cmd[0]);
		free(add_slash);
		if (access(cmd_path, X_OK) == 0)
		{
			free_from_split(cmd);
			return(cmd_path);
		}
		i++;
		free(cmd_path);
	}
	free_from_split(cmd);
	return(NULL);
}
