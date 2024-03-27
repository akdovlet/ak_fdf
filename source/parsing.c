/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:42:29 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/27 15:59:41 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

int	char_check(char c)
{
	if ((c >= '0' && c <= '9') || c == ','
		|| c == 'X' || c == 'x' || (c >= 'a' && c <= 'f')
		|| (c >= 'A' && c <= 'F') || c == '-')
		return (1);
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

int	file_and_parse(char *av, t_grid *grid)
{
	int		fd;
	t_list	*lst;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Open failed\n"), 0);
	lst = get_file(fd);
	if (!lst)
		return (ft_printf("Lst malloc failed\n"), 0);
	close(fd);
	if (ak_superlen(lst, &grid->lines, &grid->rows) == -1)
		return (ft_lstclear(&lst, free), ft_printf("Map Invalid"), 0);
	grid->pixel = data_parser(lst, grid->lines, grid->rows);
	if (!grid->pixel)
		return (ft_printf("failed grid malloc"), 0);
	ft_lstclear(&lst, free);
	return (1);
}
