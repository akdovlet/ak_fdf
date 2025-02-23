/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:11:53 by akdovlet          #+#    #+#             */
/*   Updated: 2025/02/23 00:55:46 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "parsing.h"

int	hex_check(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f')
		|| (c >= 'A' && c <= 'F'))
		return (1);
	return (0);
}

unsigned int	ak_atohex(char *str, int *i)
{
	long long int	hex;
	char			*hex1;
	char			*hex2;

	hex = 0;
	hex1 = "0123456789abcdef";
	hex2 = "0123456789ABCDEF";
	while (str[*i] && hex_check(str[*i]))
	{
		if (ak_strchr(hex1, str[*i]) != -1)
			hex = (hex * 16) + ak_strchr(hex1, str[*i]);
		else
			hex = (hex * 16) + ak_strchr(hex2, str[*i]);
		(*i)++;
	}
	return (hex);
}

unsigned int	color_manager(char *str, int *i)
{
	if (str[*i] == ',')
	{
		(*i)++;
		if (str[*i] == '0' && (str[(*i) + 1] == 'X' || str[(*i) + 1] == 'x'))
		{
			(*i) += 2;
			return (ak_atohex(str, i));
		}
	}
	return (0x33FF33);
}

int	extension_checker(char *str)
{
	int		i;
	int		j;
	char	*fdf;

	i = ft_strlen(str);
	if (i < 5)
		return (0);
	fdf = ".fdf";
	i -= 4;
	j = 0;
	while (str[i] && (str[i] == fdf[j]))
	{
		j++;
		i++;
		if (!fdf[j])
			return (1);
	}
	return (0);
}
