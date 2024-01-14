/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_multi.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 22:42:25 by akdovlet          #+#    #+#             */
/*   Updated: 2024/01/14 12:06:09 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_to_newline(int fd, char *buffer)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	if (buffer[0])
	{
		tmp = ak_strjoin(tmp, buffer);
		if (!tmp)
			return (NULL);
	}
	while (ak_strchr(buffer, '\n') == -1)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i <= 0)
			break ;
		buffer[i] = 0;
		tmp = ak_strjoin(tmp, buffer);
		if (!tmp)
			return (NULL);
	}
	return (tmp);
}

void	clean_static(char *buffer)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	if (!buffer)
		return ;
	while (buffer[j] != '\n' && buffer[j])
		j++;
	if (buffer[j] == '\n')
		j++;
	while (buffer[j])
		buffer[i++] = buffer[j++];
	buffer[i] = 0;
}

char	*extract_line(char *tmp)
{
	char	*line;
	int		i;

	i = 0;
	if (!tmp)
		return (NULL);
	while (tmp[i] != '\n' && tmp[i])
		i++;
	if (tmp[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (tmp[i] != '\n' && tmp[i])
	{
		line[i] = tmp[i];
		i++;
	}
	if (tmp[i] == '\n')
		line[i++] = '\n';
	line[i] = 0;
	return (line);
}

char	*get_next_line_multi(int fd)
{
	static char	buffer[FD_MAX][BUFFER_SIZE + 1];
	char		*tmp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_MAX)
		return (NULL);
	tmp = read_to_newline(fd, buffer[fd]);
	if (!tmp)
		return (NULL);
	line = extract_line(tmp);
	free(tmp);
	clean_static(buffer[fd]);
	return (line);
}

// int main()
// {
// 	char *line;
// 	int i = 0;
// 	int fd = open("alternate_line_nl_with_nl", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break ;
// 		// printf("%d", i);
// 		i++;
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// }
