/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:09:34 by apielasz          #+#    #+#             */
/*   Updated: 2022/07/01 01:11:02 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_ppx
{
	char	*cmd1_path;
	char	*cmd2_path;
	char	**cmd_flags;
	char	**envp;
	int		infile;
	int		outfile;
}				t_ppx;

/* pipex.c */
void	show_error_msg(int argc);

/* utils.c */

void	ft_putstr_stdout(char *str);
void	ft_putnbr_stdout(int n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(const char *s);
int	ft_strlcpy(char *dst, const char *src, int dst_size);

/* ft_split.c */
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		count_strings(const char *s, char c);
int		find_start(const char *s, char c);
int		find_len(const char *start, char c);
char	**ft_split(char const *s, char c);

#endif