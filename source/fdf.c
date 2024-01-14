/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:42:29 by akdovlet          #+#    #+#             */
/*   Updated: 2024/01/08 17:49:47 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int ft_strchr_hex(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (str[i] != (char)c)
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (i);
}
t_pixel	*lstnew_pixel(int x, int y, int z, unsigned int color)
{
	t_pixel	*node;

	node = malloc(sizeof(t_pixel));
	node->x = x;
	node->y = y;
	node->z = z;
	node->color = color;
	node->next = NULL;
	return (node);
}

ft_ato_hexa(char *str)
{
	int		i;
	int		res;
	int		power;
	char	*hexa;

	hexa = "0123456789abcdef";
	i = 0;
	res = 0;
	power = 1;
	while (str[i])
		i++;
	i--;
	while (i >= 0)
	{
		res += ft_strchr_hex(hexa, str[i]) * power;
		power *= 16;
		i--;
	}
	return (res);
}

t_pixel	*data_parsing(int fd)
{
	t_pixel	*data;
	char	*line;
	char	**strs;
	int		y;
	int		x;

	y = 0;
	data = malloc(sizeof(t_pixel));
	while (get_next_line(fd, &line))
	{
		strs = ft_multi_split(line, ", ");
		x = 0;
		while (strs[x])
		{
			data = lstnew_pixel(x / 2, y, ft_atoi(strs[x]), ft_ato_hexa(strs[x + 1]));
			lst_add_back(&data, data);
			data = data->next;
			x++;
		}
		y++;
		free(line);
	}
	return (data);
}

// int main()
// {
// 	int fd;
// 	t_pixel *data;

// 	fd = open("42.fdf", O_RDONLY);
// 	data = data_parsing(fd);
// 	while (data)
// 	{
// 		printf("%d %d %d %d\n", data->x, data->y, data->z, data->color);
// 		data = data->next;
// 	}
// 	return (0);
// }


