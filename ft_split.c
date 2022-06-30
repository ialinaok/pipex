/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 23:14:20 by apielasz          #+#    #+#             */
/*   Updated: 2022/07/01 01:05:28 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (slen < len)
		substr = (char *) malloc(slen + 1);
	else
		substr = (char *) malloc(len + 1);
	if (!substr)
		return (NULL);
	if (slen >= start)
		ft_strlcpy(substr, &s[start], len + 1);
	else
		substr[0] = '\0';
	return (substr);
}

int	count_strings(const char *s, char c)
{
	int	i;
	int	str_num;

	i = 0;
	str_num = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			str_num++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (str_num);
}

int	find_start(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	return (i);
}

int	find_len(const char *start, char c)
{
	int	slen;

	slen = 0;
	while (start[slen] != c && start[slen] != '\0')
		slen++;
	return (slen);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		start;
	int		slen;
	int		str_num;
	int		i;

	if (!s)
		return (NULL);
	str_num = count_strings(s, c);
	split = (char **) malloc((str_num + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	start = find_start(s, c);
	i = 0;
	while (i < str_num)
	{
		slen = find_len(&s[start], c);
		split[i] = ft_substr(s, start, slen);
		start = start + slen + find_start(&s[start + slen], c);
		i++;
	}
	split[str_num] = NULL;
	return (split);
}
