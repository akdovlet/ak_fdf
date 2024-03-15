/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:11:53 by akdovlet          #+#    #+#             */
/*   Updated: 2024/03/15 16:56:13 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		return (0x33FF33);
	}
	else
		return (0x33FF33);
}
