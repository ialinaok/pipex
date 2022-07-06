/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:09:14 by apielasz          #+#    #+#             */
/*   Updated: 2022/07/06 14:54:07 by apielasz         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_ppx	ppx;
	int		i;

	if (argc < 5)
		show_input_error_msg(argc);
	ppx.envp = envp;
	split_path_var(&ppx);
	run_first_command(argv, &ppx);
	i = 3;
	while (i < argc - 2)
	{
		ppx.cmd_path = get_cmd_path(argv[i], &ppx);
		ppx.cmd_flags = get_flags(argv[i]);
		run_piped_command(&ppx);
		i++;
	}
	run_last_command(argc, argv, &ppx);
	return (0);
}


// CODE GRAVEYARD

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
// // 	}
// 	printf("argv[i]: %s\n", argv[i]);
// 	ppx.cmd_path = get_cmd_path(argv[i], &ppx);
// 	// ppx.cmd_flags = get_flags(argv[i]);
// }

// // define macros for stdin and out

// void	open_files(t_ppx *ppx, char **argv)
// {
// 	ppx->infile = open(argv[1], O_RDONLY);
// 	if (ppx->infile == -1)
// 		show_error("open() failed huh.\n");
// 	ppx->outfile = open(argv[4], O_WRONLY | O_CREAT, 0777);
// 	if (ppx->outfile == -1)
// 		show_error("open() failed.\n");
// }

// void	alternate_reality(int infile, int outfile)
// {
// 	if (dup2(infile, 0) == -1)
// 		show_error("dup2() failed.\n");
// 	if (dup2(outfile, 1) == -1)
// 		show_error("dup2() failed.\n");
// }