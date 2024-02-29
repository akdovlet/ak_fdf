/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:42:29 by akdovlet          #+#    #+#             */
/*   Updated: 2024/02/29 18:38:30 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>

int	char_check(char c)
{
	if ((c >= '0' && c <= '9') || c == ',' 
		|| c == 'X' || c == 'x' || (c >= 'a' && c <= 'f')
			|| (c >= 'A' && c <= 'F') || c == '-')
		return 1;
	return (0);
}

int	count_points(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (char_check(str[i]))
		{
			count++;
			while (str[i] && char_check(str[i]))
				i++;		
		}
		else
			i++;
	}
	return (count);
}

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;
// 	size_t	y_offset;
// 	size_t	x_offset;

// 	y_offset = y * data->line_length;
// 	x_offset = x * (data->bits_per_pixel / 8);
// 	dst = &data->addr[y_offset + x_offset];
// 	*(unsigned int*)dst = color;
// }

int	ak_superlen(t_list *lst, int *lines, int *rows)
{
	int	first;
	int	len;
	int	i;

	first = count_points(lst->content);
	i = 0;
	while (lst)
	{
		len = count_points(lst->content);
		// ft_printf("amount of points: %d\n", len);
		if (len != first)
			return (-1);
		lst = lst->next;
		i++;
	}
	*lines = i;
	*rows = first;
	return (1);
}

int	ak_atoi(char *str, int *i)
{
	long	n;
	int		sign;

	n = 0;
	sign = 1;
	if (str[*i] == '-')
	{
		sign = -1;
		(*i)++;
	}
	while (str[*i] && (str[*i] >= '0' && str[*i] <= '9'))
	{
		n = n * 10 + (str[*i] - 48);
		(*i)++;
	}
	return (n * sign);
}

int	hex_check(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f')
		|| (c >= 'A' && c <= 'F'))
		return (1);
	return (0);
}

unsigned int	ak_atohex(char *str, int *i, int bin)
{
	unsigned int hex;
	char 		*hex1;
	char 		*hex2;

	hex = 0;
	hex1 = "0123456789abcdef";
	hex2 = "0123456789ABCDEF";
	while (str[*i] && hex_check(str[*i]))
	{
		if (bin)
			hex = hex * 16 + ak_strchr(hex2, str[*i]);
		else
			hex = hex * 16 + ak_strchr(hex1, str[*i]);
		(*i)++;
	}
	return (hex);
}

unsigned int	color_manager(char *str, int *i)
{
	if (str[*i] == ',')
	{
		(*i)++;
		if (str[*i] == '0' && str[(*i) + 1] == 'X')
		{
			(*i) += 2;
			return (ak_atohex(str, i, 1));
		}
		else if (str[*i] == '0' && str[(*i) + 1] == 'x')
		{
			(*i) += 2;
			return (ak_atohex(str, i, 0));
		}
		return (16777215);
	}
	else
		return (16777215);
}

t_pixel	*data_filler(char *str, int x, int y)
{
	t_pixel *data;
	int		i;
	int		j;

	data = malloc(sizeof(t_pixel) * x);
	if (!data)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] && char_check(str[i]))
		{
			data[j].x = j;
			data[j].y = y;
			data[j].z = ak_atoi(str, &i);
			data[j].color = color_manager(str, &i);
			j++;
			while (str[i] && char_check(str[i]))
				i++;
		}
		else
			i++;
	}
	return (data);
}

t_pixel **data_parser(t_list *lst, int lines, int rows)
{
	int		i;
	t_pixel	**data;
	
	i = 0;
	data = malloc(sizeof(t_pixel *) * lines);
	if (!data)
		return (NULL);
	while (lst)
	{
		data[i] = data_filler((char*)lst->content, rows, i);
		if (!data[i])
			return (pixel_clear(data, i), NULL);
		lst = lst->next;
		i++;
	}
	return (data);
}

void	pixel_clear(t_pixel **data, int i)
{
	int	j;

	j = 0;
	while (j < i && data[j])
	{
		free(data[j]);
		j++;
	}
	free(data);
}


//print the parsing data main
// int main(int ac, char **av)
// {
// 	int		i;
// 	int		j;
// 	int		x;
// 	int		y;
// 	int		fd;
// 	t_list	*lst;
// 	t_pixel	**data;

// 	i = 0;
// 	if (ac != 2)
// 		return (0);
// 	fd = open(av[1], O_RDONLY);
// 	lst = get_file(fd);
// 	x = ak_superlen(lst, &y);
// 	printf("x is: %d\ny is: %d\n", x, y);
// 	data = data_parser(lst, x, y);
// 	while (i < y)
// 	{
// 		j = 0;
// 		while (j < 10)
// 		{
// 			printf("i is: %d\nj is: %d\n", i, j);
// 			printf("x is: %f\n", data[i][j].x);
// 			printf("y is: %f\n", data[i][j].y);
// 			printf("z is: %f\n", data[i][j].z);
// 			printf("color is: %u\n", data[i][j].color);
// 			j++;
// 		}
// 		i++;
// 	}
// 	ft_lstclear(&lst, free);
// 	pixel_clear(data, y);
// 	close(fd);
// }


