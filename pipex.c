/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:09:14 by apielasz          #+#    #+#             */
/*   Updated: 2022/07/04 22:23:09 by apielasz         ###   ########.fr       */
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

void	free_it_all(t_ppx *ppx)
{
	free(ppx->cmd1_path);
	free(ppx->cmd2_path);
	free(ppx->cmd1_flags);
	free(ppx->cmd2_flags);
	free_from_split(ppx->split_paths);
}

void	open_files(t_ppx *ppx, char **argv)
{
	ppx->infile = open(argv[1], O_RDONLY);
	if (ppx->infile == -1)
		show_error("open() failed.\n")
	ppx->outfile = open(argv[4], O_WRONLY | O_CREAT, 0777);
	if (ppx->outfile == -1)
		show_error("open() failed.\n");
}

void	alternate_reality(t_ppx *ppx)
{
	if (dup2(ppx->infile, 0) == -1)
		show_error("dup2() failed.\n");
	if (dup2(ppx->outfile, 1) == -1)
		show_error("dup2() failed.\n");
}


int	main(int argc, char **argv, char **envp)
{
	t_ppx	ppx;
	int		fd[2];
	
	if (argc != 5)
		show_input_error_msg(argc);
	ppx.envp = envp;
	if (pipe(fd) == -1)
		(show_error("pipe() failed.\n"));
	open_files(&ppx, argv);
	alternate_reality(&ppx);
	
	split_path_var(&ppx);
	ppx.cmd1_path = get_cmd_path(argv[2], &ppx);
	ppx.cmd2_path = get_cmd_path(argv[3], &ppx);
	if (ppx.cmd1_path == NULL || ppx.cmd2_path == NULL)
		exit(0);
	// printf("cmd1 path: %s\n", ppx.cmd1_path);
	// printf("cmd2 path: %s\n", ppx.cmd2_path);
	ppx.cmd1_flags = get_flags(argv[2]);
	printf("the flags: %s\n", ppx.cmd1_flags);
	ppx.cmd2_flags = get_flags(argv[3]);
	printf("the flags: %s\n", ppx.cmd2_flags);
	// int din = dup2(ppx.infile, 0);
	// int dout = dup2(ppx.outfile, 1);
	// make_clone(&ppx);
	execve(ppx.cmd2_path, ppx.cmd2_flags, envp);
	free_it_all(&ppx);
} 

// define macros for stdin and out