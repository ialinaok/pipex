/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 16:27:46 by apielasz          #+#    #+#             */
/*   Updated: 2022/07/04 22:17:42 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_stderr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

void	ft_putnbr_stderr(int n)
{
	char	intprint;

	if (n > 10)
		ft_putnbr_stderr(n / 10);
	intprint = n % 10 + '0';
	write(2, &intprint, 1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0)
	{
		if (*s1 != *s2)
		{
			return ((unsigned char)*s1 - (unsigned char)*s2);
		}
		if ((*s1 == '\0') || (*s2 == '\0'))
		{
			break ;
		}
		s1++;
		s2++;
		n--;
	}
	return (0);
}

int	ft_strlen(const char *s)
{
	int	n;

	n = 0;
	while (s[n] != '\0')
	{
		n++;
	}
	return (n);
}

int	ft_strlcpy(char *dst, const char *src, int dst_size)
{
	int	src_len;
	int	i;

	i = 0;
	src_len = ft_strlen(src);
	if (dst_size > 0)
	{
		dst_size--;
		while (i < dst_size && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}
