/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balsaray <balsaray@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 12:09:17 by balsaray          #+#    #+#             */
/*   Updated: 2026/10/25 19:47:14 by balsaray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*freebuff(char *buff)
{
	free(buff);
	return (NULL);
}

char	*readbuff(int fd, char *buff)
{
	char	*temp;
	char	*oldbuff;
	int		nbytes;

	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp)
		return (freebuff(buff));
	nbytes = 1;
	while (nbytes > 0 && !(buff && ft_strchr(buff, '\n')))
	{
		nbytes = read(fd, temp, BUFFER_SIZE);
		if (nbytes < 0)
		{
			free(temp);
			return (freebuff(buff));
		}
		temp[nbytes] = '\0';
		oldbuff = buff;
		buff = ft_strjoin(buff, temp);
		free(oldbuff);
		if (!buff)
			return (freebuff(temp));
	}
	free(temp);
	return (buff);
}

char	*getreqline(char *buff)
{
	char	*line;
	int		i;

	i = 0;
	if (!buff[i])
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	line = malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	line = ft_strcpy(line, buff, i + 2);
	return (line);
}

char	*remainings(char *line, char *buff)
{
	char	*temp;
	int		i;

	i = 0;
	while (line[i] && line[i] == buff[i])
		i++;
	if (!buff[i])
	{
		return (freebuff(buff));
	}
	temp = ft_strdup(buff + i);
	if (!temp)
	{
		return (freebuff(buff));
	}
	free(buff);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*buff[1024];
	char		*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buff[fd] = readbuff(fd, buff[fd]);
	if (!buff[fd])
		return (NULL);
	line = getreqline(buff[fd]);
	if (!line)
	{
		buff[fd] = freebuff(buff[fd]);
		return (NULL);
	}
	buff[fd] = remainings(line, buff[fd]);
	return (line);
}
// int main()
// {
// 	int fd1 = open("t_basic.txt", O_RDONLY);
// 	int fd2 = open("t_short.txt", O_RDONLY);
// 	char	*l1;
// 	char	*l2;
// 	l1 = get_next_line(fd1);
// 	l2 = get_next_line(fd2);
// 	while (l1 || l2)
// 	{
// 		if (l1)
// 			printf("fd1: %s", l1);
// 		if (l2)
// 			printf("fd2: %s", l2);
// 		free(l1);
// 		free(l2);
// 		l1 = get_next_line(fd1);
// 		l2 = get_next_line(fd2);
// 	}
// 	close(fd1);
// 	close(fd2);
// }
