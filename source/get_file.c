/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 19:01:13 by akdovlet          #+#    #+#             */
/*   Updated: 2024/01/14 19:21:52 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// char	*ak_strjoin(char *s1, char *s2)
// {
// 	char	*fusion;
// 	int		i;
// 	int		j;

// 	i = -1;
// 	j = -1;
// 	if (!s1)
// 	{
// 		s1 = malloc(sizeof(char) * 1);
// 		if (!s1)
// 			return (NULL);
// 		s1[0] = '\0';
// 	}
// 	if (!s2)
// 		return (NULL);
// 	fusion = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (!fusion)
// 		return (free(s1), NULL);
// 	while (s1[++i])
// 		fusion[i] = s1[i];
// 	while (s2[++j])
// 		fusion[i + j] = s2[j];
// 	fusion[i + j] = '\0';
// 	free(s1);
// 	return (fusion);
// }

char	*read_file(int fd)
{
	char	*file;
	char	*buf;
	int		n;

	file = NULL;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (1)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n <= 0)
			break ;
		buf[n] = '\0';
		file = ak_strjoin(file, buf);
		if (!file)
			return (free(buf), NULL);
	}
	free(buf);
	return (file);
}

char	*get_file(int fd)
{
	char	*file;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	file = read_file(fd);
	if (!file)
		return (free(file), NULL);
	return (file);
}
