/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:08:50 by akdovlet          #+#    #+#             */
/*   Updated: 2024/04/01 10:46:41 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "parsing.h"

t_pixel	*data_filler(char *str, int x, int y)
{
	t_pixel	*data;
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
			data[j].x[0] = j;
			data[j].y[0] = y;
			data[j].z[0] = ak_atoi(str, &i);
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

t_pixel	**data_parser(t_list *lst, int lines, int rows)
{
	int		i;
	t_pixel	**data;

	i = 0;
	data = malloc(sizeof(t_pixel *) * lines);
	if (!data)
		return (NULL);
	while (lst)
	{
		data[i] = data_filler((char *)lst->content, rows, i);
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
