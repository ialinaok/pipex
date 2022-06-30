/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:09:14 by apielasz          #+#    #+#             */
/*   Updated: 2022/07/01 00:51:27 by apielasz         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_ppx	ppx;
	
	if (argc != 5)
		show_error_msg(argc);
	ppx.envp = envp;
	ppx.cmd1_path = get_cmd_path(argv[2], envp);
}