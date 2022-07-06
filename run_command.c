/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 13:18:10 by apielasz          #+#    #+#             */
/*   Updated: 2022/07/06 14:53:59 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_first_command(char **argv, t_ppx *ppx)
{
	int		fd[2];
	pid_t	id;

	if (pipe(fd) == -1)
		show_error("pipe() failed.\n");
	id = fork();
	if (id == -1)
		show_error("fork() failed.\n");
	if (id == 0)
	{
		ppx->infile = open(argv[1], O_RDONLY);
		if (ppx->infile == -1)
			show_error("open() failed on infile.\n");
		if (dup2(ppx->infile, 0) == -1)
			show_error("dup2() in first cmd failed. infile.\n");
		close(fd[0]);
		if (dup2(fd[1], 1) == -1)
			show_error("dup2() in first cmd failed. pipe fd.\n");
		ppx->cmd_path = get_cmd_path(argv[2], ppx);
		ppx->cmd_flags = get_flags(argv[2]);
		printf("getting thereeee: %s\n", ppx->cmd_path);
		execve(ppx->cmd_path, ppx->cmd_flags, ppx->envp);
		free(ppx->cmd_path);
		free(ppx->cmd_flags);
		free_from_split(ppx->split_paths);
		show_error("execve() first cmd failed.\n");
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
	}
}

void	run_piped_command(t_ppx *ppx)
{
	int		fd[2];
	pid_t	id;

	if (pipe(fd) == -1)
		show_error("pipe() failed.\n");
	id = fork();
	if (id == -1)
		show_error("fork() failed.\n");
	if (id == 0)
	{
		if (dup2(fd[1], 1) == -1)
			show_error("dup2() in pipe failed.\n");
		close(fd[0]);
		printf("fake news\n");
		execve(ppx->cmd_path, ppx->cmd_flags, ppx->envp);
		free(ppx->cmd_path);
		free(ppx->cmd_flags);
		free_from_split(ppx->split_paths);
		show_error("execve() failed.\n");
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
	}
}

void	run_last_command(int argc, char **argv, t_ppx *ppx)
{
	pid_t	id;

	id = fork();
	if (id == -1)
		show_error("last fork() failed.\n");
	if (id == 0)
	{
		ppx->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT, 0777);
		if (ppx->outfile == -1)
			show_error("open() outfile failed.\n");
		if (dup2(ppx->outfile, 1) == -1)
			show_error("dup2() last cmd failed.\n");
		ppx->cmd_path = get_cmd_path(argv[argc - 2], ppx);
		ppx->cmd_flags = get_flags(argv[argc - 2]);
		execve(ppx->cmd_path, ppx->cmd_flags, ppx->envp);
		free(ppx->cmd_path);
		free(ppx->cmd_flags);
		free_from_split(ppx->split_paths);
		show_error("execve() first cmd failed.\n");
	}
}
