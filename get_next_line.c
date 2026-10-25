/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: balsaray <balsaray@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 11:21:16 by balsaray          #+#    #+#             */
/*   Updated: 2026/10/25 12:26:55 by balsaray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*freebuff(char *buff)
{
	free(buff);
	return(NULL);
}
char *readbuff(int fd,char *buff)
{
	char *temp;
	char *oldbuff;
	int nbytes;

	temp = malloc((BUFFER_SIZE + 1) *  sizeof(char));
	if (!temp)
		return (NULL);
	nbytes = 1;
	while(nbytes > 0 && !(buff && ft_strchr(buff,'\n')))
	{
		nbytes = read(fd,temp,BUFFER_SIZE);
		if (nbytes < 0)
		{
			free(temp);
			return(freebuff(buff));
		}
		temp[nbytes] = '\0';
		oldbuff = buff;
		buff = ft_strjoin(buff,temp);
		free(oldbuff);
		if (!buff)
			return(freebuff(temp));
	}
	free(temp);
	return (buff);
}

char *getreqline(char *buff)
{
	char *line;
	int i;

	i = 0;
	if(!buff[i])
	return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	line = malloc((i + 2) *  sizeof(char));
	if (!line)
		return (NULL);
	line = ft_strcpy(line, buff, i + 2);
	return (line);
}
char *remainings(char *line, char *buff)
{
	char *temp;
	int i;

	i = 0;
	while (line[i] && line[i] == buff[i])
		i++;
	if (!buff[i])
	{
		return(freebuff(buff));
	}
	temp = ft_strdup(buff + i);
	if (!temp)
	{
		return(freebuff(buff));
	}
	free(buff);
	return (temp);
}

char *get_next_line(int fd)
{
	static char *buff;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = readbuff(fd, buff);
	if (!buff)
		return (NULL);
	line = getreqline(buff);
	if (!line)
	{
		buff = freebuff(buff);
		return (NULL);
	}
	buff = remainings(line,buff);
	return (line);
}
// int main()
// {
// 	int fd = open("t_one_line.txt", O_RDONLY );
// 	char *line;
// 	if (fd < 0)
// 	printf("%s",get_next_line(fd));
// 	line = get_next_line(fd);
// 	while(line)
// 	{
// 		printf("%s",line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// }
