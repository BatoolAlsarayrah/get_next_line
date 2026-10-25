/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balsaray <balsaray@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 11:21:34 by balsaray          #+#    #+#             */
/*   Updated: 2026/10/25 10:52:17 by balsaray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *src, int c)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		if (src[i] == (char)c)
			return ((char *)src + i);
		i++;
	}
	if (src[i] == (char)c)
		return ((char *)src + i);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*resstr;

	i = 0;
	j = 0;
	if (!s2)
		return (NULL);
	if (!s1 )
		s1 = "";
	resstr = malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * (sizeof(char)));
	if (!resstr)
		return (NULL);
	while (s1[j])
	{
		resstr[i++] = s1[j++];
	}
	j = 0;
	while (s2[j])
	{
		resstr[i++] = s2[j++];
	}
	resstr[i] = '\0';
	return (resstr);
}
char	*ft_strcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*dest;

	len = ft_strlen(src);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	ft_strcpy(dest, src, len + 1);
	return (dest);
}
