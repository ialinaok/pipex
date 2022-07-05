/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:09:14 by apielasz          #+#    #+#             */
/*   Updated: 2022/07/05 22:11:55 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	show_input_error_msg(int argc)
{
	ft_putstr_stderr("Error - incorrect number of args for the program. ");
	ft_putstr_stderr("Expected 4 but have ");
	ft_putnbr_stderr(argc - 1);
	write(1, ".\n", 2);
	exit(EXIT_FAILURE);
}

void	show_error(char *msg)
{
	ft_putstr_stderr(msg);
	exit(EXIT_FAILURE);
}

void	free_from_split(char **split_ret)
{
	int	i;

	i = 0;
	while (split_ret[i] != NULL)
	{
		free(split_ret[i]);
		i++;
	}
	free(split_ret);
}

void	open_files(t_ppx *ppx, char **argv)
{
	ppx->infile = open(argv[1], O_RDONLY);
	if (ppx->infile == -1)
		show_error("open() failed huh.\n");
	ppx->outfile = open(argv[4], O_WRONLY | O_CREAT, 0777);
	if (ppx->outfile == -1)
		show_error("open() failed.\n");
}

void	alternate_reality(int infile, int outfile)
{
	if (dup2(infile, 0) == -1)
		show_error("dup2() failed.\n");
	if (dup2(outfile, 1) == -1)
		show_error("dup2() failed.\n");
}

void	make_clone(char *cmd, t_ppx *ppx)
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
		execve(ppx->cmd_path, ppx->cmd_flags, ppx->envp);
		free(ppx->cmd_path);
		free(ppx->cmd_flags);
		free_from_split(ppx->split_paths);
		show_error("execve() failed.\n");
	}
	else
	{
		dup2(fd[0], 0);
	}
}

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
		if (dup2(infile, 0) == -1)
			show_error("dup2() in first cmd failed. infile.\n");
		close(fd[0]);
		if (dup2(fd[1], 1) == -1)
			show_error("dup2() in first cmd failed. pipe fd.\n");
		ppx.cmd_path = get_cmd_path(argv[2], &ppx);
		ppx.cmd_flags = get_flags(argv[2]);
		execve(ppx->cmd_path, ppx->cmd_flags, ppx->envp);
		free(ppx->cmd_path);
		free(ppx->cmd_flags);
		free_from_split(ppx->split_paths);
		show_error("execve() first cmd failed.\n");
	}
	else
	{
		close(fd[1]);
		
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_ppx	ppx;
	int		i;

	if (argc < 5)
		show_input_error_msg(argc);
	ppx.envp = envp;
	split_path_var(&ppx);
	run_first_cmd(argv, ppx);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_ppx	ppx;
// 	int		i;
	
// 	if (argc < 5)
// 		show_input_error_msg(argc);
// 	ppx.envp = envp;
// 	open_files(&ppx, argv);
// 	alternate_reality(ppx.infile, ppx.outfile);
// 	split_path_var(&ppx);
// 	i = 2;
// 	while (i < argc - 2)
// 	{
// 		ppx.cmd_path = get_cmd_path(argv[i], &ppx);
// 		ppx.cmd_flags = get_flags(argv[i]);
// 		make_clone(argv[i], &ppx);
// 		i++;
// 	}
// 	printf("argv[i]: %s\n", argv[i]);
// 	ppx.cmd_path = get_cmd_path(argv[i], &ppx);
// 	// ppx.cmd_flags = get_flags(argv[i]);
// }

// // define macros for stdin and out