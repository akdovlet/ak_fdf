/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:44:19 by akdovlet          #+#    #+#             */
/*   Updated: 2023/12/27 23:26:36 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

// Why do I have two different width managers?
// because I wrote width_m later, it's better than the first one
// but width_manager still works with certain functions 
// and I can't be arsed to change it
int	width_manager(int width, int minus, int zero)
{
	int	count;

	count = 0;
	while (width - minus > 0)
	{
		if (zero)
			count += ft_put_n_count_char('0');
		else
			count += ft_put_n_count_char(' ');
		width--;
	}
	return (count);
}

int	width_m(int width, int count, int zero)
{
	int	tmp;

	tmp = 0;
	while (count < width)
	{
		if (zero)
			tmp += ft_put_n_count_char('0');
		else
			tmp += ft_put_n_count_char(' ');
		count++;
	}
	return (tmp);
}

int	case_zero(t_flag flags)
{
	int	count;

	count = 0;
	if (flags.width)
		count += width_m(flags.width, count, flags.precision);
	return (count);
}

int	precision_manager(int precision, int len)
{
	int	count;

	count = 0;
	while (precision > len)
	{
		count += ft_put_n_count_char('0');
		precision--;
	}
	return (count);
}
