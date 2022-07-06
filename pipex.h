/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:09:34 by apielasz          #+#    #+#             */
/*   Updated: 2022/07/06 22:39:26 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_ppx
{
	char	*cmd_path;
	char	**split_cmd;
	char	**envp;
	char	**split_paths;
	int		infile;
	int		outfile;
	int		exec_status;
}				t_ppx;

/* pipex.c */
void	show_input_error_msg(int argc);
void	show_error(char *msg);
void	free_from_split(char **split_ret);
// void	free_it_all(t_ppx *ppx);

/* utils.c */
void	ft_putstr_stderr(char *str);
void	ft_putnbr_stderr(int n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(const char *s);
int		ft_strlcpy(char *dst, const char *src, int dst_size);

/* more_utils.c */
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);

/* cmd_utils.c */
void	split_path_var(t_ppx *ppx);
char	*get_cmd_path(char *argv, t_ppx *ppx);

/* ft_split.c */
int		count_strings(const char *s, char c);
int		find_start(const char *s, char c);
int		find_len(const char *start, char c);
char	**ft_split(char const *s, char c);

/* run_commands.c */
void	run_first_command(char **argv, t_ppx *ppx);
void	run_piped_command(t_ppx *ppx);
void	run_last_command(int argc, char **argv, t_ppx *ppx);

#endif