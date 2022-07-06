/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 00:33:15 by apielasz          #+#    #+#             */
/*   Updated: 2022/07/06 20:11:16 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	char	*add_slash;
	char	*cmd_path;
	int		i;

	ppx->split_cmd = ft_split(argv, ' ');
	i = 0;
	while (ppx->split_paths[i] != NULL)
	{
		add_slash = ft_strjoin(ppx->split_paths[i], "/");
		cmd_path = ft_strjoin(add_slash, ppx->split_cmd[0]);
		free(add_slash);
		if (access(cmd_path, X_OK) == 0)
			return(cmd_path);
		i++;
		free(cmd_path);
	}
	return(NULL);
}

char	*get_cmd_path(char *argv, t_ppx *ppx)
{
	char	*add_slash;
	char	*cmd_path;
	int		i;

	ppx->split_cmd = ft_split(argv, ' ');
	i = 0;
	while (ppx->split_paths[i] != NULL)
	{
		add_slash = ft_strjoin(ppx->split_paths[i], "/");
		cmd_path = ft_strjoin(add_slash, ppx->split_cmd[0]);
		free(add_slash);
		execve(cmd_path, ppx->split_cmd, ppx->envp);
		i++;
		free(cmd_path);
	}
	return(NULL);
}
