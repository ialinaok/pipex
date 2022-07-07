/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:09:14 by apielasz          #+#    #+#             */
/*   Updated: 2022/07/07 17:32:05 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	show_input_error_msg(int argc)
{
	ft_putstr_stderr("Error - incorrect number of args for the program. ");
	ft_putstr_stderr("Expected at least 4 but have ");
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
	ppx.exec_status = 0;
	split_path_var(&ppx);
	run_first_command(argv, &ppx);
	i = 3;
	while (i < argc - 2)
	{
		if (argv[i] == NULL)
			return (1);
		run_piped_command(argv[i], &ppx);
		i++;
	}
	run_last_command(argc, argv, &ppx);
	free_from_split(ppx.split_paths);
	return (0);
}

// CODE GRAVEYARD

// char	**get_flags(char *argv)
// {
// 	char	**argv_split;
// 	char	**flags;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	argv_split = ft_split(argv, ' ');
// 	while (argv_split[i] != NULL)
// 		i++;
// 	flags = malloc((i + 1) * sizeof(char *));
// 	if (!flags)
// 		return (NULL);
// 	i = 1;
// 	j = 0;
// 	while (argv_split[i] != NULL)
// 	{
// 		flags[j] = argv_split[i];
// 		j++;
// 		i++;
// 	}
// 	flags[j] = NULL;
// 	return (flags);
// }

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