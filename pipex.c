/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialinaok <ialinaok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:09:14 by apielasz          #+#    #+#             */
/*   Updated: 2022/07/02 22:53:53 by ialinaok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	show_error_msg(int argc)
{
	ft_putstr_stdout("Error - incorrect number of args for the program. ");
	ft_putstr_stdout("Expected 4 but have ");
	ft_putnbr_stdout(argc - 1);
	write(1, ".\n", 2);
	exit(0);
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
	free_from_split(ppx->split_paths);
}

void	open_files(t_ppx *ppx, char **argv)
{
	printf("frog appear!!!\n");
	ppx->infile = open(argv[1], O_RDONLY);
	if (ppx->infile == -1)
	{
		printf("here?\n");
		// return ;
	}
	ppx->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (ppx->outfile == -1)
	{
		printf("wbu?\n");
		// return ;
	}
}

void	alternate_reality(t_ppx *ppx)
{
	// if (dup2(ppx->infile, 0) == -1)
	// {
	// 	printf("makes no sense\n");
	// 	// return ;
	// }
	// if (dup2(ppx->outfile, 1) == -1)
	// {
	// 	printf("lolz\n");
	// 	// return ;
	// }
	int din = dup2(ppx->infile, 0);
	int dout = dup2(ppx->outfile, 1);
	printf("after dup2 in: %d, out: %d\n", ppx->infile, ppx->outfile);
}

int	main(int argc, char **argv, char **envp)
{
	t_ppx	ppx;
	
	if (argc != 5)
		show_error_msg(argc);
	ppx.envp = envp;
	split_path_var(&ppx);
	ppx.cmd1_path = get_cmd_path(argv[2], &ppx);
	ppx.cmd2_path = get_cmd_path(argv[3], &ppx);
	if (ppx.cmd1_path == NULL || ppx.cmd2_path == NULL)
		exit(0);
	open_files(&ppx, argv);
	// alternate_reality(&ppx);
	int din = dup2(ppx.infile, 0);
	int dout = dup2(ppx.outfile, 1);
	printf("cmd1 path: %s\n", ppx.cmd1_path);
	printf("cmd2 path: %s\n", ppx.cmd2_path);
	free_it_all(&ppx);
}