/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialinaok <ialinaok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:09:34 by apielasz          #+#    #+#             */
/*   Updated: 2022/07/02 22:37:16 by ialinaok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>


typedef struct s_ppx
{
	char	*cmd1_path;
	char	*cmd2_path;
	char	**cmd_flags;
	char	**envp;
	char	**split_paths;
	int		infile;
	int		outfile;
}				t_ppx;

/* pipex.c */
void	show_error_msg(int argc);
void	free_from_split(char **split_ret);
void	free_it_all(t_ppx *ppx);
void	open_files(t_ppx *ppx, char **argv);

/* utils.c */
void	ft_putstr_stdout(char *str);
void	ft_putnbr_stdout(int n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(const char *s);
int		ft_strlcpy(char *dst, const char *src, int dst_size);

/* cmd_utils.c */
char	*ft_strjoin(char const *s1, char const *s2);
void	split_path_var(t_ppx *ppx);
char	*get_cmd_path(char *argv, t_ppx *ppx);

/* ft_split.c */
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		count_strings(const char *s, char c);
int		find_start(const char *s, char c);
int		find_len(const char *start, char c);
char	**ft_split(char const *s, char c);

#endif