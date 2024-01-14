/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_handler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akdovlet <akdovlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:48:49 by akdovlet          #+#    #+#             */
/*   Updated: 2023/12/27 23:26:26 by akdovlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

// Same logic as d_handler, a few specific rules but otherwise same old
int	ft_put_n_count_hex(size_t n, int count, int bin)
{
	char	*base;
	char	*cbase;

	base = "0123456789abcdef";
	cbase = "0123456789ABCDEF";
	if (n >= 16)
		count = ft_put_n_count_hex(n / 16, count + 1, bin);
	if (bin)
		ft_put_n_count_char(base[n % 16]);
	else
		ft_put_n_count_char(cbase[n % 16]);
	return (count);
}

int	zero_x(unsigned int n, t_flag flags, int bin)
{
	int	count;

	count = 0;
	if (flags.hash && n > 0 && bin)
		count += ft_putstrlen("0x", 2);
	else if (flags.hash && n > 0 && !bin)
		count += ft_putstrlen("0X", 2);
	return (count);
}

void	x_rules(t_flag *flags, int len, unsigned int n)
{
	if (flags->dash && !flags->width)
		flags->dash = 0;
	if (flags->precision >= flags->width)
		flags->total_width = 0;
	if (len > flags->total_width)
		flags->total_width = 0;
	if (flags->precision > len && !flags->dash)
		flags->total_width -= flags->precision;
	if (flags->precision < len && !flags->dash)
		flags->total_width -= len;
	if (flags->hash && n > 0)
		flags->total_width -= 2;
}

int	x_width(unsigned int n, t_flag flags, int bin)
{
	int	count;
	int	len;

	count = 0;
	len = ft_nbcount(n, 16);
	x_rules(&flags, len, n);
	if (flags.dash)
	{
		count += zero_x(n, flags, bin);
		if (flags.precision > len)
			count += precision_manager(flags.precision, len);
		count += ft_put_n_count_hex(n, 1, bin);
	}
	count += width_m(flags.total_width, count, flags.zero);
	if (!flags.dash)
	{
		count += zero_x(n, flags, bin);
		if (flags.precision > len)
			count += precision_manager(flags.precision, len);
		count += ft_put_n_count_hex(n, 1, bin);
	}
	return (count);
}

int	x_handler(unsigned int hex, t_flag flags, int bin)
{
	int	count;

	count = 0;
	if (flags.dot && !flags.precision && hex == 0)
		return (case_zero(flags));
	if (flags.width || flags.precision || flags.hash)
		count += x_width(hex, flags, bin);
	else
		count += ft_put_n_count_hex(hex, 1, bin);
	return (count);
}
